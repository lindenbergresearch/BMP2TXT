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
 *  Copyright 2015-2017 Lindenberg Research Tec.
 *  All rights MIT licenced.
 *
 *  DATE            :   27/12/2016 03:39
 *  AUTHOR          :   patrick@heapdump.com
 *
 *  DESCRIPTION     :   Bitmap to text file converter for including bitmap-fonts in Propeller SPIN
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "bmp2txt.h"
#include "image.h"


/*!
 * @brief Simple abort wrapper function
 * @param msg The error-message to display
 * @param exitcode the exit-code returned to OS
 */
void die(const char *msg, const int exitcode) {
    fprintf(stderr, "error[0x%02X]: %s\n", exitcode, msg);
    exit(exitcode);
}


/*!
 * @brief Dump 4 scanlines of all chars with a given offset to a given textfile
 * @param fp Filepointer
 * @param bitmap Font data
 * @param scanline Scanline offset
 * @return
 */
static void dump_scanlines_spin(FILE *fp, const u_int8_t *bitmap, u_int8_t scanline) {
    u_int8_t k = 0;

    fprintf(fp, "' Scanlines: 0x%02X - 0x%02X of charset 0x0 - 0xFF\n", scanline, scanline + 4);

    for (int i = 0; i < CHAR_COUNT * BYTE_PER_CHAR; i += BYTE_PER_CHAR) {
        u_int8_t c;

        if (k % 8 == 0) {
            fprintf(fp, "long ");
        }

        if (++k == 8) {
            c = '\n';
            k = 0;
        } else {
            c = ',';
        }

        fprintf(fp, "$%02X%02X%02X%02X%c", bitmap[i + scanline + 3], bitmap[i + scanline + 2], bitmap[i + scanline + 1],
                bitmap[i + scanline], c);
    }
}


/*!
 * @brief Dump font data to SPIN compatible data block in textfile
 * @param filename Name of the textfile to insert
 * @param bitmap Pointer to normalized font data
 * @return Status code
 */
u_int8_t dump_spin(const char *filename, const u_int8_t *bitmap) {
    FILE *fp = fopen(filename, "w");

    /* invalid file */
    if (fp == NULL) {
        return BMP_IO_ERROR;
    }

    fprintf(fp, "' Created by: %s %s\n", TITLE, VERSION);
    fprintf(fp, "' %s %s\n\n", VENDOR, COPYRIGHT);

    dump_scanlines_spin(fp, bitmap, 0);
    fprintf(fp, "\n\n");
    dump_scanlines_spin(fp, bitmap, 4);
    fprintf(fp, "\n\n");
    dump_scanlines_spin(fp, bitmap, 8);
    fprintf(fp, "\n\n");
    dump_scanlines_spin(fp, bitmap, 12);


    fclose(fp);

    return BMP_SUCCESS;
}


int main(int argc, char **argv) {
    u_int8_t *bitmap_data;
    char *filename;
    BITMAP_HEADER *header;
    u_int8_t *bitmap;

    /* print program info */
    printf("%s\n", TITLE);
    printf("%s\n", VERSION);
    printf("%s\n", VENDOR);
    printf("%s\n\n", COPYRIGHT);

    if (argc < 3) {
        printf("Invalid arguments.\n%s\n", USAGE);
        exit(EXIT_INVALID_ARGS);
    }

    filename = argv[1];

    if (loadimage(filename, &bitmap_data) != BMP_SUCCESS) {
        die("Unable to read bitmap file!", EXIT_INVALID_FILE);
    }

    //fnt_print(bitmap_data + 4, "Lindenberg Research Tec.");
    //dump_spin("out.txt", bitmap_data + 4);

    //exit(1);


    /* map raw data to structure */
    header = (BITMAP_HEADER *)bitmap_data;

    printf("Filename  : %s\n", filename);
    printf("ID        : 0x%04X\n", header->signature);
    printf("WxH       : %ipx x %ipx\n", abs(header->width), abs(header->height));
    printf("Chars     : %i x %i\n", abs(header->width) / 8, abs(header->height) / 16);
    printf("Size      : %i Bytes\n", header->file_size);
    printf("Offset    : %i Bytes\n", header->data_offset);
    printf("bpp       : %i\n", header->bpp);
    printf("DataSize  : %i Bytes\n\n", header->image_size);


    /* check header attributes */
    if (parseimage(header) != BMP_SUCCESS) {
        die("Invalid bitmap header!", EXIT_INVALID_HEADER);
    }

    /* mirror Y axis (default bitmap structure) */
    bitmap = flipy(abs(header->width), abs(header->height), bitmap_data + header->data_offset);

    reverse(bitmap, (u_int16_t)header->image_size);

    /* convert raw bitmap data to linear bitmap */
    bitmap = bmp2chararray(abs(header->width), abs(header->height), bitmap);

    printf("Dump font data to file: %s ... ", argv[2]);
    if (dump_spin(argv[2], bitmap) != BMP_SUCCESS) {
        printf("FAILED\n");
        die("Unable to write output file!", EXIT_INVALID_FILE);
    }
    printf("OK\n");


    if (argc > 3) {
        for (int i = 2; i < argc; ++i) {

        }
    }

    exit(EXIT_SUCCESS);
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


