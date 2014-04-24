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
 * (C) Copyright 2000
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */
/* ide.c - ide support functions */


#include <common.h>

#ifdef CONFIG_CMD_IDE
#include <ata.h>
#include <ide.h>
#include <pci.h>

#define IT8212_PCI_CpuCONTROL		0x5e
#define IT8212_PCI_PciModeCONTROL	0x50
#define IT8212_PCI_IdeIoCONFIG		0x40
#define IT8212_PCI_IdeBusSkewCONTROL	0x4c
#define IT8212_PCI_IdeDrivingCURRENT	0x42

extern ulong ide_bus_offset[CONFIG_SYS_IDE_MAXBUS];
extern struct pci_controller hose;

int ide_preinit (void)
{
	int status;
	pci_dev_t devbusfn;
	int l;

	status = 1;
	for (l = 0; l < CONFIG_SYS_IDE_MAXBUS; l++) {
		ide_bus_offset[l] = -ATA_STATUS;
	}
	devbusfn = pci_find_device(PCI_VENDOR_ID_CMD, PCI_DEVICE_ID_SII_680, 0);
	if (devbusfn == -1)
		devbusfn = pci_find_device(PCI_VENDOR_ID_ITE,PCI_DEVICE_ID_ITE_8212,0);
	if (devbusfn != -1) {
		u32 ide_bus_offset32;

		status = 0;

		pci_read_config_dword (devbusfn, PCI_BASE_ADDRESS_0,
							   &ide_bus_offset32);
		ide_bus_offset[0] = ide_bus_offset32 & 0xfffffffe;
		ide_bus_offset[0] = pci_hose_bus_to_phys(&hose,
							 ide_bus_offset[0] & 0xfffffffe,
							 PCI_REGION_IO);
		pci_read_config_dword(devbusfn, PCI_BASE_ADDRESS_2,
				      (u32 *) &ide_bus_offset[1]);
		ide_bus_offset[1] &= 0xfffffffe;
		ide_bus_offset[1] = pci_hose_bus_to_phys(&hose,
							 ide_bus_offset[1] & 0xfffffffe,
							 PCI_REGION_IO);
	}

	if (pci_find_device (PCI_VENDOR_ID_ITE, PCI_DEVICE_ID_ITE_8212, 0) != -1) {
		pci_write_config_byte(devbusfn, IT8212_PCI_CpuCONTROL, 0x01);
		pci_write_config_byte(devbusfn, IT8212_PCI_PciModeCONTROL, 0x00);
		pci_write_config_word(devbusfn, PCI_COMMAND, 0x0047);
#ifdef CONFIG_IT8212_SECONDARY_ENABLE
		pci_write_config_word(devbusfn, IT8212_PCI_IdeIoCONFIG, 0xA0F3);
#else
		pci_write_config_word(devbusfn, IT8212_PCI_IdeIoCONFIG, 0x8031);
#endif
		pci_write_config_dword(devbusfn, IT8212_PCI_IdeBusSkewCONTROL, 0x02040204);
/* __LS_COMMENT__ BUFFALO changed 2004.11.10  changed for EMI */
		pci_write_config_byte(devbusfn, IT8212_PCI_IdeDrivingCURRENT, 0x36); /* 10mA */
/*		pci_write_config_byte(dev, IT8212_PCI_IdeDrivingCURRENT, 0x09); */ /* 4mA */
/*		pci_write_config_byte(dev, IT8212_PCI_IdeDrivingCURRENT, 0x12); */ /* 6mA */
/*		pci_write_config_byte(dev, IT8212_PCI_IdeDrivingCURRENT, 0x24); */ /* 6mA,2mA */
/*		pci_write_config_byte(dev, IT8212_PCI_IdeDrivingCURRENT, 0x2D); */ /* 8mA,4mA */
		pci_write_config_byte(devbusfn, PCI_LATENCY_TIMER, 0x00);
	}

	return (status);
}

void ide_set_reset (int flag) {
	return;
}

#endif /* CONFIG_CMD_IDE */
