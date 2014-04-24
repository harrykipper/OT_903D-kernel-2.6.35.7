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
 * (C) Copyright 2007
 * Michael Schwingen, michael@schwingen.org
 *
 * (C) Copyright 2006
 * Stefan Roese, DENX Software Engineering, sr@denx.de.
 *
 * (C) Copyright 2002
 * Kyle Harris, Nexus Technologies, Inc. kharris@nexus-tech.net
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <asm/arch/ixp425.h>
#include <asm/io.h>

#include <miiphy.h>

#include "actux2_hw.h"

DECLARE_GLOBAL_DATA_PTR;

int board_init (void)
{
	gd->bd->bi_arch_number = MACH_TYPE_ACTUX2;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0x00000100;

	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_IORST);
	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_ETHRST);
	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_DSR);
	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_DCD);

	GPIO_OUTPUT_CLEAR (CONFIG_SYS_GPIO_IORST);
	GPIO_OUTPUT_CLEAR (CONFIG_SYS_GPIO_ETHRST);

	GPIO_OUTPUT_CLEAR (CONFIG_SYS_GPIO_DSR);
	GPIO_OUTPUT_SET (CONFIG_SYS_GPIO_DCD);

	/* Setup GPIO's for Interrupt inputs */
	GPIO_OUTPUT_DISABLE (CONFIG_SYS_GPIO_DBGINT);
	GPIO_OUTPUT_DISABLE (CONFIG_SYS_GPIO_ETHINT);

	/* Setup GPIO's for 33MHz clock output */
	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_PCI_CLK);
	GPIO_OUTPUT_ENABLE (CONFIG_SYS_GPIO_EXTBUS_CLK);
	*IXP425_GPIO_GPCLKR = 0x011001FF;

	/* CS1: IPAC-X */
	*IXP425_EXP_CS1 = 0x94d10013;
	/* CS5: Debug port */
	*IXP425_EXP_CS5 = 0x9d520003;
	/* CS6: HW release register */
	*IXP425_EXP_CS6 = 0x81860001;
	/* CS7: LEDs */
	*IXP425_EXP_CS7 = 0x80900003;

	udelay (533);
	GPIO_OUTPUT_SET (CONFIG_SYS_GPIO_IORST);
	GPIO_OUTPUT_SET (CONFIG_SYS_GPIO_ETHRST);

	ACTUX2_LED1 (1);
	ACTUX2_LED2 (0);
	ACTUX2_LED3 (0);
	ACTUX2_LED4 (0);

	return 0;
}

/*
 * Check Board Identity
 */
int checkboard (void)
{
	char *s = getenv ("serial#");

	puts ("Board: AcTux-2 rev.");
	putc (ACTUX2_BOARDREL + 'A' - 1);

	if (s != NULL) {
		puts (", serial# ");
		puts (s);
	}
	putc ('\n');

	return (0);
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return (0);
}

/*************************************************************************
 * get_board_rev() - setup to pass kernel board revision information
 * 0 = reserved
 * 1 = Rev. A
 * 2 = Rev. B
 *************************************************************************/
u32 get_board_rev (void)
{
	return ACTUX2_BOARDREL;
}

void reset_phy (void)
{
	/* init IcPlus IP175C ethernet switch to native IP175C mode */
	miiphy_write ("NPE0", 29, 31, 0x175C);
}
