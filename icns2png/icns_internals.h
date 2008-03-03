/*
File:       icns.h
Copyright (C) 2001-2008 Mathew Eis <mathew@eisbox.net>
Copyright (C) 2002 Chenxiao Zhao <chenxiao.zhao@gmail.com>

With the exception of the limited portions mentiond, this library
is free software; you can redistribute it and/or modify it under
the terms of the GNU Library General Public License as published
by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the
Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "icns.h"

#ifndef _ICNS_INTERNALS_H_
#define	_ICNS_INTERNALS_H_

/* icns structures */

typedef struct icns_rgba_t
{
	icns_byte_t	 r;
	icns_byte_t	 g;
	icns_byte_t	 b;
	icns_byte_t	 a;
} icns_rgba_t;

typedef struct icns_argb_t
{
	icns_byte_t	 a;
	icns_byte_t	 r;
	icns_byte_t	 g;
	icns_byte_t	 b;
} icns_argb_t;

typedef struct icns_rgb_t
{
	icns_byte_t	 r;
	icns_byte_t	 g;
	icns_byte_t	 b;
} icns_rgb_t;


typedef struct icns_icon_image_info_t
{
  icns_type_t           iconType;         // type of icon (or mask)
  icns_uint32_t         iconWidth;        // width of icon in pixels
  icns_uint32_t         iconHeight;       // height of icon in pixels
  icns_uint8_t          iconChannels;     // number of channels in data
  icns_uint16_t         iconPixelDepth;   // number of bits-per-pixel
  icns_uint16_t         iconBitDepth;     // overall bit depth = iconPixelDepth * iconChannels
  icns_uint64_t         iconRawDataSize;  // bytes = width * height * depth / bits-per-pixel
} icns_icon_image_info_t;

/* icns constants */

#define			icns_byte_bits	8

/* icns macros */

/*
These functions swap the position of the alpha channel
*/


static inline icns_rgba_t ICNS_ARGB_TO_RGBA(icns_argb_t pxin) {
	icns_rgba_t pxout;
	pxout.r = pxin.r;
	pxout.g = pxin.g;
	pxout.b = pxin.b;
	pxout.a = pxin.a;
	return pxout;
}

static inline icns_argb_t ICNS_RGBA_TO_ARGB(icns_rgba_t pxin) {
	icns_argb_t pxout;
	pxout.r = pxin.r;
	pxout.g = pxin.g;
	pxout.b = pxin.b;
	pxout.a = pxin.a;
	return pxout;
}

/*
These macros will will on systems that support unaligned
accesses, as well as those that don't support it
*/

#define ICNS_READ_UNALIGNED(val, addr, type)        memcpy(&(val), (addr), sizeof(type))
#define ICNS_WRITE_UNALIGNED(addr, val, type)       memcpy((addr), &(val), sizeof(type))


/* global variables */
extern icns_bool_t gShouldPrintErrors;

/* icns function prototypes */

// icns_debug.c
void bin_print_byte(int x);
void bin_print_int(int x);

// icns_element.c
int icns_new_element_from_image(icns_image_t *imageIn,icns_type_t iconType,icns_bool_t isMask,icns_element_t **iconElementOut);

// icns_io.c
int icns_parse_family_data(unsigned long dataSize,unsigned char *data,icns_family_t **iconFamilyOut);
int icns_find_family_in_mac_resource(icns_uint32_t resDataSize, icns_byte_t *resData, icns_family_t **dataOut);
int icns_read_macbinary_resource_fork(icns_uint32_t dataSize,icns_byte_t *dataPtr,icns_type_t *dataTypeOut, icns_type_t *dataCreatorOut,icns_uint32_t *parsedResSizeOut,icns_byte_t **parsedResDataOut);
icns_bool_t icns_icns_header_check(icns_uint32_t dataSize,icns_byte_t *dataPtr);
icns_bool_t icns_rsrc_header_check(icns_uint32_t dataSize,icns_byte_t *dataPtr);
icns_bool_t icns_macbinary_header_check(icns_uint32_t dataSize,icns_byte_t *dataPtr);

// icns_jp2.c
#ifdef ICNS_OPENJPEG
void icns_opj_error_callback(const char *msg, void *client_data);
void icns_opj_warning_callback(const char *msg, void *client_data);
void icns_opj_info_callback(const char *msg, void *client_data);
#endif

// icns_utils.c
icns_icon_image_info_t icns_get_image_info_for_type(icns_type_t iconType);
icns_bool_t icns_types_equal(icns_type_t typeA,icns_type_t typeB);
icns_bool_t icns_types_not_equal(icns_type_t typeA,icns_type_t typeB);
void icns_print_err(const char *template, ...);



#endif /* _ICNS_INTERNALS_H_ */