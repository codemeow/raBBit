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

#ifndef XERRORS_H
#define XERRORS_H

#define RBB_ERRORS_LIST                                                  \
    TIER1(      SUCCESS, ""                                            ) \
    TIER1( BADARGUMENTS, "Bad arguments. See -h for usage."            ) \
    TIER1( CANTOPENFILE, "Error while opening file."                   ) \
    TIER1( CANTREADFILE, "Error while reading file."                   ) \
    TIER1(      NOTAPNG, "Selected file is not a png file."            ) \
    TIER1( PNGLIBFAILED, "One or more functions in pnglib has failed." ) \
    TIER1(     BADALLOC, "Error during memory allocation."             ) \
    TIER1(CANTCLOSEFILE, "Error while closing file."                   ) \
    TIER1(      NOALIGN, "No alignment specified."                     ) \
    TIER1( BADCOLORTYPE, "Unsupported PNG color type."                 )

#endif // XERRORS_H
