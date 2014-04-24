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

/* DO NOT EDIT THIS FILE
 * Automatically generated by generate-def-headers.xsl
 * DO NOT EDIT THIS FILE
 */

#ifndef __BFIN_DEF_ADSP_BF532_proc__
#define __BFIN_DEF_ADSP_BF532_proc__

#include "../mach-common/ADSP-EDN-core_def.h"

#include "../mach-common/ADSP-EDN-extended_def.h"

#define L1_INST_SRAM 0xFFA08000 /* 0xFFA08000 -> 0xFFA0BFFF Instruction Bank A SRAM */
#define L1_INST_SRAM_SIZE (0xFFA0BFFF - 0xFFA08000 + 1)
#define L1_INST_SRAM_END (L1_INST_SRAM + L1_INST_SRAM_SIZE)
#define L1_SRAM_SCRATCH 0xFFB00000 /* 0xFFB00000 -> 0xFFB00FFF Scratchpad SRAM */
#define L1_SRAM_SCRATCH_SIZE (0xFFB00FFF - 0xFFB00000 + 1)
#define L1_SRAM_SCRATCH_END (L1_SRAM_SCRATCH + L1_SRAM_SCRATCH_SIZE)
#define SYSMMR_BASE 0xFFC00000 /* 0xFFC00000 -> 0xFFFFFFFF MMR registers */
#define SYSMMR_BASE_SIZE (0xFFFFFFFF - 0xFFC00000 + 1)
#define SYSMMR_BASE_END (SYSMMR_BASE + SYSMMR_BASE_SIZE)

#endif /* __BFIN_DEF_ADSP_BF532_proc__ */
