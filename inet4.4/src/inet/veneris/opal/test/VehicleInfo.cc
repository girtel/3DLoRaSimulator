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

#include "VehicleInfo.h"

namespace inet {

/*VehicleInfo::VehicleInfo(int id, Coord pos, Coord speed, double br, double weight, double power) {
  this->id=id;
  this->speed=speed;
  this->pos=pos;
  this->beaconRate=br;
  this->weight=weight;
  this->power=power;
  this->last_update = simTime();
  this->init=simTime();

}*/
VehicleInfo::VehicleInfo(int id) {
    this->id=id;
    this->last_update = simTime();
    this->init=simTime();
}
VehicleInfo::~VehicleInfo() {
    // TODO Auto-generated destructor stub
}

std::string  VehicleInfo::toString() const {
    std::ostringstream s(std::ostringstream::out);

    //s <<"id="<<id<<";(x,y)="<<pos<<";sp="<<speed<<";br="<<beaconRate<<"weigth="<<weight<<"init="<<init<<"lu="<<last_update<<"power"<<power;
    s<<"id="<<id<<"init="<<init<<"lu="<<last_update;
    return s.str();
}
std::ostream& operator<<(std::ostream& out, const VehicleInfo& inf)
{
    std::string a=inf.toString();
    out<<a;
    return out;


}

} /* namespace inet */

