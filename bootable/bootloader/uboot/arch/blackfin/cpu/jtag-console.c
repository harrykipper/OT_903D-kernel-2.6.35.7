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
 * jtag-console.c - console driver over Blackfin JTAG
 *
 * Copyright (c) 2008 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <common.h>
#include <stdio_dev.h>
#include <asm/blackfin.h>

#ifndef CONFIG_JTAG_CONSOLE_TIMEOUT
# define CONFIG_JTAG_CONSOLE_TIMEOUT 500
#endif

/* The Blackfin tends to be much much faster than the JTAG hardware. */
static void jtag_write_emudat(uint32_t emudat)
{
	static bool overflowed = false;
	ulong timeout = get_timer(0) + CONFIG_JTAG_CONSOLE_TIMEOUT;
	while (bfin_read_DBGSTAT() & 0x1) {
		if (overflowed)
			return;
		if (timeout < get_timer(0))
			overflowed = true;
	}
	overflowed = false;
	__asm__ __volatile__("emudat = %0;" : : "d"(emudat));
}
/* Transmit a buffer.  The format is:
 * [32bit length][actual data]
 */
static void jtag_send(const char *c, uint32_t len)
{
	uint32_t i;

	if (len == 0)
		return;

	/* First send the length */
	jtag_write_emudat(len);

	/* Then send the data */
	for (i = 0; i < len; i += 4)
		jtag_write_emudat((c[i] << 0) | (c[i+1] << 8) | (c[i+2] << 16) | (c[i+3] << 24));
}
static void jtag_putc(const char c)
{
	jtag_send(&c, 1);
}
static void jtag_puts(const char *s)
{
	jtag_send(s, strlen(s));
}

static size_t inbound_len, leftovers_len;

/* Lower layers want to know when jtag has data */
static int jtag_tstc_dbg(void)
{
	return (bfin_read_DBGSTAT() & 0x2);
}

/* Higher layers want to know when any data is available */
static int jtag_tstc(void)
{
	return jtag_tstc_dbg() || leftovers_len;
}

/* Receive a buffer.  The format is:
 * [32bit length][actual data]
 */
static uint32_t leftovers;
static int jtag_getc(void)
{
	int ret;
	uint32_t emudat;

	/* see if any data is left over */
	if (leftovers_len) {
		--leftovers_len;
		ret = leftovers & 0xff;
		leftovers >>= 8;
		return ret;
	}

	/* wait for new data ! */
	while (!jtag_tstc_dbg())
		continue;
	__asm__("%0 = emudat;" : "=d"(emudat));

	if (inbound_len == 0) {
		/* grab the length */
		inbound_len = emudat;
	} else {
		/* store the bytes */
		leftovers_len = min(4, inbound_len);
		inbound_len -= leftovers_len;
		leftovers = emudat;
	}

	return jtag_getc();
}

int drv_jtag_console_init(void)
{
	struct stdio_dev dev;
	int ret;

	memset(&dev, 0x00, sizeof(dev));
	strcpy(dev.name, "jtag");
	dev.flags = DEV_FLAGS_OUTPUT | DEV_FLAGS_INPUT | DEV_FLAGS_SYSTEM;
	dev.putc = jtag_putc;
	dev.puts = jtag_puts;
	dev.tstc = jtag_tstc;
	dev.getc = jtag_getc;

	ret = stdio_register(&dev);
	return (ret == 0 ? 1 : ret);
}

#ifdef CONFIG_UART_CONSOLE_IS_JTAG
/* Since the JTAG is always available (at power on), allow it to fake a UART */
void serial_set_baud(uint32_t baud) {}
void serial_setbrg(void)            {}
int serial_init(void)               { return 0; }
void serial_putc(const char c)      __attribute__((alias("jtag_putc")));
void serial_puts(const char *s)     __attribute__((alias("jtag_puts")));
int serial_tstc(void)               __attribute__((alias("jtag_tstc")));
int serial_getc(void)               __attribute__((alias("jtag_getc")));
#endif
