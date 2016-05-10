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

#ifndef HELPERS_H
#define HELPERS_H

#define RBB_CHECK(X)                 \
{                                    \
    RBBErrors _res_ = (X);           \
    if (_res_ != RBB_ERRORS_SUCCESS) \
        error(_res_);                \
}

#define RBB_PIXELCMP(PX1, PX2) \
    (((PX1).alpha == (PX2).alpha) && \
     ((PX1).red   == (PX2).red  ) && \
     ((PX1).green == (PX2).green) && \
     ((PX1).blue  == (PX2).blue))

#endif // HELPERS_H
