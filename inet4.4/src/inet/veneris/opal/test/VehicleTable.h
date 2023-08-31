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

#ifndef __INET_VEHICLETABLE_H_
#define __INET_VEHICLETABLE_H_

#include <omnetpp.h>
#include "VehicleInfo.h"
using namespace omnetpp;

namespace inet {


/**
 * TODO - Generated class
 */
typedef std::map<int,VehicleInfo*> VTable;

class VehicleTable : public cSimpleModule
{
public:
    virtual ~VehicleTable();
    virtual int insertOrUpdate(VehicleInfo* info);
    virtual void refreshTable();
    VTable vt;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


    cMessage* updateTimer;
    double updateTime;
    static simsignal_t neighborsSignal;
    static simsignal_t irtSignal;

};

} //namespace


#endif
