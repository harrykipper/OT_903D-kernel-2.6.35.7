/* Copyright Statement:
 * 
 * This software/firmware and related documentation ("MediaTek Software") are 
 * protected under relevant copyright laws. The information contained herein is 
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without 
 * the prior written permission of MediaTek inc. and/or its licensors, any 
 * reproduction, modification, use or disclosure of MediaTek Software, and 
 * information contained herein, in whole or in part, shall be strictly 
 * prohibited.  
 * 
 * MediaTek Inc. (C) 2010. All rights reserved.
 * 
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES 
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") 
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON 
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER 
 * DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE SOFTWARE OF 
 * ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE 
 * MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH THIRD PARTY FOR 
 * ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT 
 * IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER 
 * LICENSES CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE 
 * RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO RECEIVER'S 
 * SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM. 
 * RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE 
 * LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 *  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, 
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO 
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */
/*
 * Copyright (c) 2008, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the 
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <boot/boot.h>
#include <boot/uart.h>
#include <msm7k/uart.h>

static unsigned uart_base = MSM_UART1_BASE;

#define uwr(v,a) writel(v, uart_base + (a))
#define urd(a) readl(uart_base + (a))

#define UART_NEED_INIT 1

void uart_init(unsigned n)
{

    switch(n) {
    case 0:
        uart_base = MSM_UART1_BASE;
        break;
    case 1:
        uart_base = MSM_UART2_BASE;
        break;
    case 2:
        uart_base = MSM_UART3_BASE;
        break;
    }

#if UART_NEED_INIT
    uwr(0x0A, UART_CR);  /* disable TX and RX */

    uwr(0x30, UART_CR);  /* reset error status */
    uwr(0x10, UART_CR);  /* reset receiver */
    uwr(0x20, UART_CR);  /* reset transmitter */

    mdelay(100);
    
        /* configuration for 19.2MHz TCXO */
    uwr(0xC0, UART_MREG);
    uwr(0xAF, UART_NREG);
    uwr(0x80, UART_DREG);
    uwr(0x19, UART_MNDREG);    

    uwr(0x10, UART_CR);  /* reset RX */
    uwr(0x20, UART_CR);  /* reset TX */
    uwr(0x30, UART_CR);  /* reset error status */
    uwr(0x40, UART_CR);  /* reset RX break */
    uwr(0x70, UART_CR);  /* rest? */
    uwr(0xD0, UART_CR);  /* reset */

    uwr(0x7BF, UART_IPR); /* stale timeout = 630 * bitrate */
    uwr(0, UART_IMR);
    uwr(115, UART_RFWR); /* RX watermark = 58 * 2 - 1 */
    uwr(10, UART_TFWR);  /* TX watermark */

    uwr(0, UART_RFWR); 
    
    uwr(UART_CSR_115200, UART_CSR);
    uwr(0, UART_IRDA);
    uwr(0x1E, UART_HCR);
//    uwr(0x7F4, UART_MR1); /* RFS/ CTS/ 500chr RFR */
    uwr(16, UART_MR1);
    uwr(0x34, UART_MR2); /* 8N1 */
    
    mdelay(100);

    uwr(0x05, UART_CR); /* enable TX & RX */
    mdelay(100);
#endif
}

int uart_getc(void)
{
    if(!(urd(UART_SR) & UART_SR_RX_READY))
        return -1;
    return urd(UART_RF);
}

void uart_putc(unsigned c)
{
    while(!(urd(UART_SR) & UART_SR_TX_READY)) ;
    uwr(c, UART_TF);
}

int uart_tx_ready(void)
{
    return urd(UART_SR) & UART_SR_TX_READY;
}


void uart_puts(const char *s)
{
    while(*s) {
        if(*s == '\n') uart_putc('\r');
        uart_putc(*s++);
    }
}

