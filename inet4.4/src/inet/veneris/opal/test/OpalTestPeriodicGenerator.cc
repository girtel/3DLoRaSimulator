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

#include "OpalTestPeriodicGenerator.h"

namespace inet {

Define_Module(OpalTestPeriodicGenerator);

void OpalTestPeriodicGenerator::initialize(int stage)
{
    OpalTestTransmitter::initialize(stage);
    if(stage == INITSTAGE_LOCAL) {
        beaconFrequency= par("beaconFrequency");
        EV_INFO<<simTime()<<" beaconFrequency="<<beaconFrequency<<endl;
    } else if(stage == INITSTAGE_APPLICATION_LAYER) {

        cancelEvent(generationTimer);
        if (beaconFrequency>0) { //If we do not want a vehicle to transmit, just set a zero or negative frequency
            //Randomize init
            scheduleAt(simTime() + uniform(0,0.002) + 1.0/beaconFrequency,generationTimer);
        }
    }


}
void OpalTestPeriodicGenerator::processGenerationTime() {
    if (beaconFrequency>0) {
        scheduleAt(simTime() + 1.0/beaconFrequency,generationTimer);
    }
    //auto data = makeShared<ByteCountChunk>(B(packetBytes));
    // Packet* cam = new Packet("cam", data);

    sendPacket();
}
void OpalTestPeriodicGenerator::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {

        processGenerationTime();
    } else {
        //Must be from lowerLayer
        OpalTest::handleMessage(msg);
    }
}

} //namespace
