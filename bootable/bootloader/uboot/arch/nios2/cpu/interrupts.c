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
 * (C) Copyright 2004, Psyent Corporation <www.psyent.com>
 * Scott McNutt <smcnutt@psyent.com>
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


#include <nios2.h>
#include <nios2-io.h>
#include <asm/types.h>
#include <asm/io.h>
#include <asm/ptrace.h>
#include <common.h>
#include <command.h>
#include <watchdog.h>
#ifdef CONFIG_STATUS_LED
#include <status_led.h>
#endif

#if defined(CONFIG_SYS_NIOS_TMRBASE) && !defined(CONFIG_SYS_NIOS_TMRIRQ)
#error CONFIG_SYS_NIOS_TMRIRQ not defined (see documentation)
#endif

/****************************************************************************/

struct	irq_action {
	interrupt_handler_t *handler;
	void *arg;
	int count;
};

static struct irq_action vecs[32];

/*************************************************************************/
volatile ulong timestamp = 0;

void reset_timer (void)
{
	nios_timer_t *tmr =(nios_timer_t *)CONFIG_SYS_NIOS_TMRBASE;

	/* From Embedded Peripherals Handbook:
	 *
	 * "When the hardware is configured with Writeable period
	 * disabled, writing to one of the period_n registers causes
	 * the counter to reset to the fixed Timeout Period specified
	 * at system generation time."
	 *
	 * Here we force a reload to prevent early timeouts from
	 * get_timer() when the interrupt period is greater than
	 * than 1 msec.
	 *
	 * Simply write to periodl with its own value to force an
	 * internal counter reload, THEN reset the timestamp.
	 */
	writel (readl (&tmr->periodl), &tmr->periodl);
	timestamp = 0;

	/* From Embedded Peripherals Handbook:
	 *
	 * "Writing to one of the period_n registers stops the internal
	 * counter, except when the hardware is configured with Start/Stop
	 * control bits off. If Start/Stop control bits is off, writing
	 * either register does not stop the counter."
	 *
	 * In order to accomodate either configuration, the control
	 * register is re-written. If the counter is stopped, it will
	 * be restarted. If it is running, the write is essentially
	 * a nop.
	 */
	writel (NIOS_TIMER_ITO | NIOS_TIMER_CONT | NIOS_TIMER_START,
			&tmr->control);

}

ulong get_timer (ulong base)
{
	WATCHDOG_RESET ();
	return (timestamp - base);
}

void set_timer (ulong t)
{
	timestamp = t;
}


/* The board must handle this interrupt if a timer is not
 * provided.
 */
#if defined(CONFIG_SYS_NIOS_TMRBASE)
void tmr_isr (void *arg)
{
	nios_timer_t *tmr = (nios_timer_t *)arg;
	/* Interrupt is cleared by writing anything to the
	 * status register.
	 */
	writel (0, &tmr->status);
	timestamp += CONFIG_SYS_NIOS_TMRMS;
#ifdef CONFIG_STATUS_LED
	status_led_tick(timestamp);
#endif
}

static void tmr_init (void)
{
	nios_timer_t *tmr =(nios_timer_t *)CONFIG_SYS_NIOS_TMRBASE;

	writel (0, &tmr->status);
	writel (0, &tmr->control);
	writel (NIOS_TIMER_STOP, &tmr->control);

#if defined(CONFIG_SYS_NIOS_TMRCNT)
	writel (CONFIG_SYS_NIOS_TMRCNT & 0xffff, &tmr->periodl);
	writel ((CONFIG_SYS_NIOS_TMRCNT >> 16) & 0xffff, &tmr->periodh);
#endif
	writel (NIOS_TIMER_ITO | NIOS_TIMER_CONT | NIOS_TIMER_START,
			&tmr->control);
	irq_install_handler (CONFIG_SYS_NIOS_TMRIRQ, tmr_isr, (void *)tmr);
}

#endif /* CONFIG_SYS_NIOS_TMRBASE */

/*************************************************************************/
int disable_interrupts (void)
{
	int val = rdctl (CTL_STATUS);
	wrctl (CTL_STATUS, val & ~STATUS_IE);
	return (val & STATUS_IE);
}

void enable_interrupts( void )
{
	int val = rdctl (CTL_STATUS);
	wrctl (CTL_STATUS, val | STATUS_IE);
}

void external_interrupt (struct pt_regs *regs)
{
	unsigned irqs;
	struct irq_action *act;

	/* Evaluate only irqs that are both enabled AND pending */
	irqs = rdctl (CTL_IENABLE) & rdctl (CTL_IPENDING);
	act = vecs;

	/* Assume (as does the Nios2 HAL) that bit 0 is highest
	 * priority. NOTE: There is ALWAYS a handler assigned
	 * (the default if no other).
	 */
	while (irqs) {
		if (irqs & 1) {
			act->handler (act->arg);
			act->count++;
		}
		irqs >>=1;
		act++;
	}
}

static void def_hdlr (void *arg)
{
	unsigned irqs = rdctl (CTL_IENABLE);

	/* Disable the individual interrupt -- with gratuitous
	 * warning.
	 */
	irqs &= ~(1 << (int)arg);
	wrctl (CTL_IENABLE, irqs);
	printf ("WARNING: Disabling unhandled interrupt: %d\n",
			(int)arg);
}

/*************************************************************************/
void irq_install_handler (int irq, interrupt_handler_t *hdlr, void *arg)
{

	int flag;
	struct irq_action *act;
	unsigned ena = rdctl (CTL_IENABLE);

	if ((irq < 0) || (irq > 31))
		return;
	act = &vecs[irq];

	flag = disable_interrupts ();
	if (hdlr) {
		act->handler = hdlr;
		act->arg = arg;
		ena |= (1 << irq);		/* enable */
	} else {
		act->handler = def_hdlr;
		act->arg = (void *)irq;
		ena &= ~(1 << irq);		/* disable */
	}
	wrctl (CTL_IENABLE, ena);
	if (flag) enable_interrupts ();
}


int interrupt_init (void)
{
	int i;

	/* Assign the default handler to all */
	for (i = 0; i < 32; i++) {
		vecs[i].handler = def_hdlr;
		vecs[i].arg = (void *)i;
		vecs[i].count = 0;
	}

#if defined(CONFIG_SYS_NIOS_TMRBASE)
	tmr_init ();
#endif

	enable_interrupts ();
	return (0);
}


/*************************************************************************/
#if defined(CONFIG_CMD_IRQ)
int do_irqinfo (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int i;
	struct irq_action *act = vecs;

	printf ("\nInterrupt-Information:\n\n");
	printf ("Nr  Routine   Arg       Count\n");
	printf ("-----------------------------\n");

	for (i=0; i<32; i++) {
		if (act->handler != def_hdlr) {
			printf ("%02d  %08lx  %08lx  %d\n",
				i,
				(ulong)act->handler,
				(ulong)act->arg,
				act->count);
		}
		act++;
	}
	printf ("\n");

	return (0);
}
#endif
