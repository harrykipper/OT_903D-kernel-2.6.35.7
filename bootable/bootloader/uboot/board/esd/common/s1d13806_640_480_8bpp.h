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
 * Copyright (c) 2000,2001 Epson Research and Development, Inc.
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
 *
 * File generated by S1D13806CFG.EXE
 * Panel:  (active)   640x480 59Hz TFT Single 18-bit (PCLK=CLKI2=25.000MHz)
 * Memory: Embedded SDRAM (MCLK=CLKI=49.152MHz) (BUSCLK=33.333MHz)
 */

static S1D_REGS regs_13806_640_320_16bpp[] =
{
	{0x0001,0x00},   /* Miscellaneous Register */
	{0x01FC,0x00},   /* Display Mode Register */
	{0x0004,0x18},   /* General IO Pins Configuration Register 0 */
	{0x0005,0x00},   /* General IO Pins Configuration Register 1 */
	{0x0008,0x18},   /* General IO Pins Control Register 0 */
	{0x0009,0x00},   /* General IO Pins Control Register 1 */
	{0x0010,0x00},   /* Memory Clock Configuration Register */
	{0x0014,0x02},   /* LCD Pixel Clock Configuration Register */
	{0x0018,0x02},   /* CRT/TV Pixel Clock Configuration Register */
	{0x001C,0x02},   /* MediaPlug Clock Configuration Register */
	{0x001E,0x01},   /* CPU To Memory Wait State Select Register */
	{0x0021,0x03},   /* DRAM Refresh Rate Register */
	{0x002A,0x00},   /* DRAM Timings Control Register 0 */
	{0x002B,0x01},   /* DRAM Timings Control Register 1 */
	{0x0020,0x80},   /* Memory Configuration Register */
	{0x0030,0x25},   /* Panel Type Register */
	{0x0031,0x00},   /* MOD Rate Register */
	{0x0032,0x4F},   /* LCD Horizontal Display Width Register */
	{0x0034,0x13},   /* LCD Horizontal Non-Display Period Register */
	{0x0035,0x00},   /* TFT FPLINE Start Position Register */
	{0x0036,0x0B},   /* TFT FPLINE Pulse Width Register */
	{0x0038,0xDF},   /* LCD Vertical Display Height Register 0 */
	{0x0039,0x01},   /* LCD Vertical Display Height Register 1 */
	{0x003A,0x24},   /* LCD Vertical Non-Display Period Register */
	{0x003B,0x00},   /* TFT FPFRAME Start Position Register */
	{0x003C,0x01},   /* TFT FPFRAME Pulse Width Register */
	{0x0040,0x03},   /* LCD Display Mode Register (8bpp) */
	{0x0041,0x00},   /* LCD Miscellaneous Register */
	{0x0042,0x00},   /* LCD Display Start Address Register 0 */
	{0x0043,0x00},   /* LCD Display Start Address Register 1 */
	{0x0044,0x00},   /* LCD Display Start Address Register 2 */
	{0x0046,0x80},   /* LCD Memory Address Offset Register 0 */
	{0x0047,0x02},   /* LCD Memory Address Offset Register 1 */
	{0x0048,0x00},   /* LCD Pixel Panning Register */
	{0x004A,0x00},   /* LCD Display FIFO High Threshold Control Register */
	{0x004B,0x00},   /* LCD Display FIFO Low Threshold Control Register */
	{0x0050,0x4F},   /* CRT/TV Horizontal Display Width Register */
	{0x0052,0x13},   /* CRT/TV Horizontal Non-Display Period Register */
	{0x0053,0x01},   /* CRT/TV HRTC Start Position Register */
	{0x0054,0x0B},   /* CRT/TV HRTC Pulse Width Register */
	{0x0056,0xDF},   /* CRT/TV Vertical Display Height Register 0 */
	{0x0057,0x01},   /* CRT/TV Vertical Display Height Register 1 */
	{0x0058,0x2B},   /* CRT/TV Vertical Non-Display Period Register */
	{0x0059,0x09},   /* CRT/TV VRTC Start Position Register */
	{0x005A,0x01},   /* CRT/TV VRTC Pulse Width Register */
	{0x005B,0x10},   /* TV Output Control Register */
	{0x0060,0x05},   /* CRT/TV Display Mode Register */
	{0x0062,0x00},   /* CRT/TV Display Start Address Register 0 */
	{0x0063,0x00},   /* CRT/TV Display Start Address Register 1 */
	{0x0064,0x00},   /* CRT/TV Display Start Address Register 2 */
	{0x0066,0x80},   /* CRT/TV Memory Address Offset Register 0 */
	{0x0067,0x02},   /* CRT/TV Memory Address Offset Register 1 */
	{0x0068,0x00},   /* CRT/TV Pixel Panning Register */
	{0x006A,0x00},   /* CRT/TV Display FIFO High Threshold Control Register */
	{0x006B,0x00},   /* CRT/TV Display FIFO Low Threshold Control Register */
	{0x0070,0x00},   /* LCD Ink/Cursor Control Register */
	{0x0071,0x01},   /* LCD Ink/Cursor Start Address Register */
	{0x0072,0x00},   /* LCD Cursor X Position Register 0 */
	{0x0073,0x00},   /* LCD Cursor X Position Register 1 */
	{0x0074,0x00},   /* LCD Cursor Y Position Register 0 */
	{0x0075,0x00},   /* LCD Cursor Y Position Register 1 */
	{0x0076,0x00},   /* LCD Ink/Cursor Blue Color 0 Register */
	{0x0077,0x00},   /* LCD Ink/Cursor Green Color 0 Register */
	{0x0078,0x00},   /* LCD Ink/Cursor Red Color 0 Register */
	{0x007A,0x1F},   /* LCD Ink/Cursor Blue Color 1 Register */
	{0x007B,0x3F},   /* LCD Ink/Cursor Green Color 1 Register */
	{0x007C,0x1F},   /* LCD Ink/Cursor Red Color 1 Register */
	{0x007E,0x00},   /* LCD Ink/Cursor FIFO Threshold Register */
	{0x0080,0x00},   /* CRT/TV Ink/Cursor Control Register */
	{0x0081,0x01},   /* CRT/TV Ink/Cursor Start Address Register */
	{0x0082,0x00},   /* CRT/TV Cursor X Position Register 0 */
	{0x0083,0x00},   /* CRT/TV Cursor X Position Register 1 */
	{0x0084,0x00},   /* CRT/TV Cursor Y Position Register 0 */
	{0x0085,0x00},   /* CRT/TV Cursor Y Position Register 1 */
	{0x0086,0x00},   /* CRT/TV Ink/Cursor Blue Color 0 Register */
	{0x0087,0x00},   /* CRT/TV Ink/Cursor Green Color 0 Register */
	{0x0088,0x00},   /* CRT/TV Ink/Cursor Red Color 0 Register */
	{0x008A,0x1F},   /* CRT/TV Ink/Cursor Blue Color 1 Register */
	{0x008B,0x3F},   /* CRT/TV Ink/Cursor Green Color 1 Register */
	{0x008C,0x1F},   /* CRT/TV Ink/Cursor Red Color 1 Register */
	{0x008E,0x00},   /* CRT/TV Ink/Cursor FIFO Threshold Register */
	{0x0100,0x00},   /* BitBlt Control Register 0 */
	{0x0101,0x00},   /* BitBlt Control Register 1 */
	{0x0102,0x00},   /* BitBlt ROP Code/Color Expansion Register */
	{0x0103,0x00},   /* BitBlt Operation Register */
	{0x0104,0x00},   /* BitBlt Source Start Address Register 0 */
	{0x0105,0x00},   /* BitBlt Source Start Address Register 1 */
	{0x0106,0x00},   /* BitBlt Source Start Address Register 2 */
	{0x0108,0x00},   /* BitBlt Destination Start Address Register 0 */
	{0x0109,0x00},   /* BitBlt Destination Start Address Register 1 */
	{0x010A,0x00},   /* BitBlt Destination Start Address Register 2 */
	{0x010C,0x00},   /* BitBlt Memory Address Offset Register 0 */
	{0x010D,0x00},   /* BitBlt Memory Address Offset Register 1 */
	{0x0110,0x00},   /* BitBlt Width Register 0 */
	{0x0111,0x00},   /* BitBlt Width Register 1 */
	{0x0112,0x00},   /* BitBlt Height Register 0 */
	{0x0113,0x00},   /* BitBlt Height Register 1 */
	{0x0114,0x00},   /* BitBlt Background Color Register 0 */
	{0x0115,0x00},   /* BitBlt Background Color Register 1 */
	{0x0118,0x00},   /* BitBlt Foreground Color Register 0 */
	{0x0119,0x00},   /* BitBlt Foreground Color Register 1 */
	{0x01E0,0x00},   /* Look-Up Table Mode Register */
	{0x01E2,0x00},   /* Look-Up Table Address Register */
	{0x01F0,0x10},   /* Power Save Configuration Register */
	{0x01F1,0x00},   /* Power Save Status Register */
	{0x01F4,0x00},   /* CPU-to-Memory Access Watchdog Timer Register */
	{0x01FC,0x01},   /* Display Mode Register */
};
