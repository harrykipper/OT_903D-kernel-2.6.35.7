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
 * (C) Copyright 2009
 * Vipin Kumar, ST Micoelectronics, vipin.kumar@st.com.
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

#ifndef SPR_SMI_H
#define SPR_SMI_H

/* 0xF800.0000 . 0xFBFF.FFFF	64MB	SMI (Serial Flash Mem) */
/* 0xFC00.0000 . 0xFC1F.FFFF	2MB	SMI (Serial Flash Reg.) */

#define FLASH_START_ADDRESS	CONFIG_SYS_FLASH_BASE
#define FLASH_BANK_SIZE		CONFIG_SYS_FLASH_BANK_SIZE

#define SMIBANK0_BASE		(FLASH_START_ADDRESS)
#define SMIBANK1_BASE		(SMIBANK0_BASE + FLASH_BANK_SIZE)
#define SMIBANK2_BASE		(SMIBANK1_BASE + FLASH_BANK_SIZE)
#define SMIBANK3_BASE		(SMIBANK2_BASE + FLASH_BANK_SIZE)

#define BANK0			0
#define BANK1			1
#define BANK2			2
#define BANK3			3

struct smi_regs {
	u32 smi_cr1;
	u32 smi_cr2;
	u32 smi_sr;
	u32 smi_tr;
	u32 smi_rr;
};

/* CONTROL REG 1 */
#define BANK_EN			0x0000000F	/* enables all banks */
#define DSEL_TIME		0x00000060	/* Deselect time */
#define PRESCAL5		0x00000500	/* AHB_CK prescaling value */
#define PRESCALA		0x00000A00	/* AHB_CK prescaling value */
#define PRESCAL3		0x00000300	/* AHB_CK prescaling value */
#define PRESCAL4		0x00000400	/* AHB_CK prescaling value */
#define SW_MODE			0x10000000	/* enables SW Mode */
#define WB_MODE			0x20000000	/* Write Burst Mode */
#define FAST_MODE		0x00008000	/* Fast Mode */
#define HOLD1			0x00010000

/* CONTROL REG 2 */
#define RD_STATUS_REG		0x00000400	/* reads status reg */
#define WE			0x00000800	/* Write Enable */
#define BANK0_SEL		0x00000000	/* Select Banck0 */
#define BANK1_SEL		0x00001000	/* Select Banck1 */
#define BANK2_SEL		0x00002000	/* Select Banck2 */
#define BANK3_SEL		0x00003000	/* Select Banck3 */
#define BANKSEL_SHIFT		12
#define SEND			0x00000080	/* Send data */
#define TX_LEN_1		0x00000001	/* data length = 1 byte */
#define TX_LEN_2		0x00000002	/* data length = 2 byte */
#define TX_LEN_3		0x00000003	/* data length = 3 byte */
#define TX_LEN_4		0x00000004	/* data length = 4 byte */
#define RX_LEN_1		0x00000010	/* data length = 1 byte */
#define RX_LEN_2		0x00000020	/* data length = 2 byte */
#define RX_LEN_3		0x00000030	/* data length = 3 byte */
#define RX_LEN_4		0x00000040	/* data length = 4 byte */
#define TFIE			0x00000100	/* Tx Flag Interrupt Enable */
#define WCIE			0x00000200	/* WCF Interrupt Enable */

/* STATUS_REG */
#define INT_WCF_CLR		0xFFFFFDFF	/* clear: WCF clear */
#define INT_TFF_CLR		0xFFFFFEFF	/* clear: TFF clear */
#define WIP_BIT			0x00000001	/* WIP Bit of SPI SR */
#define WEL_BIT			0x00000002	/* WEL Bit of SPI SR */
#define RSR			0x00000005	/* Read Status regiser */
#define TFF			0x00000100	/* Transfer Finished FLag */
#define WCF			0x00000200	/* Transfer Finished FLag */
#define ERF1			0x00000400	/* Error Flag 1 */
#define ERF2			0x00000800	/* Error Flag 2 */
#define WM0			0x00001000	/* WM Bank 0 */
#define WM1			0x00002000	/* WM Bank 1 */
#define WM2			0x00004000	/* WM Bank 2 */
#define WM3			0x00008000	/* WM Bank 3 */
#define WM_SHIFT		12

/* TR REG */
#define READ_ID			0x0000009F	/* Read Identification */
#define BULK_ERASE		0x000000C7	/* BULK erase */
#define SECTOR_ERASE		0x000000D8	/* SECTOR erase */
#define WRITE_ENABLE		0x00000006	/* Wenable command to FLASH */

struct flash_dev {
	u32 density;
	ulong size;
	ushort sector_count;
};

#define SFLASH_PAGE_SIZE	0x100	/* flash page size */
#define XFER_FINISH_TOUT	2	/* xfer finish timeout */
#define WMODE_TOUT		2	/* write enable timeout */

#endif
