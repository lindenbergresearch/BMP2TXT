/**
 *
 *  ██╗     ██████╗ ████████╗   ██╗  ██████╗ ███████╗    ██╗
 *  ██║     ██╔══██╗╚══██╔══╝  ██╔╝ ██╔═══██╗██╔════╝    ██║
 *  ██║     ██████╔╝   ██║    ██╔╝  ██║   ██║███████╗    ██║
 *  ██║     ██╔══██╗   ██║   ██╔╝   ██║   ██║╚════██║    ██║
 *  ███████╗██║  ██║   ██║  ██╔╝    ╚██████╔╝███████║    ██║
 *  ╚══════╝╚═╝  ╚═╝   ╚═╝  ╚═╝      ╚═════╝ ╚══════╝    ╚═╝
 *
 *
 *  Operating System I
 *
 *  Copyright 2016 Lindenberg Research Tec.
 *  All rights MIT licenced.
 *
 *  DATE			:	30/12/2016 08:06
 *  AUTHOR		    :	patrick@heapdump.com
 *
 *  DESCRIPTION	    :	Header file for image library
 *
 */

#ifndef BMP2TXT_IMAGE_H
#define BMP2TXT_IMAGE_H


#include <ntsid.h>


#define BMP_SIGNATURE       0x4D42  /* File signature of windows bmp format */
#define BMP_1_BPP           0x01    /* 1 bit per pixel */
#define BMP_SUCCESS         0x00    /* Common success case */
#define BMP_INVALID_FILE    0x01    /* File is not a bitmap */
#define BMP_OUT_OF_MEMORY   0x02    /* Memory error (OOM) */
#define BMP_IO_ERROR        0x03    /* I/O error */

#define BUFFERSIZE          4096    /* Read-buffer */

#define CHAR_COUNT          256     /* Number of possible characters (8 Bit = 256) */
#define CHAR_WIDTH          8       /* Character width in pixel */
#define CHAR_HEIGHT         16      /* Character height in pixel */
#define BYTE_PER_CHAR       16      /* Size of bitmap data per character (1 Bit 8x16 = 16 Bytes) */
#define MIN_IMAGE_SIZE      4096    /* maximal supported file-size = 256 * 16 Bytes */

#define STDOUT_PIXEL_ON     "██"    /* Printed char for pixel ON in font preview */
#define STDOUT_PIXEL_OFF    "  "    /* Printed char for pixel OFF in font preview */

/*
 * Definition of bitmap header
 * See: https://en.wikipedia.org/wiki/BMP_file_format
 */
#pragma pack(1)             /* little endian 1-byte ordered */
typedef struct {
    u_int16_t signature;    /* The file signature of the bmp format, must be 0x424D */
    u_int32_t file_size;    /* Size of bitmap file */
    u_int16_t reserved1;    /* First 2 Bytes of reserved fields */
    u_int16_t reserved2;    /* Second 2 Bytes of reserved fields */
    u_int32_t data_offset;  /* File offset to pixel array */
    u_int32_t dip_size;     /* DIP header size */
    u_int32_t width;        /* Image width (X) */
    u_int32_t height;       /* Image height (Y) */
    u_int16_t planes;       /* Planes */
    u_int16_t bpp;          /* BitsPerPixel */
    u_int32_t compression;  /* Compression type */
    u_int32_t image_size;   /* Plain image size in bytes */
} BITMAP_HEADER;


u_int8_t loadimage(const char *filename, u_int8_t **buffer);
u_int8_t *bmp2chararray(int width, int height, u_int8_t *bmpdata);
u_int8_t *flipy(const int width, const int height, u_int8_t *bmpdata);
void mdump(u_int8_t *data, u_int16_t length, u_int8_t width);
void fnt_print(u_int8_t *data, const char *string);
u_int8_t parseimage(BITMAP_HEADER *header);
void reverse(u_int8_t *buffer, u_int16_t size);

#endif /* BMP2TXT_IMAGE_H */

/**
 *
 * TERMS OF USE: MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
**/