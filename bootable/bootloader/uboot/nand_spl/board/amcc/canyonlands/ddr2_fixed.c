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
 * (C) Copyright 2008-2009
 * Stefan Roese, DENX Software Engineering, sr@denx.de.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <ppc4xx.h>
#include <asm/io.h>
#include <asm/processor.h>

/*
 * This code can configure those two Crucial SODIMM's:
 *
 * Crucial CT6464AC667.4FE - 512MB SO-DIMM (single rank)
 * Crucial CT6464AC667.8FB - 512MB SO-DIMM (dual rank)
 *
 */

#define TEST_ADDR	0x10000000
#define TEST_MAGIC	0x11223344

static void wait_init_complete(void)
{
	u32 val;

	do {
		mfsdram(SDRAM_MCSTAT, val);
	} while (!(val & 0x80000000));
}

static void ddr_start(void)
{
	mtsdram(SDRAM_MCOPT2, 0x28000000);
	wait_init_complete();
}

static void ddr_init_common(void)
{
	/*
	 * Reset the DDR-SDRAM controller.
	 */
	mtsdr(SDR0_SRST, (0x80000000 >> 10));
	mtsdr(SDR0_SRST, 0x00000000);

	/*
	 * These values are cloned from a running NOR booting
	 * Canyonlands with SPD-DDR2 detection and calibration
	 * enabled. This will only work for the same memory
	 * configuration as used here:
	 *
	 */
	mtsdram(SDRAM_MCOPT2, 0x00000000);
	mtsdram(SDRAM_MODT0, 0x01000000);
	mtsdram(SDRAM_WRDTR, 0x82000823);
	mtsdram(SDRAM_CLKTR, 0x40000000);
	mtsdram(SDRAM_MB0CF, 0x00000201);
	mtsdram(SDRAM_RTR, 0x06180000);
	mtsdram(SDRAM_SDTR1, 0x80201000);
	mtsdram(SDRAM_SDTR2, 0x42103243);
	mtsdram(SDRAM_SDTR3, 0x0A0D0D16);
	mtsdram(SDRAM_MMODE, 0x00000632);
	mtsdram(SDRAM_MEMODE, 0x00000040);
	mtsdram(SDRAM_INITPLR0, 0xB5380000);
	mtsdram(SDRAM_INITPLR1, 0x82100400);
	mtsdram(SDRAM_INITPLR2, 0x80820000);
	mtsdram(SDRAM_INITPLR3, 0x80830000);
	mtsdram(SDRAM_INITPLR4, 0x80810040);
	mtsdram(SDRAM_INITPLR5, 0x80800532);
	mtsdram(SDRAM_INITPLR6, 0x82100400);
	mtsdram(SDRAM_INITPLR7, 0x8A080000);
	mtsdram(SDRAM_INITPLR8, 0x8A080000);
	mtsdram(SDRAM_INITPLR9, 0x8A080000);
	mtsdram(SDRAM_INITPLR10, 0x8A080000);
	mtsdram(SDRAM_INITPLR11, 0x80000432);
	mtsdram(SDRAM_INITPLR12, 0x808103C0);
	mtsdram(SDRAM_INITPLR13, 0x80810040);
	mtsdram(SDRAM_INITPLR14, 0x00000000);
	mtsdram(SDRAM_INITPLR15, 0x00000000);
	mtsdram(SDRAM_RDCC, 0x40000000);
	mtsdram(SDRAM_RQDC, 0x80000038);
	mtsdram(SDRAM_RFDC, 0x00000257);

	mtdcr(SDRAM_R0BAS, 0x0000F800);		/* MQ0_B0BAS */
	mtdcr(SDRAM_R1BAS, 0x0400F800);		/* MQ0_B1BAS */
}

phys_size_t initdram(int board_type)
{
	/*
	 * First try init for this module:
	 *
	 * Crucial CT6464AC667.8FB - 512MB SO-DIMM (dual rank)
	 */

	ddr_init_common();

	/*
	 * Crucial CT6464AC667.8FB - 512MB SO-DIMM
	 */
	mtdcr(SDRAM_R0BAS, 0x0000F800);
	mtdcr(SDRAM_R1BAS, 0x0400F800);
	mtsdram(SDRAM_MCOPT1, 0x05122000);
	mtsdram(SDRAM_CODT, 0x02800021);
	mtsdram(SDRAM_MB1CF, 0x00000201);

	ddr_start();

	/*
	 * Now test if the dual-ranked module is really installed
	 * by checking an address in the upper 256MByte region
	 */
	out_be32((void *)TEST_ADDR, TEST_MAGIC);
	if (in_be32((void *)TEST_ADDR) != TEST_MAGIC) {
		/*
		 * The test failed, so we assume that the single
		 * ranked module is installed:
		 *
		 * Crucial CT6464AC667.4FE - 512MB SO-DIMM (single rank)
		 */

		ddr_init_common();

		mtdcr(SDRAM_R0BAS, 0x0000F000);
		mtsdram(SDRAM_MCOPT1, 0x05322000);
		mtsdram(SDRAM_CODT, 0x00800021);

		ddr_start();
	}

	return CONFIG_SYS_MBYTES_SDRAM << 20;
}
