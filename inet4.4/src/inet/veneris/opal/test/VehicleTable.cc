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

#include "VehicleTable.h"
#define UPDATE_TO 4001
namespace inet {

Define_Module(VehicleTable);
simsignal_t VehicleTable::neighborsSignal=cComponent::registerSignal("neighbors");
simsignal_t VehicleTable::irtSignal=cComponent::registerSignal("irt");

VehicleTable::~VehicleTable() {
    cancelAndDelete(updateTimer);
}
void VehicleTable::initialize()
{

    updateTimer = new cMessage("VTable update", UPDATE_TO );
    updateTime=par("updateTime");
    scheduleAt(simTime()+updateTime, updateTimer);
    EV_INFO<<"Initializing Vehicle Table with update time="<<updateTime<<endl;
    WATCH_PTRMAP(vt);

}

void VehicleTable::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        refreshTable();
        scheduleAt(simTime()+updateTime, updateTimer);
        emit(neighborsSignal, 0);
    }
}
int  VehicleTable::insertOrUpdate(VehicleInfo* info) {

    emit(neighborsSignal,vt.size());
    VTable::iterator it = vt.find(info->id);
    if (it==vt.end()) {
        //VehicleInfo* newNeigbor=new VehicleInfo(info->id,info->pos,info->speed,info->beaconRate,info->weight,info->power);
        VehicleInfo* newNeigbor=new VehicleInfo(info->id);
        vt.insert(it,std::pair<int,VehicleInfo*>(info->id,newNeigbor));
        return 1;
    } else {
        emit(irtSignal,(simTime()-it->second->last_update).dbl());
        (*it->second) = *info;
        it->second->last_update=simTime();
        return 0;
    }

}
void VehicleTable::refreshTable(){
    emit(neighborsSignal,vt.size());
    VTable::iterator it=vt.begin();


    while(it!=vt.end()) {

        if (simTime()-it->second->last_update > updateTime) {
            emit(irtSignal,(simTime()-it->second->last_update).dbl());

            delete(it->second);
            vt.erase(it);
        }

        ++it;
    }

}

} //namespace

