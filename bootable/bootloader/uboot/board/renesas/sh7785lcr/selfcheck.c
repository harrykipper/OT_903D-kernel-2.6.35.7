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
 * Copyright (C) 2008 Yoshihiro Shimoda <shimoda.yoshihiro@renesas.com>
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
#include <asm/io.h>
#include <asm/processor.h>
#include <asm/pci.h>

#if defined(CONFIG_CPU_32BIT)
#define NOCACHE_OFFSET		0x00000000
#else
#define NOCACHE_OFFSET		0xa0000000
#endif
#define PLD_LEDCR		(0x04000008 + NOCACHE_OFFSET)
#define PLD_SWSR		(0x0400000a + NOCACHE_OFFSET)
#define PLD_VERSR		(0x0400000c + NOCACHE_OFFSET)

#define SM107_DEVICEID		(0x13e00060 + NOCACHE_OFFSET)

static void wait_ms(unsigned long time)
{
	while (time--)
		udelay(1000);
}

static void test_pld(void)
{
	printf("PLD version = %04x\n", readb(PLD_VERSR));
}

static void test_sm107(void)
{
	printf("SM107 device ID = %04x\n", readl(SM107_DEVICEID));
}

static void test_led(void)
{
	printf("turn on LEDs 3, 5, 7, 9\n");
	writeb(0x55, PLD_LEDCR);
	wait_ms(2000);
	printf("turn on LEDs 4, 6, 8, 10\n");
	writeb(0xaa, PLD_LEDCR);
	wait_ms(2000);
	writeb(0x00, PLD_LEDCR);
}

static void test_dipsw(void)
{
	printf("Please DIPSW set = B'0101\n");
	while (readb(PLD_SWSR) != 0x05) {
		if (ctrlc())
			return;
	}
	printf("Please DIPSW set = B'1010\n");
	while (readb(PLD_SWSR) != 0x0A) {
		if (ctrlc())
			return;
	}
	printf("DIPSW OK\n");
}

static void test_net(void)
{
	unsigned long data;

	writel(0x80000000, 0xfe0401c0);
	data = readl(0xfe040220);
	if (data == 0x816910ec)
		printf("Ethernet OK\n");
	else
		printf("Ethernet NG, data = %08x\n", (unsigned int)data);
}

static void test_sata(void)
{
	unsigned long data;

	writel(0x80000800, 0xfe0401c0);
	data = readl(0xfe040220);
	if (data == 0x35121095)
		printf("SATA OK\n");
	else
		printf("SATA NG, data = %08x\n", (unsigned int)data);
}

static void test_pci(void)
{
	writel(0x80001800, 0xfe0401c0);
	printf("PCI CN1 ID = %08x\n", readl(0xfe040220));

	writel(0x80001000, 0xfe0401c0);
	printf("PCI CN2 ID = %08x\n", readl(0xfe040220));
}

int do_hw_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	char *cmd;

	if (argc != 2) {
		cmd_usage(cmdtp);
		return 1;
	}

	cmd = argv[1];
	switch (cmd[0]) {
	case 'a':	/* all */
		test_pld();
		test_led();
		test_dipsw();
		test_sm107();
		test_net();
		test_sata();
		test_pci();
		break;
	case 'p':	/* pld or pci */
		if (cmd[1] == 'l')
			test_pld();
		else
			test_pci();
		break;
	case 'l':	/* led */
		test_led();
		break;
	case 'd':	/* dipsw */
		test_dipsw();
		break;
	case 's':	/* sm107 or sata */
		if (cmd[1] == 'm')
			test_sm107();
		else
			test_sata();
		break;
	case 'n':	/* net */
		test_net();
		break;
	default:
		cmd_usage(cmdtp);
		return 1;
	}

	return 0;
}

U_BOOT_CMD(
	hwtest,	2,	1,	do_hw_test,
	"hardware test for R0P7785LC0011RL board",
	"\n"
	"hwtest all   - test all hardware\n"
	"hwtest pld   - output PLD version\n"
	"hwtest led   - turn on LEDs\n"
	"hwtest dipsw - test DIP switch\n"
	"hwtest sm107 - output SM107 version\n"
	"hwtest net   - check RTL8110 ID\n"
	"hwtest sata  - check SiI3512 ID\n"
	"hwtest pci   - output PCI slot device ID"
);
