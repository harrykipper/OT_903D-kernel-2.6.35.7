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
 * (C) Copyright 2002
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

/*
 * CPU test
 * Branch instructions:		b, bl, bc
 *
 * The first 2 instructions (b, bl) are verified by jumping
 * to a fixed address and checking whether control was transfered
 * to that very point. For the bl instruction the value of the
 * link register is checked as well (using mfspr).
 * To verify the bc instruction various combinations of the BI/BO
 * fields, the CTR and the condition register values are
 * checked. The list of such combinations is pre-built and
 * linked in U-Boot at build time.
 */

#include <post.h>
#include "cpu_asm.h"

#if CONFIG_POST & CONFIG_SYS_POST_CPU

extern void cpu_post_exec_11 (ulong *code, ulong *res, ulong op1);
extern void cpu_post_exec_31 (ulong *code, ulong *ctr, ulong *lr, ulong *jump,
    ulong cr);

static int cpu_post_test_bc (ulong cmd, ulong bo, ulong bi,
    int pjump, int decr, int link, ulong pctr, ulong cr)
{
    int ret = 0;
    ulong lr = 0;
    ulong ctr = pctr;
    ulong jump;

    unsigned long code[] =
    {
	ASM_MTCR(6),
	ASM_MFLR(6),
	ASM_MTCTR(3),
	ASM_MTLR(4),
	ASM_LI(5, 1),
	ASM_3O(cmd, bo, bi, 8),
	ASM_LI(5, 0),
	ASM_MFCTR(3),
	ASM_MFLR(4),
	ASM_MTLR(6),
	ASM_BLR,
    };

    cpu_post_exec_31 (code, &ctr, &lr, &jump, cr);

    if (ret == 0)
	ret = pjump == jump ? 0 : -1;
    if (ret == 0)
    {
	if (decr)
	    ret = pctr == ctr + 1 ? 0 : -1;
	else
	    ret = pctr == ctr ? 0 : -1;
    }
    if (ret == 0)
    {
	if (link)
	    ret = lr == (ulong) code + 24 ? 0 : -1;
	else
	    ret = lr == 0 ? 0 : -1;
    }

    return ret;
}

int cpu_post_test_b (void)
{
    int ret = 0;
    unsigned int i;
    int flag = disable_interrupts();

    if (ret == 0)
    {
	ulong code[] =
	{
	   ASM_MFLR(4),
	   ASM_MTLR(3),
	   ASM_B(4),
	   ASM_MFLR(3),
	   ASM_MTLR(4),
	   ASM_BLR,
	};
	ulong res;

	cpu_post_exec_11 (code, &res, 0);

	ret = res == 0 ? 0 : -1;

	if (ret != 0)
	{
	    post_log ("Error at b1 test !\n");
	}
    }

    if (ret == 0)
    {
	ulong code[] =
	{
	   ASM_MFLR(4),
	   ASM_MTLR(3),
	   ASM_BL(4),
	   ASM_MFLR(3),
	   ASM_MTLR(4),
	   ASM_BLR,
	};
	ulong res;

	cpu_post_exec_11 (code, &res, 0);

	ret = res == (ulong)code + 12 ? 0 : -1;

	if (ret != 0)
	{
	    post_log ("Error at b2 test !\n");
	}
    }

    if (ret == 0)
    {
	ulong cc, cd;
	int cond;
	ulong ctr;
	int link;

	i = 0;

	for (cc = 0; cc < 4 && ret == 0; cc++)
	{
	    for (cd = 0; cd < 4 && ret == 0; cd++)
	    {
		for (link = 0; link <= 1 && ret == 0; link++)
		{
		    for (cond = 0; cond <= 1 && ret == 0; cond++)
		    {
			for (ctr = 1; ctr <= 2 && ret == 0; ctr++)
			{
			    int decr = cd < 2;
			    int cr = cond ? 0x80000000 : 0x00000000;
			    int jumpc = cc >= 2 ||
					(cc == 0 && !cond) ||
					(cc == 1 && cond);
			    int jumpd = cd >= 2 ||
					(cd == 0 && ctr != 1) ||
					(cd == 1 && ctr == 1);
			    int jump = jumpc && jumpd;

			    ret = cpu_post_test_bc (link ? OP_BCL : OP_BC,
				(cc << 3) + (cd << 1), 0, jump, decr, link,
				ctr, cr);

			    if (ret != 0)
			    {
				post_log ("Error at b3 test %d !\n", i);
			    }

			    i++;
			}
		    }
		}
	    }
	}
    }

    if (flag)
	enable_interrupts();

    return ret;
}

#endif
