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

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <png.h>
#include "../definitions/types.h"

typedef struct
{
    png_uint_32 width;
    png_uint_32 height;
    png_byte    colortype;
    png_bytep * data;
    png_structp handler;
    png_infop   info;
} RBBImage;

typedef struct
{
    RBBFlags flags;
      char * filename;
    RBBImage image;
} RBBWarehouse;

extern RBBWarehouse warehouse;

RBBErrors initialise();

#endif // WAREHOUSE_H
