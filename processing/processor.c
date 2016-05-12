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

#include <png.h>
#include <stdlib.h>
#include "../definitions/helpers.h"
#include "../definitions/consts.h"
#include "../processing/processor.h"
#include "../warehouse/warehouse.h"
#include "../printing/print.h"

char  COLOR_O[20];
char  COLOR_C[20];
char LBRACKET[ 5];
char RBRACKET[ 5];
char EQUALITY[ 5];
char    BLOCK[10];

void preparestrings()
{
    if (warehouse.flags.paint)
    {
        strcpy(COLOR_O,   "color");
        strcpy(COLOR_C,  "/color");
        strcpy(LBRACKET, "[");
        strcpy(RBRACKET, "]");
        strcpy(EQUALITY, "=");
    }
    else
    {
        strcpy(COLOR_O,  "");
        strcpy(COLOR_C,  "");
        strcpy(LBRACKET, "");
        strcpy(RBRACKET, "");
        strcpy(EQUALITY, "");
    }

    if (warehouse.flags.doubles)
    {
        strcpy(BLOCK, "\xE2\x96\x88\xE2\x96\x88");
    }
    else
    {
        strcpy(BLOCK, "\xE2\x96\x88");
    }
}

RBBPixel getpixel(uint32_t x, uint32_t y)
{
    RBBPixel result;

    switch (warehouse.image.colortype)
    {
    ///@todo more types
    case PNG_COLOR_TYPE_RGB :
    {
        result.alpha = UCHAR_MAX;
        result.red   = warehouse.image.data[y][x * RBB_MULTIPLIER_RGB + RBB_COLSHIFT_R];
        result.green = warehouse.image.data[y][x * RBB_MULTIPLIER_RGB + RBB_COLSHIFT_G];
        result.blue  = warehouse.image.data[y][x * RBB_MULTIPLIER_RGB + RBB_COLSHIFT_B];
        break;
    }
    case PNG_COLOR_TYPE_RGBA:
    {
        result.alpha = warehouse.image.data[y][x * RBB_MULTIPLIER_RGBA + RBB_COLSHIFT_A];
        result.red   = warehouse.image.data[y][x * RBB_MULTIPLIER_RGBA + RBB_COLSHIFT_R];
        result.green = warehouse.image.data[y][x * RBB_MULTIPLIER_RGBA + RBB_COLSHIFT_G];
        result.blue  = warehouse.image.data[y][x * RBB_MULTIPLIER_RGBA + RBB_COLSHIFT_B];
        break;
    }
    default:
        error(RBB_ERRORS_BADCOLORTYPE);
    }

    return result;
}

RBBErrors subprocessleft()
{
    uint32_t x, y;
    printf("[left]\n");
    for (y = 0; y < warehouse.image.height; y++)
    {
        RBBPixel cpixel;
        RBBPixel opixel = getpixel(0, y);
        RBBBool    same = RBB_FALSE;
        char * colstring = /* Pessimistic size */
                malloc(strlen("[color=transparent]XX[/color]") *
                       warehouse.image.width + 1);
        if (!colstring)
            error(RBB_ERRORS_BADALLOC);
        colstring[0] = '\0';

        for (x = 0; x < warehouse.image.width; x++)
        {
            char cols_s[20]; char * cols = cols_s;

            cpixel = getpixel(x, y);

            if (cpixel.alpha < RBB_TRANS_LEVEL) strcpy(cols, "transparent");
                                           else pix2hex(&cols, cpixel);

            if (RBB_PIXELCMP(cpixel, opixel) && (x != 0))
                 same = RBB_TRUE;
            else same = RBB_FALSE;

            if ((!same) && (x != 0))
            {
                sprintf(colstring + strlen(colstring), "%s%s%s",
                        LBRACKET, COLOR_C, RBRACKET);
                printf("%s", colstring);
                colstring[0] = '\0';
            }

            if (!same)
            {
                if (warehouse.flags.paint)
                    sprintf(colstring + strlen(colstring), "%s%s%s%s%s%s",
                            LBRACKET, COLOR_O, EQUALITY, cols, RBRACKET, BLOCK);
                else
                    sprintf(colstring + strlen(colstring), "%s%s%s%s%s",
                            LBRACKET, COLOR_O, EQUALITY,       RBRACKET, BLOCK);
            }
                else strcat(colstring, BLOCK);

            opixel = cpixel;
        }

        sprintf(colstring + strlen(colstring), "%s%s%s",
                LBRACKET, COLOR_C, RBRACKET);
        if (!(warehouse.flags.optimisation))
            printf("%s", colstring);
        else if ((cpixel.alpha == RBB_TRANS_LEVEL))
            printf("%s", colstring);

        printf("\n");
    }
    printf("[/left]\n");

    return RBB_ERRORS_SUCCESS;
}

RBBErrors subprocesscenter()
{
    uint32_t x, y;
    printf("[center]\n");

    uint32_t * xlimit = calloc(warehouse.image.height, sizeof(uint32_t));
    if (!xlimit)
        error(RBB_ERRORS_BADALLOC);

    if (warehouse.flags.optimisation)
    {
        for (y = 0; y < warehouse.image.height; y++)
        {
            for (x = 0; x < warehouse.image.width / 2; x++)
            {
                RBBPixel lpixel = getpixel(x, y);
                RBBPixel rpixel = getpixel(warehouse.image.width - x - 1, y);
                if ((lpixel.alpha < RBB_TRANS_LEVEL) &&
                    (rpixel.alpha < RBB_TRANS_LEVEL))
                    xlimit[y]++;
                else
                    break;
            }
        }
    }

    for (y = 0; y < warehouse.image.height; y++)
    {
        RBBPixel cpixel;
        RBBPixel opixel = getpixel(0, y);
        RBBBool    same = RBB_FALSE;
        RBBBool    used = RBB_FALSE;
        char * colstring = /* Pessimistic size */
                malloc(strlen("[color=transparent]XX[/color]") *
                       warehouse.image.width + 1);
        if (!colstring)
            error(RBB_ERRORS_BADALLOC);
        colstring[0] = '\0';

        for (x = xlimit[y]; x < (warehouse.image.width - xlimit[y]); x++)
        {
            used = RBB_TRUE;
            char cols_s[20]; char * cols = cols_s;

            cpixel = getpixel(x, y);

            if (cpixel.alpha < RBB_TRANS_LEVEL) strcpy(cols, "transparent");
                                           else pix2hex(&cols, cpixel);

            if (RBB_PIXELCMP(cpixel, opixel) && (x != xlimit[y]))
                 same = RBB_TRUE;
            else same = RBB_FALSE;

            if ((!same) && (x != xlimit[y]))
            {
                sprintf(colstring + strlen(colstring), "%s%s%s",
                        LBRACKET, COLOR_C, RBRACKET);                
                printf("%s", colstring);
                colstring[0] = '\0';
            }

            if (!same)
            {
                if (warehouse.flags.paint)
                    sprintf(colstring + strlen(colstring), "%s%s%s%s%s%s",
                            LBRACKET, COLOR_O, EQUALITY, cols, RBRACKET, BLOCK);
                else
                    sprintf(colstring + strlen(colstring), "%s%s%s%s%s",
                            LBRACKET, COLOR_O, EQUALITY,       RBRACKET, BLOCK);
            }
                else strcat(colstring, BLOCK);

            opixel = cpixel;
        }

        if (used)
        {
            sprintf(colstring + strlen(colstring), "%s%s%s",
                    LBRACKET, COLOR_C, RBRACKET);
            printf("%s", colstring);
        }

        printf("\n");
    }
    printf("[/center]\n");

    free(xlimit);

    return RBB_ERRORS_SUCCESS;
}

RBBErrors subprocessright()
{
    uint32_t x, y;
    printf("[right]\n");
    for (y = 0; y < warehouse.image.height; y++)
    {
        RBBPixel cpixel;
        RBBPixel opixel = getpixel(0, y);
        RBBBool    same = RBB_FALSE;
        RBBBool   first = RBB_TRUE;
        uint32_t startx = 0;
        char * colstring = /* Pessimistic size */
                malloc(strlen("[color=transparent]XX[/color]") *
                       warehouse.image.width + 1);
        if (!colstring)
            error(RBB_ERRORS_BADALLOC);
        colstring[0] = '\0';

        for (x = startx; x < warehouse.image.width; x++)
        {
            char cols_s[20]; char * cols = cols_s;

            cpixel = getpixel(x, y);

            if ((warehouse.flags.optimisation  ) &&
                (cpixel.alpha < RBB_TRANS_LEVEL) &&
                (first))
            {
                startx++;
                continue;
            }
                    else first = RBB_FALSE;

            if (cpixel.alpha < RBB_TRANS_LEVEL) strcpy(cols, "transparent");
                                           else pix2hex(&cols, cpixel);

            if (RBB_PIXELCMP(cpixel, opixel) && (x != 0))
                 same = RBB_TRUE;
            else same = RBB_FALSE;

            if ((!same) && (x != startx))
            {
                sprintf(colstring + strlen(colstring), "%s%s%s",
                        LBRACKET, COLOR_C, RBRACKET);
                printf("%s", colstring);
                colstring[0] = '\0';
            }

            if (!same)
            {
                if (warehouse.flags.paint)
                    sprintf(colstring + strlen(colstring), "%s%s%s%s%s%s",
                            LBRACKET, COLOR_O, EQUALITY, cols, RBRACKET, BLOCK);
                else
                    sprintf(colstring + strlen(colstring), "%s%s%s%s%s",
                            LBRACKET, COLOR_O, EQUALITY,       RBRACKET, BLOCK);
            }
                else strcat(colstring, BLOCK);

            opixel = cpixel;
        }

        if (startx != warehouse.image.width)
            sprintf(colstring + strlen(colstring), "%s%s%s",
                    LBRACKET, COLOR_C, RBRACKET);
        printf("%s\n", colstring);
    }
    printf("[/right]\n");

    return RBB_ERRORS_SUCCESS;
}

RBBErrors processdata()
{
    preparestrings();

    switch (warehouse.flags.align)
    {
    case RBB_ALIGN_LEFT   : RBB_CHECK(subprocessleft  ()); break;
    case RBB_ALIGN_CENTER : RBB_CHECK(subprocesscenter()); break;
    case RBB_ALIGN_RIGHT  : RBB_CHECK(subprocessright ()); break;
    default:
        error(RBB_ERRORS_NOALIGN);
    }

    return RBB_ERRORS_SUCCESS;
}
