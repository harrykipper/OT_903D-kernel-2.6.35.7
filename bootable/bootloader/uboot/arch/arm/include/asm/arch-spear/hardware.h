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
 * Vipin Kumar, STMicroelectronics, <vipin.kumar@st.com>
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

#ifndef _ASM_ARCH_HARDWARE_H
#define _ASM_ARCH_HARDWARE_H

#define CONFIG_SYS_USBD_BASE			(0xE1100000)
#define CONFIG_SYS_PLUG_BASE			(0xE1200000)
#define CONFIG_SYS_FIFO_BASE			(0xE1000800)
#define CONFIG_SYS_SMI_BASE			(0xFC000000)
#define CONFIG_SPEAR_SYSCNTLBASE		(0xFCA00000)
#define CONFIG_SPEAR_TIMERBASE			(0xFC800000)
#define CONFIG_SPEAR_MISCBASE			(0xFCA80000)

#define CONFIG_SYS_NAND_CLE			(1 << 16)
#define CONFIG_SYS_NAND_ALE			(1 << 17)

#if defined(CONFIG_SPEAR600)
#define CONFIG_SYS_I2C_BASE			(0xD0200000)
#define CONFIG_SPEAR_FSMCBASE			(0xD1800000)

#elif defined(CONFIG_SPEAR300)
#define CONFIG_SYS_I2C_BASE			(0xD0180000)
#define CONFIG_SPEAR_FSMCBASE			(0x94000000)

#elif defined(CONFIG_SPEAR310)
#define CONFIG_SYS_I2C_BASE			(0xD0180000)
#define CONFIG_SPEAR_FSMCBASE			(0x44000000)

#undef CONFIG_SYS_NAND_CLE
#undef CONFIG_SYS_NAND_ALE
#define CONFIG_SYS_NAND_CLE			(1 << 17)
#define CONFIG_SYS_NAND_ALE			(1 << 16)

#define CONFIG_SPEAR_EMIBASE			(0x4F000000)
#define CONFIG_SPEAR_RASBASE			(0xB4000000)

#elif defined(CONFIG_SPEAR320)
#define CONFIG_SYS_I2C_BASE			(0xD0180000)
#define CONFIG_SPEAR_FSMCBASE			(0x4C000000)

#define CONFIG_SPEAR_EMIBASE			(0x40000000)
#define CONFIG_SPEAR_RASBASE			(0xB3000000)

#endif
#endif /* _ASM_ARCH_HARDWARE_H */
