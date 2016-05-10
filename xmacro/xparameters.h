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

#ifndef XPARAMETERS_H
#define XPARAMETERS_H

#define RBB_PARAMETERS_LIST        \
    TIER1(h,     help, parameterh, "            Show usage") \
    TIER1(l,     left, parameterl, "    Set left alignment") \
    TIER1(c,   center, parameterc, "  Set center alignment") \
    TIER1(r,    right, parameterr, "   Set right alignment") \
    TIER1(o, optimise, parametero, "      Optimise output ") \
    TIER1(p,    paint, parameterp, "    Don't color blocks") \
    TIER1(d,   double, parameterd, "Doubles the block char")

#endif // XPARAMETERS_H
