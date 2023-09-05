//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package inet.LoRaPhy;

import inet.physicallayer.wireless.common.pathloss.FreeSpacePathLoss;

module HataOkumura extends FreeSpacePathLoss
{
    parameters:
        //parameters taken from paper LoRaSim
        double K1 = default(127.5);
        double K2 = default(35.2);
        bool small = default(true); // true if is a Small or Medium Town, false if is a Large Town
        int suburban = default(0); // 0 if is a Urban area, 1 if is a suburban area, 2 if is a Opan Rural Area
        int GW = default(11);
        int Node = default(2);
        @class(HataOkumura);
}
