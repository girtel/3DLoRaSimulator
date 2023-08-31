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

#ifndef __INET_VENERISSERVER_H_
#define __INET_VENERISSERVER_H_

#include <omnetpp.h>
#include "ExecutionServer.h"
#include "inet/veneris/opal/OpalRadioMedium.h"
#include "VenerisExternalMobility.h"
#include "messages/BaseTypes_generated.h"
using namespace omnetpp;

namespace inet {

/**
 * Server handling messages from Veneris
 */
class VenerisServer : public ExecutionServer
{

protected:
    struct VehicleInfo {
        cModule* module;
        VenerisExternalMobility* mob;
    };

    //Opal can be used to simulate propagation or not
    bool useOpal;
    //Force using a different propagation/pathloss mechanism even if the external entity requires Opal
    bool forceNotUsingOpal;
    std::string opalModule;
    std::string vehicleModule;
    std::string mobilityModule;

    int activeVehiclesIndex;
    std::set<uint> insertedVehicles; //To keep track of inserted vehicles
    std::map<int,VehicleInfo> activeVehicles;
    inet::physicallayer::OpalRadioMedium* opalRadio;
    virtual int numInitStages() const override {return NUM_INIT_STAGES;}
    virtual void initialize(int stage) override;
//Util
    optix::float3 Vec3ToFloat3(const Veneris::Communications::Vec3* v);


    //Server message handlers
    virtual void configOpal();
    virtual void addStaticMeshWithFaces();
    virtual void addOpalEdge();
    virtual void addOpalEdgeToGroup();
    virtual void registerGain();
    virtual void registerReceiverGain();
    virtual void raySphereRange();
    virtual void setRDNRayRange();
    virtual void createOpal();
    virtual void addStaticMesh();
    virtual void addStaticCurvedMesh();
    virtual void finishOpalContext();
    virtual void createVehicle();
    virtual void destroyVehicle();
    virtual void updateVehicleState();
    virtual void addDynamicMeshGroup();
    virtual void addDynamicMesh();
    virtual void addDynamicMeshWithFaces();
    virtual void finishDynamicMeshGroup();
    virtual void removeDynamicMeshGroup();
    virtual void updateTransformInGroup();
public:
    VenerisServer();
    virtual ~VenerisServer();
    virtual void processMessage( Veneris::Communications::VenerisMessageTypes type, uint32_t size) override;
};

} //namespace

#endif
