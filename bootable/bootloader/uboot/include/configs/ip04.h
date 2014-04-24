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
 * U-boot - Configuration file for IP04 board (having BF532 processor)
 *
 * Copyright (c) 2006 Intratrade Ltd., Ivan Danov, idanov@gmail.com
 *
 * Copyright (c) 2005-2010 Analog Devices Inc.
 *
 * (C) Copyright 2000-2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Licensed under the GPL-2 or later.
 */

#ifndef __CONFIG_IP04_H__
#define __CONFIG_IP04_H__

#include <asm/config-pre.h>


/*
 * Processor Settings
 */
#define CONFIG_BFIN_CPU             bf532-0.5
#define CONFIG_BFIN_BOOT_MODE       BFIN_BOOT_NAND


/*
 * Clock Settings
 *	CCLK = (CLKIN * VCO_MULT) / CCLK_DIV
 *	SCLK = (CLKIN * VCO_MULT) / SCLK_DIV
 */
/* CONFIG_CLKIN_HZ is any value in Hz					*/
#define CONFIG_CLKIN_HZ			10000000
/* CLKIN_HALF controls the DF bit in PLL_CTL      0 = CLKIN		*/
/*                                                1 = CLKIN / 2		*/
#define CONFIG_CLKIN_HALF		0
/* PLL_BYPASS controls the BYPASS bit in PLL_CTL  0 = do not bypass	*/
/*                                                1 = bypass PLL	*/
#define CONFIG_PLL_BYPASS		0
/* VCO_MULT controls the MSEL (multiplier) bits in PLL_CTL		*/
/* Values can range from 0-63 (where 0 means 64)			*/
#define CONFIG_VCO_MULT			40
/* CCLK_DIV controls the core clock divider				*/
/* Values can be 1, 2, 4, or 8 ONLY					*/
#define CONFIG_CCLK_DIV			1
/* SCLK_DIV controls the system clock divider				*/
/* Values can range from 1-15						*/
#define CONFIG_SCLK_DIV			3


/*
 * Memory Settings
 */
#define CONFIG_MEM_ADD_WDTH	10
#define CONFIG_MEM_SIZE		64

#define CONFIG_EBIU_SDRRC_VAL	0x408
#define CONFIG_EBIU_SDGCTL_VAL	0x9111cd

#define CONFIG_EBIU_AMGCTL_VAL	0xFF
#define CONFIG_EBIU_AMBCTL0_VAL	0xffc2ffc2
#define CONFIG_EBIU_AMBCTL1_VAL	0xffc2ffc2

#define CONFIG_SYS_MONITOR_LEN		(256 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(128 * 1024)


/*
 * Network Settings
 */
#define ADI_CMDS_NETWORK	1
#define CONFIG_NET_MULTI	1
#define CONFIG_HOSTNAME		IP04

#define CONFIG_DRIVER_DM9000	1
#define CONFIG_DM9000_NO_SROM
#define CONFIG_DM9000_BASE	0x20100000
#define DM9000_IO		CONFIG_DM9000_BASE
#define DM9000_DATA		(CONFIG_DM9000_BASE + 2)


/*
 * Flash Settings
 */
#define CONFIG_ENV_OVERWRITE	1
#define CONFIG_SYS_NO_FLASH		/* we have only NAND */


/*
 * SPI Settings
 */
#define CONFIG_BFIN_SPI
#define CONFIG_ENV_SPI_MAX_HZ	30000000
#define CONFIG_SF_DEFAULT_SPEED	30000000
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_STMICRO
#define CONFIG_SPI_FLASH_WINBOND


/*
 * Env Storage Settings
 */
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_PREBOOT		"echo starting from spi flash"
#define CONFIG_ENV_OFFSET	0x30000
#define CONFIG_ENV_SIZE		0x10000
#define CONFIG_ENV_SECT_SIZE	0x10000


/*
 * NAND Settings
 */
#define CONFIG_NAND_PLAT
#define CONFIG_SYS_NAND_BASE		0x20000000
#define CONFIG_SYS_MAX_NAND_DEVICE	1

#define BFIN_NAND_CLE(chip) ((unsigned long)(chip)->IO_ADDR_W | (1 << 2))
#define BFIN_NAND_ALE(chip) ((unsigned long)(chip)->IO_ADDR_W | (1 << 1))
#define BFIN_NAND_READY     PF10
#define BFIN_NAND_WRITE(addr, cmd) \
	do { \
		bfin_write8(addr, cmd); \
		SSYNC(); \
	} while (0)

#define NAND_PLAT_WRITE_CMD(chip, cmd) BFIN_NAND_WRITE(BFIN_NAND_CLE(chip), cmd)
#define NAND_PLAT_WRITE_ADR(chip, cmd) BFIN_NAND_WRITE(BFIN_NAND_ALE(chip), cmd)
#define NAND_PLAT_DEV_READY(chip)      (bfin_read_FIO_FLAG_D() & BFIN_NAND_READY)
#define NAND_PLAT_INIT() \
	do { \
		bfin_write_FIO_DIR(bfin_read_FIO_DIR() & ~BFIN_NAND_READY); \
		bfin_write_FIO_INEN(bfin_read_FIO_INEN() | BFIN_NAND_READY); \
		bfin_write_FIO_EDGE(bfin_read_FIO_EDGE() & ~BFIN_NAND_READY); \
		bfin_write_FIO_POLAR(bfin_read_FIO_POLAR() & ~BFIN_NAND_READY); \
	} while (0)


/*
 * Misc Settings
 */
#define CONFIG_BAUDRATE		115200
#define CONFIG_MISC_INIT_R	/* needed for MAC address */
#define CONFIG_UART_CONSOLE	0

#undef CONFIG_SHOW_BOOT_PROGRESS
/* Enable this if bootretry required; currently it's disabled */
#define CONFIG_BOOT_RETRY_TIME	-1
#define CONFIG_BOOTCOMMAND	"run nandboot"
#define CONFIG_AUTOBOOT_PROMPT	"autoboot in %d seconds\n"


/*
 * Pull in common ADI header for remaining command/environment setup
 */
#include <configs/bfin_adi_common.h>

#endif