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
 *  DESCRIPTION     :   Header file for converter
 *
 */

#ifndef BMP2TXT_BMP2TXT_H
#define BMP2TXT_BMP2TXT_H


#include <dtrace.h>


#define TITLE       "Bitmap to Text Converter for SPIN GFX Driver"
#define VERSION     "Version 0.0.9a"
#define VENDOR      "Copyright 2015-2017 Lindenberg Research Tec."
#define COPYRIGHT   "All rights MIT licenced."


/*
 * Exit codes passed back to OS
 */
#define EXIT_SUCCESS            0x00    /* OK, no errors */
#define EXIT_INVALID_ARGS       0x01    /* Malformed program arguments */
#define EXIT_EXCEEDED_FILESIZE  0x02    /* File exceeds maximum size */
#define EXIT_INVALID_FILE       0x03    /* Unable to open file or file could not read */
#define EXIT_INVALID_HEADER     0x05    /* invalid file header */
#define EXIT_NO_MEMORY          0x04    /* Memory allocation failed */


//unsigned char byterev(int wert);
//char *strrev(const char *string);
void die(const char *msg, const int exitcode);


#endif /* BMP2TXT_BMP2TXT_H */

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