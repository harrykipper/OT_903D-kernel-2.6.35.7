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
 * This file is part of UBIFS.
 *
 * Copyright (C) 2006-2008 Nokia Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Authors: Adrian Hunter
 *          Artem Bityutskiy (Битюцкий Артём)
 */

/*
 * This file implements commit-related functionality of the LEB properties
 * subsystem.
 */

#include "crc16.h"
#include "ubifs.h"

/**
 * free_obsolete_cnodes - free obsolete cnodes for commit end.
 * @c: UBIFS file-system description object
 */
static void free_obsolete_cnodes(struct ubifs_info *c)
{
	struct ubifs_cnode *cnode, *cnext;

	cnext = c->lpt_cnext;
	if (!cnext)
		return;
	do {
		cnode = cnext;
		cnext = cnode->cnext;
		if (test_bit(OBSOLETE_CNODE, &cnode->flags))
			kfree(cnode);
		else
			cnode->cnext = NULL;
	} while (cnext != c->lpt_cnext);
	c->lpt_cnext = NULL;
}

/**
 * first_nnode - find the first nnode in memory.
 * @c: UBIFS file-system description object
 * @hght: height of tree where nnode found is returned here
 *
 * This function returns a pointer to the nnode found or %NULL if no nnode is
 * found. This function is a helper to 'ubifs_lpt_free()'.
 */
static struct ubifs_nnode *first_nnode(struct ubifs_info *c, int *hght)
{
	struct ubifs_nnode *nnode;
	int h, i, found;

	nnode = c->nroot;
	*hght = 0;
	if (!nnode)
		return NULL;
	for (h = 1; h < c->lpt_hght; h++) {
		found = 0;
		for (i = 0; i < UBIFS_LPT_FANOUT; i++) {
			if (nnode->nbranch[i].nnode) {
				found = 1;
				nnode = nnode->nbranch[i].nnode;
				*hght = h;
				break;
			}
		}
		if (!found)
			break;
	}
	return nnode;
}

/**
 * next_nnode - find the next nnode in memory.
 * @c: UBIFS file-system description object
 * @nnode: nnode from which to start.
 * @hght: height of tree where nnode is, is passed and returned here
 *
 * This function returns a pointer to the nnode found or %NULL if no nnode is
 * found. This function is a helper to 'ubifs_lpt_free()'.
 */
static struct ubifs_nnode *next_nnode(struct ubifs_info *c,
				      struct ubifs_nnode *nnode, int *hght)
{
	struct ubifs_nnode *parent;
	int iip, h, i, found;

	parent = nnode->parent;
	if (!parent)
		return NULL;
	if (nnode->iip == UBIFS_LPT_FANOUT - 1) {
		*hght -= 1;
		return parent;
	}
	for (iip = nnode->iip + 1; iip < UBIFS_LPT_FANOUT; iip++) {
		nnode = parent->nbranch[iip].nnode;
		if (nnode)
			break;
	}
	if (!nnode) {
		*hght -= 1;
		return parent;
	}
	for (h = *hght + 1; h < c->lpt_hght; h++) {
		found = 0;
		for (i = 0; i < UBIFS_LPT_FANOUT; i++) {
			if (nnode->nbranch[i].nnode) {
				found = 1;
				nnode = nnode->nbranch[i].nnode;
				*hght = h;
				break;
			}
		}
		if (!found)
			break;
	}
	return nnode;
}

/**
 * ubifs_lpt_free - free resources owned by the LPT.
 * @c: UBIFS file-system description object
 * @wr_only: free only resources used for writing
 */
void ubifs_lpt_free(struct ubifs_info *c, int wr_only)
{
	struct ubifs_nnode *nnode;
	int i, hght;

	/* Free write-only things first */

	free_obsolete_cnodes(c); /* Leftover from a failed commit */

	vfree(c->ltab_cmt);
	c->ltab_cmt = NULL;
	vfree(c->lpt_buf);
	c->lpt_buf = NULL;
	kfree(c->lsave);
	c->lsave = NULL;

	if (wr_only)
		return;

	/* Now free the rest */

	nnode = first_nnode(c, &hght);
	while (nnode) {
		for (i = 0; i < UBIFS_LPT_FANOUT; i++)
			kfree(nnode->nbranch[i].nnode);
		nnode = next_nnode(c, nnode, &hght);
	}
	for (i = 0; i < LPROPS_HEAP_CNT; i++)
		kfree(c->lpt_heap[i].arr);
	kfree(c->dirty_idx.arr);
	kfree(c->nroot);
	vfree(c->ltab);
	kfree(c->lpt_nod_buf);
}
