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
/* libs/diskconfig/diskconfig.h
 *
 * Copyright 2008, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __LIBS_DISKCONFIG_H
#define __LIBS_DISKCONFIG_H

#include <stdint.h>

#define MAX_NAME_LEN                 512
#define MAX_NUM_PARTS                16

/* known partition schemes */
#define PART_SCHEME_MBR              0x1
#define PART_SCHEME_GPT              0x2

/* PC Bios partition status */
#define PC_PART_ACTIVE               0x80
#define PC_PART_NORMAL               0x0

/* Known (rather, used by us) partition types */
#define PC_PART_TYPE_LINUX           0x83
#define PC_PART_TYPE_EXTENDED        0x05

#define PC_NUM_BOOT_RECORD_PARTS     4

#define PC_EBR_LOGICAL_PART          0
#define PC_EBR_NEXT_PTR_PART         1

#define PC_BIOS_BOOT_SIG             0xAA55

#define PC_MBR_DISK_OFFSET           0
#define PC_MBR_SIZE                  512

#define PART_ACTIVE_FLAG             0x1

struct chs {
    uint8_t head;
    uint8_t sector;
    uint8_t cylinder;
} __attribute__((__packed__));

/* 16 byte pc partition descriptor that sits in MBR and EPBR.
 * Note: multi-byte entities have little-endian layout on disk */
struct pc_partition {
    uint8_t status;     /* byte  0     */
    struct chs start;   /* bytes 1-3   */
    uint8_t type;       /* byte  4     */
    struct chs end;     /* bytes 5-7   */
    uint32_t start_lba; /* bytes 8-11  */
    uint32_t len_lba;   /* bytes 12-15 */
} __attribute__((__packed__));

struct pc_boot_record {
    uint8_t code[440];                                      /* bytes 0-439   */
    uint32_t disk_sig;                                      /* bytes 440-443 */
    uint16_t pad;                                           /* bytes 444-445 */
    struct pc_partition ptable[PC_NUM_BOOT_RECORD_PARTS];   /* bytes 446-509 */
    uint16_t mbr_sig;                                       /* bytes 510-511 */
} __attribute__((__packed__));

struct part_info {
    char *name;
    uint8_t flags;
    uint8_t type;
    uint32_t len_kb;       /* in 1K-bytes */
    uint32_t start_lba;    /* the LBA where this partition begins */
};

struct disk_info {
    char *device;
    uint8_t scheme;
    int sect_size;       /* expected sector size in bytes. MUST BE POWER OF 2 */
    uint32_t skip_lba;   /* in sectors (1 unit of LBA) */
    uint32_t num_lba;    /* the size of the disk in LBA units */
    struct part_info *part_lst;
    int num_parts;
};

struct write_list {
    struct write_list *next;
    loff_t offset;
    uint32_t len;
    uint8_t data[0];
};


struct write_list *alloc_wl(uint32_t data_len);
void free_wl(struct write_list *item);
struct write_list *wlist_add(struct write_list **lst, struct write_list *item);
void wlist_free(struct write_list *lst);
int wlist_commit(int fd, struct write_list *lst, int test);

struct disk_info *load_diskconfig(const char *fn, char *path_override);
int dump_disk_config(struct disk_info *dinfo);
int apply_disk_config(struct disk_info *dinfo, int test);
char *find_part_device(struct disk_info *dinfo, const char *name);
int process_disk_config(struct disk_info *dinfo);
struct part_info *find_part(struct disk_info *dinfo, const char *name);

int write_raw_image(const char *dst, const char *src, loff_t offset, int test);

/* For MBR partition schemes */
struct write_list *config_mbr(struct disk_info *dinfo);
char *find_mbr_part(struct disk_info *dinfo, const char *name);

#endif /* __LIBS_DISKCONFIG_H */
