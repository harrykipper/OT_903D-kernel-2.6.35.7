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
 * (C) Copyright 2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>
#include <common.h>
#include <asm/io.h>

#include "hardware.h"
#include "i2c.h"

static void		i2c_start	(void);
static void		i2c_stop	(void);
static int		i2c_write	(u8		data);
static void		i2c_read	(u8 *		data);

static inline void	i2c_port_start  (void);
static inline void	i2c_clock	(unsigned int	val);
static inline void	i2c_data	(unsigned int	val);
static inline unsigned int
			i2c_in		(void);
static inline void	i2c_write_bit	(unsigned int	val);
static inline unsigned int
			i2c_read_bit	(void);

static inline void	i2c_udelay	(unsigned int	time);

int i2c_read_byte (
  u8 *			data,
  u8			dev,
  u8			offset)
{
  int			err = 0;

  i2c_start();

  err = ! i2c_write(dev);

  if (! err)
  {
    err = ! i2c_write(offset);
  }

  if (! err)
  {
    i2c_start();
  }

  if (! err)
  {
    err = ! i2c_write(dev | 0x01);
  }

  if (! err)
  {
    i2c_read(data);
  }

  i2c_stop();

  return ! err;
}

static inline void i2c_udelay (
  unsigned int		time)
{
  int			v;

  asm volatile("mtdec %0" : : "r" (time * ((CONFIG_SYS_BUS_CLK / 4) / 1000000)));

  do
  {
    asm volatile("isync; mfdec %0" : "=r" (v));
  } while (v >= 0);
}

  /* Low-level hardware access
   */

#define BIT_GPDATA		0x80000000
#define BIT_GPCLK		0x40000000

static inline void i2c_port_start (void)
{
  out32(REG(CPC0, GPDIR), in32(REG(CPC0, GPDIR)) & ~(BIT_GPCLK | BIT_GPDATA));
  out32(REG(CPC0, GPOUT), in32(REG(CPC0, GPOUT)) & ~(BIT_GPCLK | BIT_GPDATA));
  iobarrier_rw();

  i2c_udelay(1);
}

static inline void i2c_clock (
  unsigned int		val)
{
  if (val)
  {
    out32(REG(CPC0, GPDIR), in32(REG(CPC0, GPDIR)) & ~BIT_GPCLK);
  }
  else
  {
    out32(REG(CPC0, GPDIR), in32(REG(CPC0, GPDIR)) | BIT_GPCLK);
  }

  iobarrier_rw();

  i2c_udelay(1);
}

static inline void i2c_data (
  unsigned int		val)
{
  if (val)
  {
    out32(REG(CPC0, GPDIR), in32(REG(CPC0, GPDIR)) & ~BIT_GPDATA);
  }
  else
  {
    out32(REG(CPC0, GPDIR), in32(REG(CPC0, GPDIR)) | BIT_GPDATA);
  }

  iobarrier_rw();

  i2c_udelay(1);
}

static inline unsigned int i2c_in (void)
{
  unsigned int		val = ((in32(REG(CPC0, GPIN)) & BIT_GPDATA) != 0)?1:0;

  iobarrier_rw();

  return val;
}


  /* Protocol implementation
   */

static inline void i2c_write_bit (
  unsigned int		val)
{
  i2c_data(val);
  i2c_udelay(10);
  i2c_clock(1);
  i2c_udelay(10);
  i2c_clock(0);
  i2c_udelay(10);
}

static inline unsigned int i2c_read_bit (void)
{
  unsigned int		val;

  i2c_data(1);
  i2c_udelay(10);

  i2c_clock(1);
  i2c_udelay(10);

  val = i2c_in();

  i2c_clock(0);
  i2c_udelay(10);

  return val;
}

unsigned int i2c_reset (void)
{
  unsigned int		val;
  int i;

  i2c_port_start();

  i=0;
  do {
    i2c_udelay(10);
    i2c_clock(0);
    i2c_udelay(10);
    i2c_clock(1);
    i2c_udelay(10);
    val = i2c_in();
    i++;
  }  while ((i<9)&&(val==0));
  return (val);
}


static void i2c_start (void)
{
  i2c_data(1);
  i2c_clock(1);
  i2c_udelay(10);
  i2c_data(0);
  i2c_udelay(10);
  i2c_clock(0);
  i2c_udelay(10);
}

static void i2c_stop (void)
{
  i2c_data(0);
  i2c_udelay(10);
  i2c_clock(1);
  i2c_udelay(10);
  i2c_data(1);
  i2c_udelay(10);
}

static int i2c_write (
  u8			data)
{
  unsigned int		i;

  for (i = 0; i < 8; i++)
  {
    i2c_write_bit(data >> 7);
    data <<= 1;
  }

  return i2c_read_bit() == 0;
}

static void i2c_read (
  u8 *			data)
{
  unsigned int		i;
  u8			val = 0;

  for (i = 0; i < 8; i++)
  {
    val <<= 1;
    val |= i2c_read_bit();
  }

  *data = val;
  i2c_write_bit(1); /* NoAck */
}
