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
 * Copyright (C) 2009 Texas Instruments Incorporated
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <common.h>
#include <nand.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>
#include <asm/arch/gpio_defs.h>
#include <asm/arch/nand_defs.h>
#include "../common/misc.h"
#include <net.h>
#include <netdev.h>

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	struct davinci_gpio *gpio01_base =
			(struct davinci_gpio *)DAVINCI_GPIO_BANK01;
	struct davinci_gpio *gpio23_base =
			(struct davinci_gpio *)DAVINCI_GPIO_BANK23;
	struct davinci_gpio *gpio67_base =
			(struct davinci_gpio *)DAVINCI_GPIO_BANK67;

	gd->bd->bi_arch_number = MACH_TYPE_DM355_LEOPARD;
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

	/* GIO 9 & 10 are used for IO */
	writel((readl(PINMUX3) & 0XF8FFFFFF), PINMUX3);

	/* Interrupt set GIO 9 */
	writel((readl(DAVINCI_GPIO_BINTEN) | 0x1), DAVINCI_GPIO_BINTEN);

	/* set GIO 9 input */
	writel((readl(&gpio01_base->dir) | (1 << 9)), &gpio01_base->dir);

	/* Both edge trigger GIO 9 */
	writel((readl(&gpio01_base->set_rising) | (1 << 9)),
						&gpio01_base->set_rising);
	writel((readl(&gpio01_base->dir) & ~(1 << 5)), &gpio01_base->dir);

	/* output low */
	writel((readl(&gpio01_base->set_data) & ~(1 << 5)),
						&gpio01_base->set_data);

	/* set GIO 10 output */
	writel((readl(&gpio01_base->dir) & ~(1 << 10)), &gpio01_base->dir);

	/* output high */
	writel((readl(&gpio01_base->set_data) | (1 << 10)),
						&gpio01_base->set_data);

	/* set GIO 32 output */
	writel((readl(&gpio23_base->dir) & ~(1 << 0)), &gpio23_base->dir);

	/* output High */
	writel((readl(&gpio23_base->set_data) | (1 << 0)),
						&gpio23_base->set_data);

	/* Enable UART1 MUX Lines */
	writel((readl(PINMUX0) & ~3), PINMUX0);
	writel((readl(&gpio67_base->dir) & ~(1 << 6)), &gpio67_base->dir);
	writel((readl(&gpio67_base->set_data) | (1 << 6)),
						&gpio67_base->set_data);

	return 0;
}

#ifdef CONFIG_DRIVER_DM9000
int board_eth_init(bd_t *bis)
{
	return dm9000_initialize(bis);
}
#endif

#ifdef CONFIG_NAND_DAVINCI
int board_nand_init(struct nand_chip *nand)
{
	davinci_nand_init(nand);

	return 0;
}
#endif
