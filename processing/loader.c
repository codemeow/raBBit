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

#include <stdlib.h>
#include <png.h>
#include "../definitions/consts.h"
#include "../processing/loader.h"
#include "../warehouse/warehouse.h"
#include "../printing/print.h"

RBBErrors loadimage()
{
    png_byte header[RBB_HEADER_SIZE];

    FILE * file = fopen(warehouse.filename, "rb");
    if (!file)
        error(RBB_ERRORS_CANTOPENFILE);

    if (fread(header, 1, RBB_HEADER_SIZE, file) != RBB_HEADER_SIZE)
        error(RBB_ERRORS_CANTREADFILE);

    if (png_sig_cmp(header, 0, RBB_HEADER_SIZE))
        error(RBB_ERRORS_NOTAPNG);

    warehouse.image.handler = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!warehouse.image.handler)
        error(RBB_ERRORS_PNGLIBFAILED);

    warehouse.image.info = png_create_info_struct(warehouse.image.handler);
    if (!warehouse.image.info)
        error(RBB_ERRORS_PNGLIBFAILED);

    if (setjmp(png_jmpbuf(warehouse.image.handler)))
        error(RBB_ERRORS_PNGLIBFAILED);

    png_init_io(warehouse.image.handler, file);
    png_set_sig_bytes(warehouse.image.handler, RBB_HEADER_SIZE);

    png_read_info(warehouse.image.handler,
                  warehouse.image.info);

    warehouse.image.width     = png_get_image_width (warehouse.image.handler,
                                                     warehouse.image.info);
    warehouse.image.height    = png_get_image_height(warehouse.image.handler,
                                                     warehouse.image.info);
    warehouse.image.colortype = png_get_color_type  (warehouse.image.handler,
                                                     warehouse.image.info);

    if (setjmp(png_jmpbuf(warehouse.image.handler)))
        error(RBB_ERRORS_PNGLIBFAILED);

    warehouse.image.data = malloc(sizeof(png_bytep) * warehouse.image.height);
    if (!(warehouse.image.data))
        error(RBB_ERRORS_BADALLOC);

    png_uint_32 y;
    for (y = 0; y < warehouse.image.height; y++)
    {
        warehouse.image.data[y] =
            (png_byte*) malloc(png_get_rowbytes(warehouse.image.handler,
                                                warehouse.image.info));
        if (!(warehouse.image.data[y]))
            error(RBB_ERRORS_BADALLOC);
    }

    png_read_image(warehouse.image.handler, warehouse.image.data);

    if (fclose(file))
        error(RBB_ERRORS_CANTCLOSEFILE);

    return RBB_ERRORS_SUCCESS;
}


RBBErrors cleardata()
{
    uint32_t y;
    for (y = 0; y < warehouse.image.height; y++)
        free(warehouse.image.data[y]);

    free(warehouse.image.data);

    return RBB_ERRORS_SUCCESS;
}
