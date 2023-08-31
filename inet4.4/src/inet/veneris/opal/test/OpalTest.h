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

#ifndef __INET4_5_OPALTEST_H_
#define __INET4_5_OPALTEST_H_

#include <omnetpp.h>
#include "inet/common/packet/Packet.h"
#include "VehicleTable.h"
#include "inet/mobility/contract/IMobility.h"
using namespace omnetpp;

namespace inet {


/**
 * Simple periodic packet generator for tests
 */
class OpalTest : public cSimpleModule, cListener
{
protected:


    int id;


    virtual void initialize(int stage);
    virtual int numInitStages() const override {return NUM_INIT_STAGES;}

    virtual void handleMessage(cMessage *msg);

    void handleCAM(cMessage *msg);
    void sendDown(Packet* o);
    void sendPacket();
    int lowerLayerOutId;
    int lowerLayerInId;
    int packetBytes;
    VehicleTable* vt;
    VehicleInfo* info;
public:
    OpalTest();
    virtual ~OpalTest();
    virtual void receiveSignal(cComponent *source, simsignal_t signal, cObject *value, cObject *details) override;

};

} //namespace

#endif
