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
 * Mentor USB OTG Core functionality common for both Host and Device
 * functionality.
 *
 * Copyright (c) 2008 Texas Instruments
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
 *
 * Author: Thomas Abraham t-abraham@ti.com, Texas Instruments
 */

#include <common.h>

#include "musb_core.h"
struct musb_regs *musbr;

/*
 * program the mentor core to start (enable interrupts, dma, etc.)
 */
void musb_start(void)
{
#if defined(CONFIG_MUSB_HCD)
	u8 devctl;
#endif

	/* disable all interrupts */
	writew(0, &musbr->intrtxe);
	writew(0, &musbr->intrrxe);
	writeb(0, &musbr->intrusbe);
	writeb(0, &musbr->testmode);

	/* put into basic highspeed mode and start session */
	writeb(MUSB_POWER_HSENAB, &musbr->power);
#if defined(CONFIG_MUSB_HCD)
	devctl = readb(&musbr->devctl);
	writeb(devctl | MUSB_DEVCTL_SESSION, &musbr->devctl);
#endif
}

#ifdef MUSB_NO_DYNAMIC_FIFO
# define config_fifo(dir, idx, addr)
#else
# define config_fifo(dir, idx, addr) \
	do { \
		writeb(idx, &musbr->dir##fifosz); \
		writew(fifoaddr >> 3, &musbr->dir##fifoadd); \
	} while (0)
#endif

/*
 * This function configures the endpoint configuration. The musb hcd or musb
 * device implementation can use this function to configure the endpoints
 * and set the FIFO sizes. Note: The summation of FIFO sizes of all endpoints
 * should not be more than the available FIFO size.
 *
 * epinfo	- Pointer to EP configuration table
 * cnt		- Number of entries in the EP conf table.
 */
void musb_configure_ep(struct musb_epinfo *epinfo, u8 cnt)
{
	u16 csr;
	u16 fifoaddr = 64; /* First 64 bytes of FIFO reserved for EP0 */
	u32 fifosize;
	u8  idx;

	while (cnt--) {
		/* prepare fifosize to write to register */
		fifosize = epinfo->epsize >> 3;
		idx = ffs(fifosize) - 1;

		writeb(epinfo->epnum, &musbr->index);
		if (epinfo->epdir) {
			/* Configure fifo size and fifo base address */
			config_fifo(tx, idx, fifoaddr);

			csr = readw(&musbr->txcsr);
#if defined(CONFIG_MUSB_HCD)
			/* clear the data toggle bit */
			writew(csr | MUSB_TXCSR_CLRDATATOG, &musbr->txcsr);
#endif
			/* Flush fifo if required */
			if (csr & MUSB_TXCSR_TXPKTRDY)
				writew(csr | MUSB_TXCSR_FLUSHFIFO,
					&musbr->txcsr);
		} else {
			/* Configure fifo size and fifo base address */
			config_fifo(rx, idx, fifoaddr);

			csr = readw(&musbr->rxcsr);
#if defined(CONFIG_MUSB_HCD)
			/* clear the data toggle bit */
			writew(csr | MUSB_RXCSR_CLRDATATOG, &musbr->rxcsr);
#endif
			/* Flush fifo if required */
			if (csr & MUSB_RXCSR_RXPKTRDY)
				writew(csr | MUSB_RXCSR_FLUSHFIFO,
					&musbr->rxcsr);
		}
		fifoaddr += epinfo->epsize;
		epinfo++;
	}
}

/*
 * This function writes data to endpoint fifo
 *
 * ep		- endpoint number
 * length	- number of bytes to write to FIFO
 * fifo_data	- Pointer to data buffer that contains the data to write
 */
__attribute__((weak))
void write_fifo(u8 ep, u32 length, void *fifo_data)
{
	u8  *data = (u8 *)fifo_data;

	/* select the endpoint index */
	writeb(ep, &musbr->index);

	/* write the data to the fifo */
	while (length--)
		writeb(*data++, &musbr->fifox[ep]);
}

/*
 * This function reads data from endpoint fifo
 *
 * ep           - endpoint number
 * length       - number of bytes to read from FIFO
 * fifo_data    - pointer to data buffer into which data is read
 */
__attribute__((weak))
void read_fifo(u8 ep, u32 length, void *fifo_data)
{
	u8  *data = (u8 *)fifo_data;

	/* select the endpoint index */
	writeb(ep, &musbr->index);

	/* read the data to the fifo */
	while (length--)
		*data++ = readb(&musbr->fifox[ep]);
}
