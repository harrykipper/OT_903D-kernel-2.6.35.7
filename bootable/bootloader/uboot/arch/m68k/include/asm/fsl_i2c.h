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
 * Freescale I2C Controller
 *
 * Copyright 2006 Freescale Semiconductor, Inc.
 *
 * Based on earlier versions by Gleb Natapov <gnatapov@mrv.com>,
 * Xianghua Xiao <x.xiao@motorola.com>, Eran Liberty (liberty@freescale.com),
 * and Jeff Brown.
 * Some bits are taken from linux driver writen by adrian@humboldt.co.uk.
 *
 * This software may be used and distributed according to the
 * terms of the GNU Public License, Version 2, incorporated
 * herein by reference.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * Version 2 as published by the Free Software Foundation.
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

#ifndef _ASM_FSL_I2C_H_
#define _ASM_FSL_I2C_H_

#include <asm/types.h>

typedef struct fsl_i2c {

	u8 adr;		/* I2C slave address */
	u8 res0[3];
#define I2C_ADR		0xFE
#define I2C_ADR_SHIFT	1
#define I2C_ADR_RES	~(I2C_ADR)

	u8 fdr;		/* I2C frequency divider register */
	u8 res1[3];
#define IC2_FDR		0x3F
#define IC2_FDR_SHIFT	0
#define IC2_FDR_RES	~(IC2_FDR)

	u8 cr;		/* I2C control redister	*/
	u8 res2[3];
#define I2C_CR_MEN	0x80
#define I2C_CR_MIEN	0x40
#define I2C_CR_MSTA	0x20
#define I2C_CR_MTX	0x10
#define I2C_CR_TXAK	0x08
#define I2C_CR_RSTA	0x04
#define I2C_CR_BCST	0x01

	u8 sr;		/* I2C status register */
	u8 res3[3];
#define I2C_SR_MCF	0x80
#define I2C_SR_MAAS	0x40
#define I2C_SR_MBB	0x20
#define I2C_SR_MAL	0x10
#define I2C_SR_BCSTM	0x08
#define I2C_SR_SRW	0x04
#define I2C_SR_MIF	0x02
#define I2C_SR_RXAK	0x01

	u8 dr;		/* I2C data register */
	u8 res4[3];
#define I2C_DR		0xFF
#define I2C_DR_SHIFT	0
#define I2C_DR_RES	~(I2C_DR)
} fsl_i2c_t;

#endif	/* _ASM_I2C_H_ */
