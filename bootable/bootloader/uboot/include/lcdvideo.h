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
 * MPC823 LCD and Video Controller
 * Copyright (c) 1999 Dan Malek (dmalek@jlc.net)
 */
#ifndef __LCDVIDEO_H__
#define __LCDVIDEO_H__


/* LCD Controller Configuration Register.
*/
#define LCCR_BNUM	((uint)0xfffe0000)
#define LCCR_EIEN	((uint)0x00010000)
#define LCCR_IEN	((uint)0x00008000)
#define LCCR_IRQL	((uint)0x00007000)
#define LCCR_CLKP	((uint)0x00000800)
#define LCCR_OEP	((uint)0x00000400)
#define LCCR_HSP	((uint)0x00000200)
#define LCCR_VSP	((uint)0x00000100)
#define LCCR_DP		((uint)0x00000080)
#define LCCR_BPIX	((uint)0x00000060)
#define LCCR_LBW	((uint)0x00000010)
#define LCCR_SPLT	((uint)0x00000008)
#define LCCR_CLOR	((uint)0x00000004)
#define LCCR_TFT	((uint)0x00000002)
#define LCCR_PON	((uint)0x00000001)

/* Define the bit shifts to load values into the register.
*/
#define LCDBIT(BIT, VAL)	((VAL) << (31 - BIT))

#define LCCR_BNUM_BIT	((uint)14)
#define LCCR_EIEN_BIT	((uint)15)
#define LCCR_IEN_BIT	((uint)16)
#define LCCR_IROL_BIT	((uint)19)
#define LCCR_CLKP_BIT	((uint)20)
#define LCCR_OEP_BIT	((uint)21)
#define LCCR_HSP_BIT	((uint)22)
#define LCCR_VSP_BIT	((uint)23)
#define LCCR_DP_BIT	((uint)24)
#define LCCR_BPIX_BIT	((uint)26)
#define LCCR_LBW_BIT	((uint)27)
#define LCCR_SPLT_BIT	((uint)28)
#define LCCR_CLOR_BIT	((uint)29)
#define LCCR_TFT_BIT	((uint)30)
#define LCCR_PON_BIT	((uint)31)

/* LCD Horizontal control register.
*/
#define LCHCR_BO	((uint)0x01000000)
#define LCHCR_AT	((uint)0x00e00000)
#define LCHCR_HPC	((uint)0x001ffc00)
#define LCHCR_WBL	((uint)0x000003ff)

#define LCHCR_AT_BIT	((uint)10)
#define LCHCR_HPC_BIT	((uint)21)
#define LCHCR_WBL_BIT	((uint)31)

/* LCD Vertical control register.
*/
#define LCVCR_VPW	((uint)0xf0000000)
#define LCVCR_LCD_AC	((uint)0x01e00000)
#define LCVCR_VPC	((uint)0x001ff800)
#define LCVCR_WBF	((uint)0x000003ff)

#define LCVCR_VPW_BIT	((uint)3)
#define LCVCR_LCD_AC_BIT ((uint)10)
#define LCVCR_VPC_BIT	((uint)20)

#endif /* __LCDVIDEO_H__ */
