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

#ifndef CONSTS_H
#define CONSTS_H

///@todo version returning parameter
#define RBB_MAJOR_VERSION (0)
#define RBB_MINOR_VERSION (1)

#define RBB_HEADER_SIZE     (8)

#define RBB_COLSHIFT_R (0)
#define RBB_COLSHIFT_G (1)
#define RBB_COLSHIFT_B (2)
#define RBB_COLSHIFT_A (3)

#define RBB_MULTIPLIER_RGB  (3)
#define RBB_MULTIPLIER_RGBA (4)

#define RBB_TRANS_LEVEL (0xFF)

extern const char * RBB_EXIT_STRINGS[];

#endif // CONSTS_H
