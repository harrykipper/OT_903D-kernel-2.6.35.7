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
 * Copyright (C) 2007 Nobuhiro Iwamatsu
 * Copyright (C) 2008 Yusuke Goda <goda.yusuke@renesas.com>
 *
 * u-boot/board/r7780mp/r7780mp.h
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

#ifndef _BOARD_R7780MP_R7780MP_H_
#define _BOARD_R7780MP_R7780MP_H_

/* R7780MP's FPGA register map */
#define FPGA_BASE          0xa4000000
#define FPGA_IRLMSK        (FPGA_BASE + 0x00)
#define FPGA_IRLMON        (FPGA_BASE + 0x02)
#define FPGA_IRLPRI1       (FPGA_BASE + 0x04)
#define FPGA_IRLPRI2       (FPGA_BASE + 0x06)
#define FPGA_IRLPRI3       (FPGA_BASE + 0x08)
#define FPGA_IRLPRI4       (FPGA_BASE + 0x0A)
#define FPGA_RSTCTL        (FPGA_BASE + 0x0C)
#define FPGA_PCIBD         (FPGA_BASE + 0x0E)
#define FPGA_PCICD         (FPGA_BASE + 0x10)
#define FPGA_EXTGIO        (FPGA_BASE + 0x16)
#define FPGA_IVDRMON       (FPGA_BASE + 0x18)
#define FPGA_IVDRCR        (FPGA_BASE + 0x1A)
#define FPGA_OBLED         (FPGA_BASE + 0x1C)
#define FPGA_OBSW          (FPGA_BASE + 0x1E)
#define FPGA_TPCTL         (FPGA_BASE + 0x100)
#define FPGA_TPDCKCTL      (FPGA_BASE + 0x102)
#define FPGA_TPCLR         (FPGA_BASE + 0x104)
#define FPGA_TPXPOS        (FPGA_BASE + 0x106)
#define FPGA_TPYPOS        (FPGA_BASE + 0x108)
#define FPGA_DBSW          (FPGA_BASE + 0x200)
#define FPGA_VERSION       (FPGA_BASE + 0x700)
#define FPGA_CFCTL         (FPGA_BASE + 0x300)
#define FPGA_CFPOW         (FPGA_BASE + 0x302)
#define FPGA_CFCDINTCLR    (FPGA_BASE + 0x304)
#define FPGA_PMR           (FPGA_BASE + 0x900)

#endif /* _BOARD_R7780RP_R7780RP_H_ */
