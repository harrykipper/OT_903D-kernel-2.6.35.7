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
 * Copyright (C) 2008 The Android Open Source Project
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

#include <stdarg.h>
#include "libc_private.h"

static int hex2asc(int n)
{
    n &= 15;
    if(n > 9){
        return ('a' - 10) + n;
    } else {
        return '0' + n;
    }
}

static void xputs(const char *s, void (*xputc)(unsigned n, void *cookie), void *cookie)
{
    while (*s) {
        xputc(*s++, cookie);
    }
}

void __xprintf(const char *fmt, va_list ap,
               void (*xputc)(unsigned n, void *cookie),
               void *cookie)
{
    char scratch[16];

    for(;;){
        switch(*fmt){
        case 0:
            va_end(ap);
            return;
        case '%':
            switch(fmt[1]) {
            case 'c': {
                unsigned n = va_arg(ap, unsigned);
                xputc(n, cookie);
                fmt += 2;
                continue;
            }
            case 'h': {
                unsigned n = va_arg(ap, unsigned);
                xputc(hex2asc(n >> 12), cookie);
                xputc(hex2asc(n >> 8), cookie);
                xputc(hex2asc(n >> 4), cookie);
                xputc(hex2asc(n >> 0), cookie);
                fmt += 2;
                continue;
            }
            case 'b': {
                unsigned n = va_arg(ap, unsigned);
                xputc(hex2asc(n >> 4), cookie);
                xputc(hex2asc(n >> 0), cookie);
                fmt += 2;
                continue;
            }                
            case 'p':
            case 'X':
            case 'x': {
                unsigned n = va_arg(ap, unsigned);
                char *p = scratch + 15;
                *p = 0;
                do {
                    *--p = hex2asc(n);
                    n = n >> 4; 
                } while(n != 0);
                while(p > (scratch + 7)) *--p = '0';
                xputs(p, xputc, cookie);
                fmt += 2;
                continue;
            }
            case 'd': {
                int n = va_arg(ap, int);
                char *p = scratch + 15;
                *p = 0;
                if(n < 0) {
                    xputc('-', cookie);
                    n = -n;
                }
                do {
                    *--p = (n % 10) + '0';
                    n /= 10;
                } while(n != 0);
                xputs(p, xputc, cookie);
                fmt += 2;
                continue;
            }
            case 's': {
                char *s = va_arg(ap, char*);
                if(s == 0) s = "(null)";
                xputs(s, xputc, cookie);
                fmt += 2;
                continue;
            }
            }
            xputc(*fmt++, cookie);
            break;
        case '\n':
            xputc('\r', cookie);
        default:
            xputc(*fmt++, cookie);
        }
    }
}
