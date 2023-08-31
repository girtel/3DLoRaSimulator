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

#include "OpalTestTransmitter.h"

namespace inet {

Define_Module(OpalTestTransmitter);

void OpalTestTransmitter::initialize(int stage)
{
    OpalTest::initialize(stage);
    if(stage == INITSTAGE_LOCAL) {
        transmitTime=par("transmitTime");
        generationTimer = new cMessage("Generation timer");
        transmitWhenPositionChanges = par("transmitWhenPositionChanges").boolValue();
    } else if(stage == INITSTAGE_APPLICATION_LAYER) {

        if (transmitWhenPositionChanges) {


        } else {
            scheduleAt(simTime() + transmitTime,generationTimer);
        }
    }
    // TODO - Generated method body
}

void OpalTestTransmitter::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {

        sendPacket();
    } else {
        //Must be from lowerLayer
        OpalTest::handleMessage(msg);
    }
}

OpalTestTransmitter::OpalTestTransmitter() :   generationTimer(nullptr) {
}

OpalTestTransmitter::~OpalTestTransmitter() {
    if (generationTimer!=nullptr) {
        cancelAndDelete(generationTimer);
    }
}
void OpalTestTransmitter::receiveSignal(cComponent* source,
        simsignal_t signal, cObject* value, cObject* details) {
    if (signal==IMobility::mobilityStateChangedSignal) {

        //MobilityBase* mob=check_and_cast<MobilityBase*>(value);
        if (transmitWhenPositionChanges) {
            Enter_Method_Silent();
            sendPacket();

        }
    }
}

} //namespace
