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

#ifndef INET_OPALTEST_VEHICLEINFO_H_
#define INET_OPALTEST_VEHICLEINFO_H_
#include "inet/common/geometry/common/Coord.h"
#include <omnetpp/cobject.h>

namespace inet {


class VehicleInfo: public omnetpp::cObject {
public:
    // VehicleInfo(int id, Coord pos, Coord speed, double br, double weight, double power);
    VehicleInfo(int id);
    virtual ~VehicleInfo();
    //Coord speed;
    //Coord pos;
    //double beaconRate;
    simtime_t last_update;
    simtime_t init;
    int id;
    //double weight;
    //double power;
    friend std::ostream& operator<<(std::ostream& out, const VehicleInfo& inf);
    std::string  toString() const;

};

} /* namespace inet */


#endif /* INET_OPALTEST_VEHICLEINFO_H_ */
