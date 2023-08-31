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

module LoRaLogNormalShadowing extends FreeSpacePathLoss
{
    parameters:
        //parameters taken from paper LoRaSim
        double d0 = default(250m) @unit(m);
        // TFG
        //double gamma = default(2.41);
        //double sigma = default(8.868)
		// LAST MEAS
		//double gamma = default(2.41);
        //double sigma = default(8.868);
        // ARTICULO
        //double gamma = default(4.1532);
        //double sigma = default(7.7667);
        // ARTICULO_2
        double gamma = default(3.946);
        double sigma = default(7.75); //13.168    
        @class(LoRaLogNormalShadowing);
}
