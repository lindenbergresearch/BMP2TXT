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
 *  DATE            :   30/12/2016 08:06
 *  AUTHOR          :   patrick@heapdump.com
 *
 *  DESCRIPTION     :   Image library
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "image.h"


/*!
 * @brief Reverse bit-order of a give byte
 * @param b Byte
 * @return Reversed Byte
 */
static u_int8_t revbyte(u_int8_t b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}


/*!
 * @brief Reverse a given buffer
 * @param buffer Pointer to byte buffer
 * @param size Size of buffer to reverse
 */
void reverse(u_int8_t *buffer, u_int16_t size) {
    for (int i = 0; i < size; ++i) {
        buffer[i] = revbyte(buffer[i]);
    }
}


/*!
 * @brief Converts a byte into a pseudo bit-array (array of bools)
 * @param n unsigned 8-bit int (byte)
 * @return Byte array
 */
static u_int8_t *byte2bitarray(u_int8_t n) {
    u_int8_t *buffer = malloc(8);

    for (u_int8_t i = 0; i < 8; ++i) {
        if (1 << i & n) {
            buffer[i] = 1;
        } else {
            buffer[i] = 0;
        }
    }

    return buffer;
}


/*!
 * @brief Print one scanline of 1-bit font data
 * @param data 1-bit font data
 * @param line Index of scanline
 */
static void fnt_println(const u_int8_t *data, const u_int8_t line) {
    u_int8_t *row = byte2bitarray(data[line]);

    for (int i = 0; i < CHAR_WIDTH; ++i) {
        row[i] ? printf(STDOUT_PIXEL_ON) : printf(STDOUT_PIXEL_OFF);
    }
}


/*!
 * @brief Prints  a 1-bit 8x16 bitmap to console
 * @param data Pointer to a 16 byte buffer
 * @param offset Buffer offset in bytes
 */
static void printc(u_int8_t *data, u_int16_t offset) {
    for (int i = 0; i < 16; ++i) {
        u_int8_t *row = byte2bitarray(data[i + offset]);
        printf("\n");
        for (int j = 0; j < 8; ++j) {
            row[j] ? printf("██") : printf("  ");
        }
    }
}


/*!
 * @brief Print a given String at 8x16 to console for testing font
 * @param data 1-bit font data
 * @param string Text to print
 */
void fnt_print(u_int8_t *data, const char *string) {
    printf("\n");

    /* iterate over scanlines */
    for (u_int8_t i = 0; i < CHAR_HEIGHT; ++i) {
        u_int8_t n = 0;

        /* null terminated string */
        do {
            u_int16_t offset = (u_int16_t) CHAR_HEIGHT * (u_int16_t) string[n];
            fnt_println(data + offset, i);
        } while (string[n++] != 0x00);

        printf("\n");
    }
}


/*!
 * @brief Dump memory buffer to hex output
 * @param data Pointer to data to dump
 * @param length Size in bytes
 * @param width Width before newline in characters
 */
void mdump(u_int8_t *data, u_int16_t length, u_int8_t width) {
    for (int i = 0; i < length; ++i) {
        unsigned char c;

        if ((i + 1) % width == 0) c = '\n'; else c = ' ';

        printf("%02X%c", data[i], c);

    }

    printf("----------------\n");
}


/*!
 * @brief Loads the contents of a bitmap file into buffer
 * @param filename Pointer to filename
 * @param buffer Pointer to buffer
 * @return Error No. or zero in case of success
 */
u_int8_t loadimage(const char *filename, u_int8_t **buffer) {
    FILE *fp;
    size_t size;
    u_int16_t *signature;

    /* acquire memory for buffer */
    *buffer = malloc(BUFFERSIZE);

    if (*buffer == NULL) {
        return BMP_OUT_OF_MEMORY;
    }

    /* open file */
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        return BMP_IO_ERROR;
    }

    /* get file size */
    fseek(fp, 0, SEEK_END);
    size = (size_t) ftell(fp);
    rewind(fp);

    size_t read = fread(*buffer, 1, size, fp);

    /* error on read */
    if (read == 0) {
        return BMP_IO_ERROR;
    }

    fclose(fp);

    return BMP_SUCCESS;
}


/*!
 * @brief Check BMP attributes
 * @param header Pointer to BMP header
 * @return Statuscode
 */
u_int8_t parseimage(BITMAP_HEADER *header) {
    /* check for valid file signature */
    if (header->signature != BMP_SIGNATURE) {
        return BMP_INVALID_FILE;
    }

    /* check proportion of resolution */
    if (header->width % CHAR_WIDTH != 0 || header->height % CHAR_HEIGHT != 0) {
        return BMP_INVALID_FILE;
    }

    /* check bit depth */
    if (header->bpp != BMP_1_BPP) {
        return BMP_INVALID_FILE;
    }

    /* check image size */
    if (header->image_size < MIN_IMAGE_SIZE) {
        return BMP_INVALID_FILE;
    }

    return BMP_SUCCESS;
}


/*!
 * @brief Converts plain bitmap data to indexed char array
 * @param width Bitmap width in pixel
 * @param height Bitmap height in pixel
 * @param bmpdata Pointer to plain bitmap data
 * @return Pointer to indexed char array
 */
u_int8_t *bmp2chararray(const int width, const int height, u_int8_t *bmpdata) {
    u_int8_t *buffer;
    int cx = width / 8;
    //int cy = height / 16;

    /* allocate memory for data array */
    buffer = malloc(CHAR_COUNT * BYTE_PER_CHAR);

    if (buffer == NULL) {
        return NULL;
    }

    int pos = 0;
    for (int scanline = 0; scanline < height; ++scanline) {
        for (int x = 0; x < cx; ++x) {
            int index = x + ((scanline / BYTE_PER_CHAR) * cx);
            int offset = scanline % BYTE_PER_CHAR;

            buffer[index * BYTE_PER_CHAR + offset] = bmpdata[pos++];
            //printf("x=[%3i]   scanline=[%3i]   idx=[%3i]   offset=[%3i]   position=[%4i]\n", x, scanline, index, offset, pos);
        }
    }

    return buffer;
}


/*!
 * @brief Flips bitmap data vertically
 * @param width Width of bitmap
 * @param height Height of bitmap
 * @param bmpdata Pointer to bitmap data
 * @return Flipped bitmap data
 */
u_int8_t *flipy(const int width, const int height, u_int8_t *bmpdata) {
    u_int8_t *buffer;
    int cx = width / 8;

    /* allocate memory for data array */
    buffer = malloc(width * cx);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < cx; ++x) {
            buffer[(height - 1 - y) * cx + x] = bmpdata[y * cx + x];
        }
    }

    return buffer;
}

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