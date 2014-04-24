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
 * (C) Copyright 2000-2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2001 Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Andreas Heppel <aheppel@sysgo.de>

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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#if defined(CONFIG_I2C_ENV_EEPROM_BUS)
#include <i2c.h>
#endif

#ifdef CONFIG_ENV_OFFSET_REDUND
#define ACTIVE_FLAG   1
#define OBSOLETE_FLAG 0
#endif

DECLARE_GLOBAL_DATA_PTR;

env_t *env_ptr = NULL;

char * env_name_spec = "EEPROM";
int env_eeprom_bus = -1;

static int eeprom_bus_read (unsigned dev_addr, unsigned offset, uchar *buffer,
				unsigned cnt)
{
	int rcode;
#if defined(CONFIG_I2C_ENV_EEPROM_BUS)
	int old_bus = i2c_get_bus_num();

	if (gd->flags & GD_FLG_RELOC) {
		if (env_eeprom_bus == -1) {
			I2C_MUX_DEVICE *dev = NULL;
			dev = i2c_mux_ident_muxstring(
				(uchar *)CONFIG_I2C_ENV_EEPROM_BUS);
			if (dev != NULL) {
				env_eeprom_bus = dev->busid;
			} else
				printf ("error adding env eeprom bus.\n");
		}
		if (old_bus != env_eeprom_bus) {
			i2c_set_bus_num(env_eeprom_bus);
			old_bus = env_eeprom_bus;
		}
	} else {
		rcode = i2c_mux_ident_muxstring_f(
				(uchar *)CONFIG_I2C_ENV_EEPROM_BUS);
	}
#endif

	rcode = eeprom_read (dev_addr, offset, buffer, cnt);
#if defined(CONFIG_I2C_ENV_EEPROM_BUS)
	if (old_bus != env_eeprom_bus)
		i2c_set_bus_num(old_bus);
#endif
	return rcode;
}

static int eeprom_bus_write (unsigned dev_addr, unsigned offset, uchar *buffer,
				unsigned cnt)
{
	int rcode;
#if defined(CONFIG_I2C_ENV_EEPROM_BUS)
	int old_bus = i2c_get_bus_num();

	rcode = i2c_mux_ident_muxstring_f((uchar *)CONFIG_I2C_ENV_EEPROM_BUS);
#endif
	rcode = eeprom_write (dev_addr, offset, buffer, cnt);
#if defined(CONFIG_I2C_ENV_EEPROM_BUS)
	i2c_set_bus_num(old_bus);
#endif
	return rcode;
}

uchar env_get_char_spec (int index)
{
	uchar c;
	unsigned int off;
	off = CONFIG_ENV_OFFSET;
#ifdef CONFIG_ENV_OFFSET_REDUND
	if (gd->env_valid == 2)
		off = CONFIG_ENV_OFFSET_REDUND;
#endif

	eeprom_bus_read (CONFIG_SYS_DEF_EEPROM_ADDR,
		     off + index + offsetof(env_t,data),
		     &c, 1);

	return (c);
}

void env_relocate_spec (void)
{
	unsigned int off = CONFIG_ENV_OFFSET;
#ifdef CONFIG_ENV_OFFSET_REDUND
	if (gd->env_valid == 2)
		off = CONFIG_ENV_OFFSET_REDUND;
#endif
	eeprom_bus_read (CONFIG_SYS_DEF_EEPROM_ADDR,
		     off,
		     (uchar*)env_ptr,
		     CONFIG_ENV_SIZE);
}

int saveenv(void)
{
	int rc;
	unsigned int off = CONFIG_ENV_OFFSET;
#ifdef CONFIG_ENV_OFFSET_REDUND
	unsigned int off_red = CONFIG_ENV_OFFSET_REDUND;
	char flag_obsolete = OBSOLETE_FLAG;
	if (gd->env_valid == 1) {
		off = CONFIG_ENV_OFFSET_REDUND;
		off_red = CONFIG_ENV_OFFSET;
	}

	env_ptr->flags = ACTIVE_FLAG;
#endif

	rc = eeprom_bus_write (CONFIG_SYS_DEF_EEPROM_ADDR,
			     off,
			     (uchar *)env_ptr,
			     CONFIG_ENV_SIZE);

#ifdef CONFIG_ENV_OFFSET_REDUND
	if (rc == 0) {
		eeprom_bus_write (CONFIG_SYS_DEF_EEPROM_ADDR,
				  off_red + offsetof(env_t,flags),
				  (uchar *)&flag_obsolete,
				  1);
		if (gd->env_valid == 1)
			gd->env_valid = 2;
		else
			gd->env_valid = 1;

	}
#endif

	return rc;
}

/************************************************************************
 * Initialize Environment use
 *
 * We are still running from ROM, so data use is limited
 * Use a (moderately small) buffer on the stack
 */

#ifdef CONFIG_ENV_OFFSET_REDUND
int env_init(void)
{
	ulong len;
	ulong crc[2], crc_tmp;
	unsigned int off, off_env[2];
	uchar buf[64];
	int crc_ok[2] = {0,0};
	unsigned char flags[2];
	int i;

	eeprom_init ();	/* prepare for EEPROM read/write */

	off_env[0] = CONFIG_ENV_OFFSET;
	off_env[1] = CONFIG_ENV_OFFSET_REDUND;

	for (i = 0; i < 2; i++) {
		/* read CRC */
		eeprom_bus_read (CONFIG_SYS_DEF_EEPROM_ADDR,
			off_env[i] + offsetof(env_t,crc),
			(uchar *)&crc[i], sizeof(ulong));
		/* read FLAGS */
		eeprom_bus_read (CONFIG_SYS_DEF_EEPROM_ADDR,
			off_env[i] + offsetof(env_t,flags),
			(uchar *)&flags[i], sizeof(uchar));

		crc_tmp= 0;
		len = ENV_SIZE;
		off = off_env[i] + offsetof(env_t,data);
		while (len > 0) {
			int n = (len > sizeof(buf)) ? sizeof(buf) : len;

			eeprom_bus_read (CONFIG_SYS_DEF_EEPROM_ADDR, off,
				buf, n);

			crc_tmp = crc32 (crc_tmp, buf, n);
			len -= n;
			off += n;
		}
		if (crc_tmp == crc[i])
			crc_ok[i] = 1;
	}

	if (!crc_ok[0] && !crc_ok[1]) {
		gd->env_addr  = 0;
		gd->env_valid = 0;

		return 0;
	} else if (crc_ok[0] && !crc_ok[1]) {
		gd->env_valid = 1;
	}
	else if (!crc_ok[0] && crc_ok[1]) {
		gd->env_valid = 2;
	} else {
		/* both ok - check serial */
		if (flags[0] == ACTIVE_FLAG && flags[1] == OBSOLETE_FLAG)
			gd->env_valid = 1;
		else if (flags[0] == OBSOLETE_FLAG && flags[1] == ACTIVE_FLAG)
			gd->env_valid = 2;
		else if (flags[0] == 0xFF && flags[1] == 0)
			gd->env_valid = 2;
		else if(flags[1] == 0xFF && flags[0] == 0)
			gd->env_valid = 1;
		else /* flags are equal - almost impossible */
			gd->env_valid = 1;
	}

	if (gd->env_valid == 2)
		gd->env_addr = off_env[1] + offsetof(env_t,data);
	else if (gd->env_valid == 1)
		gd->env_addr = off_env[0] + offsetof(env_t,data);

	return (0);
}
#else
int env_init(void)
{
	ulong crc, len, new;
	unsigned off;
	uchar buf[64];

	eeprom_init ();	/* prepare for EEPROM read/write */

	/* read old CRC */
	eeprom_bus_read (CONFIG_SYS_DEF_EEPROM_ADDR,
		     CONFIG_ENV_OFFSET+offsetof(env_t,crc),
		     (uchar *)&crc, sizeof(ulong));

	new = 0;
	len = ENV_SIZE;
	off = offsetof(env_t,data);
	while (len > 0) {
		int n = (len > sizeof(buf)) ? sizeof(buf) : len;

		eeprom_bus_read (CONFIG_SYS_DEF_EEPROM_ADDR,
				CONFIG_ENV_OFFSET + off, buf, n);
		new = crc32 (new, buf, n);
		len -= n;
		off += n;
	}

	if (crc == new) {
		gd->env_addr  = offsetof(env_t,data);
		gd->env_valid = 1;
	} else {
		gd->env_addr  = 0;
		gd->env_valid = 0;
	}

	return (0);
}
#endif
