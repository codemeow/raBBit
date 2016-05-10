/* «RaBBit» - png-to-bb code program
 *
 *  Copyright (C) Alexey Shishkin 2016
 *
 *  This file is part of project «RaBBit».
 *
 *  Project «RaBBit» is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Project «RaBBit» is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Project «RaBBit». If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../printing/print.h"
#include "../definitions/consts.h"

void error(RBBErrors error)
{
    if (error != RBB_ERRORS_SUCCESS)
        fprintf(stderr, "%s\n", RBB_EXIT_STRINGS[error]);
    exit(error);
}

void print(char * text)
{
    printf("%s", text);
}

RBBErrors pix2hex(char ** result, RBBPixel pixel)
{
    uint32_t color = (pixel.red << 16) | (pixel.green << 8) | (pixel.blue);
    return int2hex(result, color, 6, RBB_FALSE, RBB_FALSE, RBB_TRUE);
}

RBBErrors int2hex(char ** result, int32_t value, uint8_t msize, RBBBool alloc, RBBBool up, RBBBool pre)
{
    if (msize > 8)
        msize = 8;

    const char * hexdigit[2] = {"0123456789abcdef",
                                "0123456789ABCDEF"};

    union itou
    {
        int32_t  i;
        uint32_t u;
    };

    union itou conv;
    conv.i = value;

    uint32_t pos;

    if ((alloc) &&   /* #FFFFFFFF\0 */
        (!(*result = malloc(10))))
        return RBB_ERRORS_BADALLOC;

    pos = 10;
    int size = 0;
    do
    {
        (*result)[pos--] = hexdigit[up][conv.u & 0xF];
        conv.u >>= 4;
        size++;
    }
    while (conv.u > 0);

    while (size < msize)
    {
        (*result)[pos--] = '0';
        size++;
    }

    if (pre)
    {
        (*result)[pos--] = '#';
        size += 1;
    }

    memmove(*result, *result + pos + 1, 11 - pos - 1);

    (*result)[size] = '\0';

    return RBB_ERRORS_SUCCESS;
}
