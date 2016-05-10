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

#include <stdint.h>
#include <string.h>
#include "../definitions/helpers.h"
#include "../processing/parameters.h"
#include "../warehouse/warehouse.h"
#include "../printing/print.h"
#include "../xmacro/xparameters.h"

RBBErrors parameterh()
/* Help */
{
    // print auto-generated help
    print("Usage: rbb [options] file\n"
          "Options:\n"
#         define TIER1(SHORT, LONG, CALLBACK, MSG) \
          " -" #SHORT ", --" #LONG " " MSG "\n"
          RBB_PARAMETERS_LIST
#         undef TIER1
          );

    error(RBB_ERRORS_SUCCESS);
    /* Pointless, shut up, compiler */
    return RBB_ERRORS_SUCCESS;
}


RBBErrors parameterl()
/* Left align */
{
    if (warehouse.flags.align == RBB_ALIGN_UNDETERMINED)
        warehouse.flags.align =  RBB_ALIGN_LEFT;
    else
        error(RBB_ERRORS_BADARGUMENTS);

    return RBB_ERRORS_SUCCESS;
}


RBBErrors parameterc()
/* Center align */
{
    if (warehouse.flags.align == RBB_ALIGN_UNDETERMINED)
        warehouse.flags.align =  RBB_ALIGN_CENTER;
    else
        error(RBB_ERRORS_BADARGUMENTS);

    return RBB_ERRORS_SUCCESS;
}


RBBErrors parameterr()
/* Right align */
{
    if (warehouse.flags.align == RBB_ALIGN_UNDETERMINED)
        warehouse.flags.align =  RBB_ALIGN_RIGHT;
    else
        error(RBB_ERRORS_BADARGUMENTS);

    return RBB_ERRORS_SUCCESS;
}

RBBErrors parametero()
/* Optimize flag */
{
    if (!warehouse.flags.optimisation)
         warehouse.flags.optimisation = RBB_TRUE;
    else
        error(RBB_ERRORS_BADARGUMENTS);

    return RBB_ERRORS_SUCCESS;
}

RBBErrors parameterp()
/* Don't-paint-flag */
{
    if (!warehouse.flags.paint)
         warehouse.flags.paint = RBB_TRUE;
    else
        error(RBB_ERRORS_BADARGUMENTS);

    return RBB_ERRORS_SUCCESS;
}

RBBErrors parameterd()
/* Doubles flag */
{
    if (!warehouse.flags.doubles)
         warehouse.flags.doubles = RBB_TRUE;
    else
        error(RBB_ERRORS_BADARGUMENTS);

    return RBB_ERRORS_SUCCESS;
}

RBBErrors processargument(char * parameter, int32_t argc, int32_t pos)
{
    /* Parameters types
     * -g -h -j
     * -ghj
     * --ger --hou --jik
     * filename         */

    /* NOTE: argument is always more than 1 character long */
    if (parameter[0] == '-')
    {
        /* -g -h -j
         * -ghj
         * --ger --hou --jik */
        if (parameter[1] == '-')
        {
            /* --ger --hou --jik */
            if (strlen(parameter) > 2)
            {
                parameter += 2;
#               define TIER1(SHORT, LONG, CALLBACK, MSG) \
                if (!strcmp(parameter, #LONG))      \
                {                                   \
                    CALLBACK();                     \
                } else
                RBB_PARAMETERS_LIST
#               undef TIER1
                    error(RBB_ERRORS_BADARGUMENTS);
            }
            else
                error(RBB_ERRORS_BADARGUMENTS);
        }
        else
        {
            /* -g -h -j
             * -ghj    */
            parameter++;
            uint32_t i;
            for (i = 0; i < strlen(parameter); i++)
            {
#               define TIER1(SHORT, LONG, CALLBACK, MSG) \
                if ((parameter[i] == #SHORT[0]))    \
                {                                   \
                    CALLBACK();                     \
                } else
                RBB_PARAMETERS_LIST
#               undef TIER1
                    error(RBB_ERRORS_BADARGUMENTS);
            }
        }
    }
    else
    {
        /* filename */
        if (pos != argc - 1)
            error(RBB_ERRORS_BADARGUMENTS);
        if (!(warehouse.filename)) warehouse.filename = parameter;
                              else error(RBB_ERRORS_BADARGUMENTS);
    }

    return RBB_ERRORS_SUCCESS;
}

RBBErrors processarguments(int32_t argc, char ** argv)
{
    int32_t i;
    for (i = 1; i < argc; i++)
        RBB_CHECK(processargument(argv[i], argc, i));

    return RBB_ERRORS_SUCCESS;
}
