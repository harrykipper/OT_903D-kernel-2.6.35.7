/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/*
 * da8xx.c - TI's DA8xx platform specific usb wrapper functions.
 *
 * Author: Ajay Kumar Gupta <ajay.gupta@ti.com>
 *
 * Based on drivers/usb/musb/davinci.c
 *
 * Copyright (C) 2009 Texas Instruments Incorporated
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include <common.h>

#include "da8xx.h"

/* MUSB platform configuration */
struct musb_config musb_cfg = {
	(struct	musb_regs *)DA8XX_USB_OTG_CORE_BASE,
	DA8XX_USB_OTG_TIMEOUT,
	0
};

/*
 * This function enables VBUS by driving the GPIO Bank4 Pin 15 high.
 */
static void enable_vbus(void)
{
	u32 value;

	/* configure GPIO bank4 pin 15 in output direction */
	value = readl(&davinci_gpio_bank45->dir);
	writel((value & (~DA8XX_USB_VBUS_GPIO)), &davinci_gpio_bank45->dir);

	/* set GPIO bank4 pin 15 high to drive VBUS */
	value = readl(&davinci_gpio_bank45->set_data);
	writel((value | DA8XX_USB_VBUS_GPIO), &davinci_gpio_bank45->set_data);
}

/*
 * Enable the usb0 phy. This initialization procedure is explained in
 * the DA8xx USB user guide document.
 */
static u8 phy_on(void)
{
	u32 timeout;
	u32 cfgchip2;

	cfgchip2 = readl(&davinci_syscfg_regs->cfgchip2);

	cfgchip2 &= ~(CFGCHIP2_RESET | CFGCHIP2_PHYPWRDN | CFGCHIP2_OTGPWRDN |
		      CFGCHIP2_OTGMODE | CFGCHIP2_REFFREQ);
	cfgchip2 |= CFGCHIP2_SESENDEN | CFGCHIP2_VBDTCTEN | CFGCHIP2_PHY_PLLON |
		    CFGCHIP2_REFFREQ_24MHZ;

	writel(cfgchip2, &davinci_syscfg_regs->cfgchip2);

	/* wait until the usb phy pll locks */
	timeout = musb_cfg.timeout;
	while (timeout--)
		if (readl(&davinci_syscfg_regs->cfgchip2) & CFGCHIP2_PHYCLKGD)
			return 1;

	/* USB phy was not turned on */
	return 0;
}

/*
 * Disable the usb phy
 */
static void phy_off(void)
{
	u32 cfgchip2;

	/*
	 * Power down the on-chip PHY.
	 */
	cfgchip2 = readl(&davinci_syscfg_regs->cfgchip2);
	cfgchip2 &= ~CFGCHIP2_PHY_PLLON;
	cfgchip2 |= CFGCHIP2_PHYPWRDN | CFGCHIP2_OTGPWRDN;
	writel(cfgchip2, &davinci_syscfg_regs->cfgchip2);
}

/*
 * This function performs DA8xx platform specific initialization for usb0.
 */
int musb_platform_init(void)
{
	u32  revision;

	/* enable psc for usb2.0 */
	lpsc_on(33);

	/* enable usb vbus */
	enable_vbus();

	/* reset the controller */
	writel(0x1, &da8xx_usb_regs->control);
	udelay(5000);

	/* start the on-chip usb phy and its pll */
	if (phy_on() == 0)
		return -1;

	/* Returns zero if e.g. not clocked */
	revision = readl(&da8xx_usb_regs->revision);
	if (revision == 0)
		return -1;

	/* Disable all interrupts */
	writel((DA8XX_USB_USBINT_MASK | DA8XX_USB_TXINT_MASK |
		DA8XX_USB_RXINT_MASK), &da8xx_usb_regs->intmsk_set);
	return 0;
}

/*
 * This function performs DA8xx platform specific deinitialization for usb0.
 */
void musb_platform_deinit(void)
{
	/* Turn of the phy */
	phy_off();

	/* flush any interrupts */
	writel((DA8XX_USB_USBINT_MASK | DA8XX_USB_TXINT_MASK |
		DA8XX_USB_RXINT_MASK), &da8xx_usb_regs->intmsk_clr);
	writel(0, &da8xx_usb_regs->eoi);
}
