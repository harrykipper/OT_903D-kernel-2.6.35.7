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
 * (C) Copyright 2000, 2001, 2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
#include <mpc8xx.h>

/* ------------------------------------------------------------------------- */
const uint sdram_table[] =
{
/*-----------------
 UPM A contents:
----------------- */
/*---------------------------------------------------
 Read Single Beat Cycle. Offset 0 in the RAM array.
---------------------------------------------------- */
0x1f07fc04,  0xeeaefc04,  0x11adfc04,  0xefbbbc00 ,
0x1ff77c47,  0x1ff77c35,  0xefeabc34,  0x1fb57c35 ,
/*------------------------------------------------
 Read Burst Cycle. Offset 0x8 in the RAM array.
------------------------------------------------ */
0x1f07fc04,  0xeeaefc04,  0x10adfc04,  0xf0affc00,
0xf0affc00,  0xf1affc00,  0xefbbbc00,  0x1ff77c47,
0xffffffff,  0xffffffff,  0xffffffff,  0xffffffff,
0xffffffff,  0xffffffff,  0xffffffff,  0xffffffff,
/*-------------------------------------------------------
 Write Single Beat Cycle. Offset 0x18 in the RAM array
------------------------------------------------------- */
0x1f27fc04,  0xeeaebc00,  0x01b93c04,  0x1ff77c47 ,
0xffffffff,  0xffffffff,  0xffffffff,  0xffffffff ,
/*-------------------------------------------------
 Write Burst Cycle. Offset 0x20 in the RAM array
------------------------------------------------- */
0x1f07fc04, 0xeeaebc00, 0x10ad7c00, 0xf0affc00,
0xf0affc00, 0xe1bbbc04, 0x1ff77c47, 0xffffffff,
0xffffffff,  0xffffffff,  0xffffffff,  0xffffffff ,
0xffffffff,  0xffffffff,  0xffffffff,  0xffffffff ,
/*------------------------------------------------------------------------
 Periodic Timer Expired. For DRAM refresh. Offset 0x30 in the RAM array
------------------------------------------------------------------------ */
0x1ff5fc84, 0xfffffc04, 0xfffffc04, 0xfffffc04,
0xfffffc84, 0xfffffc07, 0xffffffff, 0xffffffff,
0xffffffff,  0xffffffff,  0xffffffff,  0xffffffff ,
/*-----------
*  Exception:
*  ----------- */
0x7ffefc07,  0xffffffff,  0xffffffff,  0xffffffff ,
};

/* ------------------------------------------------------------------------- */
/*
 * Check Board Identity:
 *
 * Test ID string (SVM8...)
 *
 * Return 1 for "SC8xx" type, 0 else.
 */

int checkboard (void)
{
    char *s = getenv("serial#");
    int board_type;

    if (!s || strncmp(s, "SVM8", 4)) {
	printf ("### No HW ID - assuming SVM SC8xx\n");
	return (0);
    }

    board_type = 1;

    for (; *s; ++s) {
	if (*s == ' ')
	    break;
	putc (*s);
    }

    putc ('\n');

    return (0);
}

/* ------------------------------------------------------------------------- */

phys_size_t initdram (int board_type)
{
	volatile immap_t     *immap  = (immap_t *)CONFIG_SYS_IMMR;
	volatile memctl8xx_t *memctl = &immap->im_memctl;
	long int size_b0 = 0;

	upmconfig(UPMA, (uint *)sdram_table, sizeof(sdram_table)/sizeof(uint));

	memctl->memc_mptpr = CONFIG_SYS_MPTPR;
#if defined (CONFIG_SDRAM_16M)
	memctl->memc_mamr = 0x00802114 | CONFIG_SYS_MxMR_PTx;
	memctl->memc_mcr  = 0x80002105;     /* SDRAM bank 0 */
	udelay(1);
	memctl->memc_mcr  = 0x80002830;
	udelay(1);
	memctl->memc_mar  = 0x00000088;
	udelay(1);
	memctl->memc_mcr  = 0x80002106;
	udelay(1);
	memctl->memc_or1 =  0xff000a00;
	size_b0 = 0x01000000;
#elif defined (CONFIG_SDRAM_32M)
	memctl->memc_mamr = 0x00904114 | CONFIG_SYS_MxMR_PTx;
	memctl->memc_mcr  = 0x80002105;     /* SDRAM bank 0 */
	udelay(1);
	memctl->memc_mcr  = 0x80002830;
	udelay(1);
	memctl->memc_mar  = 0x00000088;
	udelay(1);
	memctl->memc_mcr  = 0x80002106;
	udelay(1);
	memctl->memc_or1 =  0xfe000a00;
	size_b0 = 0x02000000;
#elif defined (CONFIG_SDRAM_64M)
	memctl->memc_mamr = 0x00a04114 | CONFIG_SYS_MxMR_PTx;
	memctl->memc_mcr  = 0x80002105;     /* SDRAM bank 0 */
	udelay(1);
	memctl->memc_mcr  = 0x80002830;
	udelay(1);
	memctl->memc_mar  = 0x00000088;
	udelay(1);
	memctl->memc_mcr  = 0x80002106;
	udelay(1);
	memctl->memc_or1 =  0xfc000a00;
	size_b0 = 0x04000000;
#else
#error SDRAM size configuration missing.
#endif
	memctl->memc_br1 =  0x00000081;
	udelay(200);
	return (size_b0 );
}

#if defined(CONFIG_CMD_DOC)
void doc_init (void)
{
	        doc_probe (CONFIG_SYS_DOC_BASE);
}
#endif