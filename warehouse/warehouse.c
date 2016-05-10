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

#include <stddef.h>
#include "../warehouse/warehouse.h"

RBBWarehouse warehouse;

RBBErrors initialise()
{
    warehouse.flags.align        = RBB_ALIGN_UNDETERMINED;
    warehouse.flags.optimisation = RBB_FALSE;
    warehouse.flags.paint        = RBB_FALSE;
    warehouse.flags.doubles      = RBB_FALSE;
    warehouse.filename           = NULL;    

    return RBB_ERRORS_SUCCESS;
}
