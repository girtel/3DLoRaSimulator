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

#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/linklayer/common/Ieee802SapTag_m.h"
#include "inet/linklayer/common/MacAddress.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/common/Ptr.h"
#include "inet/common/ProtocolGroup.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/physicallayer/wireless/ieee80211/mode/Ieee80211ModeSet.h"
#include "inet/common/Simsignals.h"


#include "CAMPacket_m.h"
#include "OpalTest.h"


namespace inet {


Define_Module(OpalTest);


OpalTest::OpalTest() :   vt(nullptr), info(nullptr)
{
}
OpalTest::~OpalTest() {

}
void OpalTest::initialize(int stage)
{
    if(stage == INITSTAGE_LOCAL) {

        id=getParentModule()->par("id");
        lowerLayerOutId=findGate("lowerLayerOut");
        lowerLayerInId =findGate("lowerLayerIn");

        packetBytes= par("packetBytes");


        info = new VehicleInfo(-1);


        //Subscribe to position changes for the receivers and transmitters
        getParentModule()->subscribe(IMobility::mobilityStateChangedSignal,this);
    } else if(stage == INITSTAGE_APPLICATION_LAYER) {
        vt=check_and_cast<VehicleTable*>(getParentModule()->getSubmodule("vehicleTable"));


       // const physicallayer::Ieee80211ModeSet* modeSet= physicallayer::Ieee80211ModeSet::getModeSet("p");
       // emit(modesetChangedSignal, modeSet);
    }

}

void OpalTest::handleMessage(cMessage *msg)
{

        //Must be from lowerLayer
        handleCAM(msg);

        std::cout<<simTime()<<":"<<id<<":Received CAM"<< endl;
        delete msg;

}


void OpalTest::sendPacket() {
    auto data = makeShared<opaltest::CAMPacket>();
    data->setSource(id);
    data->setCreationTime(simTime());
    data->setChunkLength(B(packetBytes));
    Packet* cam = new Packet("cam", data);
    sendDown(cam);

}
void OpalTest::sendDown(Packet* p) {
    //Add SAP. I think we may remove this
    p->addTagIfAbsent<Ieee802SapReq>()->setDsap(SapCode::SAP_IP);
    p->addTagIfAbsent<MacAddressReq>()->setDestAddress(MacAddress::BROADCAST_ADDRESS);
    //Should put something sensible here. Keep this to prevent LlcEpd from complaining
    p->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::ipv4);


    send(p,lowerLayerOutId);
}

void OpalTest::handleCAM(cMessage* msg) {
    EV_INFO<<id<<":Received CAM"<< endl;
    Packet* pkt=static_cast<Packet*>(msg);
    auto data=pkt->peekAtFront<opaltest::CAMPacket>(B(packetBytes));
    int sid=data->getSource();
    info->id=sid;
    vt->insertOrUpdate(info);


}
void OpalTest::receiveSignal(cComponent* source,
        simsignal_t signal, cObject* value, cObject* details) {
    if (signal==IMobility::mobilityStateChangedSignal) {

    }
}



} //namespace
