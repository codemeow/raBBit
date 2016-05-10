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

#include "./definitions/helpers.h"
#include "./processing/parameters.h"
#include "./processing/loader.h"
#include "./processing/processor.h"
#include "./printing/print.h"
#include "./warehouse/warehouse.h"

int main(int argc, char ** argv)
{
    RBB_CHECK(initialise());
    RBB_CHECK(processarguments(argc, argv));
    RBB_CHECK(loadimage());
    RBB_CHECK(processdata());
    RBB_CHECK(cleardata());

    return RBB_ERRORS_SUCCESS;
}
