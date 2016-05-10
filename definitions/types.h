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

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include "../xmacro/xerrors.h"

#define TIER1(NAME, MSG) RBB_ERRORS_ ## NAME,
typedef enum
{
    RBB_ERRORS_LIST
    RBB_ERRORS_LAST
} RBBErrors;
#undef TIER1

typedef enum
{
    RBB_ALIGN_UNDETERMINED,
    RBB_ALIGN_LEFT,
    RBB_ALIGN_CENTER,
    RBB_ALIGN_RIGHT
} RBBAlign;

typedef enum
{
    RBB_FALSE,
    RBB_TRUE
} RBBBool;

typedef struct
{
    RBBAlign align;
    RBBBool  optimisation;
    RBBBool  paint;
    RBBBool  doubles;
} RBBFlags;

typedef struct
{
    uint8_t alpha;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RBBPixel;

#endif // TYPES_H
