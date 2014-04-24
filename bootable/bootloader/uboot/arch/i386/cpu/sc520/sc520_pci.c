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
 * Daniel Engstr�m, Omicron Ceti AB <daniel@omicron.se>.
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
 */

/* stuff specific for the sc520, but independent of implementation */

#include <common.h>
#include <pci.h>
#include <asm/io.h>
#include <asm/pci.h>
#include <asm/ic/pci.h>
#include <asm/ic/sc520.h>

static struct {
	u8 priority;
	u16 level_reg;
	u8 level_bit;
} sc520_irq[] = {
	{ SC520_IRQ0,  0, 0x01 },
	{ SC520_IRQ1,  0, 0x02 },
	{ SC520_IRQ2,  1, 0x02 },
	{ SC520_IRQ3,  0, 0x08 },
	{ SC520_IRQ4,  0, 0x10 },
	{ SC520_IRQ5,  0, 0x20 },
	{ SC520_IRQ6,  0, 0x40 },
	{ SC520_IRQ7,  0, 0x80 },

	{ SC520_IRQ8,  1, 0x01 },
	{ SC520_IRQ9,  1, 0x02 },
	{ SC520_IRQ10, 1, 0x04 },
	{ SC520_IRQ11, 1, 0x08 },
	{ SC520_IRQ12, 1, 0x10 },
	{ SC520_IRQ13, 1, 0x20 },
	{ SC520_IRQ14, 1, 0x40 },
	{ SC520_IRQ15, 1, 0x80 }
};


/* The interrupt used for PCI INTA-INTD  */
int sc520_pci_ints[15] = {
	-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1
};

/* utility function to configure a pci interrupt */
int pci_sc520_set_irq(int pci_pin, int irq)
{
	int i;
	u8 tmpb;
	u16 tmpw;

# if 1
	printf("set_irq(): map INT%c to IRQ%d\n", pci_pin + 'A', irq);
#endif
	if (irq < 0 || irq > 15) {
		return -1; /* illegal irq */
	}

	if (pci_pin < 0 || pci_pin > 15) {
		return -1; /* illegal pci int pin */
	}

	/* first disable any non-pci interrupt source that use
	 * this level */

	/* PCI interrupt mapping (A through D)*/
	for (i=0; i<=3 ;i++) {
		if (readb(&sc520_mmcr->pci_int_map[i]) == sc520_irq[irq].priority)
			writeb(SC520_IRQ_DISABLED, &sc520_mmcr->pci_int_map[i]);
	}

	/* GP IRQ interrupt mapping */
	for (i=0; i<=10 ;i++) {
		if (readb(&sc520_mmcr->gp_int_map[i]) == sc520_irq[irq].priority)
			writeb(SC520_IRQ_DISABLED, &sc520_mmcr->gp_int_map[i]);
	}

	/* Set the trigger to level */
	tmpb = readb(&sc520_mmcr->pic_mode[sc520_irq[irq].level_reg]);
	tmpb |= sc520_irq[irq].level_bit;
	writeb(tmpb, &sc520_mmcr->pic_mode[sc520_irq[irq].level_reg]);


	if (pci_pin < 4) {
		/* PCI INTA-INTD */
		/* route the interrupt */
		writeb(sc520_irq[irq].priority, &sc520_mmcr->pci_int_map[pci_pin]);
	} else {
		/* GPIRQ0-GPIRQ10 used for additional PCI INTS */
		writeb(sc520_irq[irq].priority, &sc520_mmcr->gp_int_map[pci_pin - 4]);

		/* also set the polarity in this case */
		tmpw = readw(&sc520_mmcr->intpinpol);
		tmpw |= (1 << (pci_pin-4));
		writew(tmpw, &sc520_mmcr->intpinpol);
	}

	/* register the pin */
	sc520_pci_ints[pci_pin] = irq;


	return 0; /* OK */
}

void pci_sc520_init(struct pci_controller *hose)
{
	hose->first_busno = 0;
	hose->last_busno = 0xff;
	hose->region_count = pci_set_regions(hose);

	pci_setup_type1(hose,
			SC520_REG_ADDR,
			SC520_REG_DATA);

	pci_register_hose(hose);

	hose->last_busno = pci_hose_scan(hose);

	/* enable target memory acceses on host brige */
	pci_write_config_word(0, PCI_COMMAND,
			      PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);

}
