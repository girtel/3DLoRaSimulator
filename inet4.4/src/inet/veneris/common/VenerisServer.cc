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

#include "VenerisServer.h"


#include "messages/BaseTypes_generated.h"
#include "messages/Header_generated.h"
#include "messages/ConfigOpal_generated.h"
#include "messages/UseOpal_generated.h"
#include "messages/RegisterReceiverGain_generated.h"
#include "messages/RegisterGain_generated.h"
#include "messages/RaySphereRange_generated.h"
#include "messages/RDNRayRange_generated.h"
#include "messages/OpalEdge_generated.h"
#include "messages/OpalEdgeToGroup_generated.h"
#include "messages/StaticMesh_generated.h"
#include "messages/StaticCurvedMesh_generated.h"
#include "messages/StaticMeshWithFaces_generated.h"
#include "messages/CreateVehicle_generated.h"
#include "messages/DestroyVehicle_generated.h"
#include "messages/VehicleState_generated.h"
#include "messages/AddDynamicMeshGroup_generated.h"
#include "messages/RemoveDynamicMeshGroup_generated.h"
#include "messages/FinishDynamicMeshGroup_generated.h"
#include "messages/DynamicMesh_generated.h"
#include "messages/DynamicMeshWithFaces_generated.h"
#include "messages/UpdateTransformInGroup_generated.h"
#include "inet/common/IPrintableObject.h"



using namespace Veneris::Communications;
namespace inet {

Define_Module(VenerisServer);

#define CHKOPAL() if (!useOpal) {return;} else if (forceNotUsingOpal) {return;} if (opalRadio==nullptr) {throw cRuntimeError("OpalRadio Module not created before adding static mesh");return;}


void VenerisServer::configOpal() {
    auto msg = readMsg<ConfigOpal>(msg_size);
    if (forceNotUsingOpal) {
        //Print configuration
        std::cout<<"Forced not using Opal"<<endl;
        std::cout<< check_and_cast<inet::IPrintableObject*>(getParentModule()->getModuleByPath(".radioMedium"))->getCompleteStringRepresentation()<<std::endl;
        std::cout<< check_and_cast<inet::IPrintableObject*>(getParentModule()->getModuleByPath(".radioMedium.pathLoss"))->getCompleteStringRepresentation()<<std::endl;
        std::cout<< check_and_cast<inet::IPrintableObject*>(getParentModule()->getModuleByPath(".radioMedium.backgroundNoise"))->getCompleteStringRepresentation()<<std::endl;
        std::cout<< check_and_cast<inet::IPrintableObject*>(getParentModule()->getModuleByPath(".radioMedium.mediumLimitCache"))->getCompleteStringRepresentation()<<std::endl;

        return;
    }
    //Remove default radioMedium
    getParentModule()->getModuleByPath(".radioMedium")->deleteModule();

    useOpal=true;

    //We may want to use a different configurations
    bool override=par("overrideConfigurationMessage").boolValue();

    //Read configuration from message
    float f=msg->frequency();
    int32_t simType=msg->simType();
    int32_t computeMode=msg->computeMode();
    uint32_t maxReflections=msg->maxReflections();
    bool useExactSpeedOfLight=msg->useExactSpeedOfLight();
    bool useDiffraction=msg->useDiffraction();
    bool enableFastMath=msg->enableFastMath();
    bool generateRaysOnLaunch=msg->generateRaysOnLaunch();
    bool multiGPU=msg->multiGPU();
    bool logTrace=msg->logTrace();
    bool multiTransmitter=msg->multiTransmitter();
    bool useAntennaGain=msg->useAntennaGain();
    float minEpsilon = msg->minEpsilon();

    if (override) {
        //Overridable parameters at the moment
        maxReflections = static_cast<uint32_t>(par("maxReflections").intValue());
        f= Hz(par("carrierFrequency")).get();
    }

    cModuleType *moduleType = cModuleType::get(opalModule.c_str());
    cModule *module = moduleType->create("radioMedium", this->getParentModule());
    module->par("carrierFrequency").setDoubleValue((double)f);
    module->par("loadMeshesFromFile").setBoolValue(false);
    module->par("maxNumberOfReflections").setIntValue(maxReflections);

    switch(simType) {
    case 0:
        module->par("simulationType").setStringValue("Basic");
        break;
    case 1:
        module->par("simulationType").setStringValue("Depolarization");
        break;
    case 2:
        module->par("simulationType").setStringValue("RDN");
        break;
    case 3:
        module->par("simulationType").setStringValue("Diffraction");
        break;
    }
    switch(computeMode) {
    case 0:
        module->par("computeMode").setStringValue("Voltage");
        break;
    case 1:
        module->par("computeMode").setStringValue("Field");
        break;
    }

    module->par("useExactSpeedOfLight").setBoolValue(useExactSpeedOfLight);
    module->par("useDiffraction").setBoolValue(useDiffraction);
    module->par("enableFastMath").setBoolValue(enableFastMath);
    module->par("generateRaysOnLaunch").setBoolValue(generateRaysOnLaunch);
    module->par("enableMultiGPU").setBoolValue(multiGPU);
    module->par("logTrace").setBoolValue(logTrace);
    //module->par("multiTransmitter").setBoolValue(multiTransmitter);
    module->par("useAntennaGain").setBoolValue(useAntennaGain);

    //This parameter does not come from Veneris at the moment
    //module->par("minEpsilon").setDoubleValue(par("minEpsilon").doubleValue()); //To avoid numerical errors. Implies that separations between meshes and receiver below 1 mm cannot be distinguished
    module->par("minEpsilon").setDoubleValue(minEpsilon);
    opalRadio=check_and_cast<inet::physicallayer::OpalRadioMedium*>(module);
    module->finalizeParameters();
    module->buildInside();
    module->scheduleStart(simTime());
    module->callInitialize();
    if (par("printEnabled").boolValue()) {
        opalRadio->setPrintEnabled(1024*1024*1024);
    }


}

void VenerisServer::createOpal() {
    auto msg = readMsg<UseOpal>(msg_size);
    if (forceNotUsingOpal) {
        //Print configuration
        std::cout<<"Forced not using Opal"<<endl;
        std::cout<< check_and_cast<inet::IPrintableObject*>(getParentModule()->getModuleByPath(".radioMedium"))->getCompleteStringRepresentation()<<std::endl;
        std::cout<< check_and_cast<inet::IPrintableObject*>(getParentModule()->getModuleByPath(".radioMedium.pathLoss"))->getCompleteStringRepresentation()<<std::endl;
        std::cout<< check_and_cast<inet::IPrintableObject*>(getParentModule()->getModuleByPath(".radioMedium.backgroundNoise"))->getCompleteStringRepresentation()<<std::endl;
        std::cout<< check_and_cast<inet::IPrintableObject*>(getParentModule()->getModuleByPath(".radioMedium.mediumLimitCache"))->getCompleteStringRepresentation()<<std::endl;

        return;
    }
    //Remove default radioMedium
    getParentModule()->getModuleByPath(".radioMedium")->deleteModule();

    useOpal=true;

    //We may want to use a different configurations
    bool override=par("overrideConfigurationMessage").boolValue();

    //Read configuration from message
    uint32_t ad=msg->azimuthDelta();
    uint32_t ed=msg->elevationDelta();
    bool useDecimal=msg->useDecimalDegrees();
    uint32_t maxReflections=msg->maxReflections();
    float f=msg->frequency();

    if (override) {
        //Overridable parameters at the moment
        maxReflections = static_cast<uint32_t>(par("maxReflections").intValue());
        f= Hz(par("carrierFrequency")).get();
    }


    cModuleType *moduleType = cModuleType::get(opalModule.c_str());
    cModule *module = moduleType->create("radioMedium", this->getParentModule());
    module->par("azimuthDelta").setIntValue(ad);
    module->par("elevationDelta").setIntValue(ed);
    module->par("carrierFrequency").setDoubleValue((double)f);
    module->par("loadMeshesFromFile").setBoolValue(false);
    module->par("maxNumberOfReflections").setIntValue(maxReflections);
    module->par("useDecimalDegreeDelta").setBoolValue(useDecimal);
    //This parameter does not come from Veneris at the moment
    module->par("minEpsilon").setDoubleValue(par("minEpsilon").doubleValue()); //To avoid numerical errors. Implies that separations between meshes and receiver below 1 mm cannot be distinguished

    opalRadio=check_and_cast<inet::physicallayer::OpalRadioMedium*>(module);
    module->finalizeParameters();
    module->buildInside();
    module->scheduleStart(simTime());
    module->callInitialize();
    if (par("printEnabled").boolValue()) {
        opalRadio->setPrintEnabled(1024*1024*1024);
    }

    //Log configuration
    std::cout<<simTime()<<": Creating Opal contex. "<<"azimuthDelta="<<ad<<" elevationDelta="<<ed<<" carrierFrequency="<<f<<" maxNumberOfReflections="<<maxReflections<<" useDecimalDegreeDelta="<<useDecimal<<"minEpsilon="<<par("minEpsilon").doubleValue()<<"printEnabled="<<par("printEnabled").boolValue()<<endl;

}
VenerisServer::VenerisServer() {
    opalRadio=nullptr;
    useOpal=false;
    activeVehiclesIndex=0;
}
VenerisServer::~VenerisServer() {

}

void VenerisServer::initialize(int stage) {
    ExecutionServer::initialize(stage);
    if (stage==INITSTAGE_LOCAL) {
        opalModule=par("opalModule").stdstringValue();
        vehicleModule=par("vehicleModule").stdstringValue();
        mobilityModule=par("mobilityModule").stdstringValue();
        forceNotUsingOpal=par("forceNotUsingOpal").boolValue();

    }
}
void VenerisServer::addStaticMeshWithFaces() {
    auto msg = readMsg<StaticMeshWithFaces>(msg_size); //Let message be read to remove from buffers
    CHKOPAL();
    std::cout<<simTime()<<": Adding static mesh with faces "<<std::endl;
    auto vertices=msg->vertices();
    auto indices=msg->indexes();
    auto faceids=msg->faceIds();
    //We are copying a lot...
    int vsize;
    if (vertices) {
        vsize=vertices->size();
    } else {
        throw cRuntimeError("addStaticMeshWithFaces() vertices is null");
    }

    std::vector<optix::float3> vo(vsize);
    for (int i=0; i<vsize; i++){

        vo[i]=optix::make_float3(vertices->Get(i)->x(),vertices->Get(i)->y(),vertices->Get(i)->z());
        //std::cout<<"v["<<i<<"]="<<vo[i]<<std::endl;
    }
    int isize=indices->size();
    std::vector<int> io(isize);
    for (int i=0; i<isize; i++){
        io[i]=indices->Get(i);
        //std::cout<<"i["<<i<<"]="<<io[i]<<std::endl;

    }
    int fosize=faceids->size();
    std::vector<int> fo(fosize);

    for (int i=0; i<fosize; i++){
        fo[i]=faceids->Get(i);
    }
    std::vector<std::pair<optix::int3,unsigned int> > faces;
    for (int i=0; i<io.size(); i=i+3){
        //  optix::int3 tri=;
        faces.push_back(std::make_pair<optix::int3,unsigned int>(make_int3(io[i],io[i+1],io[i+2]),static_cast<unsigned int>(fo[i])));

    }

    auto tm=msg->transform();
    optix::Matrix4x4 tmo;
    tmo.setRow(0, optix::make_float4(tm->r0().x(),tm->r0().y(),tm->r0().z(),tm->r0().w()));
    tmo.setRow(1, optix::make_float4(tm->r1().x(),tm->r1().y(),tm->r1().z(),tm->r1().w()));
    tmo.setRow(2, optix::make_float4(tm->r2().x(),tm->r2().y(),tm->r2().z(),tm->r2().w()));
    tmo.setRow(3, optix::make_float4(tm->r3().x(),tm->r3().y(),tm->r3().z(),tm->r3().w()));
    //std::cout<<"transformation matrix "<<tmo<<std::endl;

    auto em=msg->material();

    MaterialEMProperties emo=opalRadio->ITUparametersToMaterial(em->a(),em->b(),em->c(),em->d());
    opalRadio->addStaticMeshWithFaces(vo, faces, tmo, emo);
}


void VenerisServer::addStaticMesh() {

    auto msg = readMsg<StaticMesh>(msg_size); //Let message be read to remove from buffers
    CHKOPAL();
    std::cout<<simTime()<<": Adding static mesh "<<std::endl;
    auto vertices=msg->vertices();
    auto indices=msg->indexes();
    //We are copying a lot...
    int vsize=vertices->size();

    std::vector<optix::float3> vo(vsize);
    for (int i=0; i<vsize; i++){

        vo[i]=optix::make_float3(vertices->Get(i)->x(),vertices->Get(i)->y(),vertices->Get(i)->z());
        //std::cout<<"v["<<i<<"]="<<vo[i]<<std::endl;
    }
    int isize=indices->size();
    std::vector<int> io(isize);
    for (int i=0; i<isize; i++){
        io[i]=indices->Get(i);
        //std::cout<<"i["<<i<<"]="<<io[i]<<std::endl;

    }
    auto tm=msg->transform();
    optix::Matrix4x4 tmo;
    tmo.setRow(0, optix::make_float4(tm->r0().x(),tm->r0().y(),tm->r0().z(),tm->r0().w()));
    tmo.setRow(1, optix::make_float4(tm->r1().x(),tm->r1().y(),tm->r1().z(),tm->r1().w()));
    tmo.setRow(2, optix::make_float4(tm->r2().x(),tm->r2().y(),tm->r2().z(),tm->r2().w()));
    tmo.setRow(3, optix::make_float4(tm->r3().x(),tm->r3().y(),tm->r3().z(),tm->r3().w()));
    //std::cout<<"transformation matrix "<<tmo<<std::endl;

    auto em=msg->material();

    MaterialEMProperties emo=opalRadio->ITUparametersToMaterial(em->a(),em->b(),em->c(),em->d());
    //std::cout<<simTime()<<": MaterialEMProperties="<<emo.dielectricConstant<<std::endl; It does not work anymore... why?
    opalRadio->addStaticMesh(vsize, vo.data(), isize,io.data(), tmo, emo);



}
void VenerisServer::addStaticCurvedMesh() {

    auto msg = readMsg<StaticCurvedMesh>(msg_size); //Let message be read to remove from buffers
    CHKOPAL();
    std::cout<<simTime()<<": Adding static curved mesh "<<std::endl;
    auto vertices=msg->vertices();
    auto indices=msg->indexes();
    //We are copying a lot...
    int vsize=vertices->size();
    auto pd1=msg->pd1();
    auto pd2=msg->pd2();
    auto makeSingleFace=msg->singleFace();
    auto faceId=msg->faceId();

    std::vector<optix::float3> vo(vsize);
    for (int i=0; i<vsize; i++){

        vo[i]=optix::make_float3(vertices->Get(i)->x(),vertices->Get(i)->y(),vertices->Get(i)->z());
        //std::cout<<"v["<<i<<"]="<<vo[i]<<std::endl;
    }
    int isize=indices->size();
    std::vector<int> io(isize);
    for (int i=0; i<isize; i++){
        io[i]=indices->Get(i);
        //std::cout<<"i["<<i<<"]="<<io[i]<<std::endl;

    }
    auto tm=msg->transform();
    optix::Matrix4x4 tmo;
    tmo.setRow(0, optix::make_float4(tm->r0().x(),tm->r0().y(),tm->r0().z(),tm->r0().w()));
    tmo.setRow(1, optix::make_float4(tm->r1().x(),tm->r1().y(),tm->r1().z(),tm->r1().w()));
    tmo.setRow(2, optix::make_float4(tm->r2().x(),tm->r2().y(),tm->r2().z(),tm->r2().w()));
    tmo.setRow(3, optix::make_float4(tm->r3().x(),tm->r3().y(),tm->r3().z(),tm->r3().w()));
    //std::cout<<"transformation matrix "<<tmo<<std::endl;

    auto em=msg->material();

    MaterialEMProperties emo=opalRadio->ITUparametersToMaterial(em->a(),em->b(),em->c(),em->d());
    //std::cout<<simTime()<<": MaterialEMProperties="<<emo.dielectricConstant<<std::endl; It does not work anymore... why?

    int pd1size=pd1->size();

    std::vector<optix::float4> pd1o(vsize);
    for (int i=0; i<pd1size; i++){

        pd1o[i]=optix::make_float4(pd1->Get(i)->x(),pd1->Get(i)->y(),pd1->Get(i)->z(),pd1->Get(i)->w());
        //std::cout<<"v["<<i<<"]="<<vo[i]<<std::endl;
    }
    int pd2size=pd2->size();

    std::vector<optix::float4> pd2o(vsize);
    for (int i=0; i<pd2size; i++){

        pd2o[i]=optix::make_float4(pd2->Get(i)->x(),pd2->Get(i)->y(),pd2->Get(i)->z(),pd2->Get(i)->w());
        //std::cout<<"v["<<i<<"]="<<vo[i]<<std::endl;
    }
    opalRadio->addStaticCurvedMesh(vo, io,  pd1o, pd2o, tmo, emo,makeSingleFace,faceId);



}
void VenerisServer::finishOpalContext() {

    CHKOPAL();
    opalRadio->finishOpalContext();
}

void VenerisServer::createVehicle() {
    auto msg = readMsg<CreateVehicle>(msg_size);
    uint id=msg->id();
    auto pos=msg->position();
    auto radius=msg->radius();


    //The index and vector size of the module seems to be just an internal property of the module, not really used because
    // OMNET modules seems to be stored in a linked list (at least previous to omnet 6.0.1)
    //So the index may be anything...
    //Just increment the index, and forget about the size when we remove a module.
    //But the statistics are recorded with the index of the vector...and we can remove and reinsert a vehicle.

    //We have to check inserted vehicles and vehicles indexes with omnet 6.0.1
    // TODO: we should keep track of removed and reinserted vehicles to merge the collected statistics, at the moment just erro
    if (insertedVehicles.find(id)!=insertedVehicles.end()) {
        error("Reinserted a previously inserted vehicle. Newly inserted vehicles must have different id, otherwise collected statistics are wrong");
    }

    cModuleType *moduleType = cModuleType::get(vehicleModule.c_str());
    cModule* parentmod = getParentModule();
            if (!parentmod) error("Parent Module not found");

    auto nodesSize=parentmod->getSubmoduleVectorSize("node");



    parentmod->setSubmoduleVectorSize("node", nodesSize +1);

    cModule *module = moduleType->create("node", parentmod,id);
    ++activeVehiclesIndex;
    module->par("id").setIntValue(id);
    if (useOpal) {
        module->par("receptionRadius").setDoubleValue(radius);
    }
    module->par("mobilityType").setStringValue(mobilityModule);
    module->finalizeParameters();
    module->buildInside();
    module->scheduleStart(simTime());

    //Init position
    cModule *mob = module->getModuleByPath(".mobility");
    VenerisExternalMobility* ven= check_and_cast<VenerisExternalMobility*>(mob);
    ven->setPosition(pos->x(),pos->y(), pos->z());
    VehicleInfo info;
    info.module=module;
    info.mob=ven;

    module->getModuleByPath(".wlan.radio.transmitter")->par("power").setDoubleValue(1.0);
    module->callInitialize();
    activeVehicles.insert(std::pair<int,VehicleInfo>(id, info));
    insertedVehicles.insert(id);

    std::cout<<simTime()<<": Created vehicle with module="<<vehicleModule<<", id="<<id<<". Active vehicles="<<activeVehicles.size()<<std::endl;

}

void VenerisServer::updateVehicleState() {
    auto msg = readMsg<VehicleState>(msg_size);
    uint id=msg->id();
    auto upos=msg->position();

    //Just update the position, the receiver in Opal is updated with the emitted signal
    try {
        VehicleInfo info=activeVehicles.at(id);
        info.mob->setPosition(upos->x(), upos->y(), upos->z());

    } catch (std::out_of_range e) {
        std::stringstream s;
        s<<"updateVehicleState():: Vehicle "<<id<<" is not registered with opal";
        throw cRuntimeError(s.str().c_str());
        return;
    }

}

void VenerisServer::addDynamicMeshGroup() {

    auto msg = readMsg<AddDynamicMeshGroup>(msg_size);
    CHKOPAL();
    const int id=msg->id();
    std::cout<<simTime()<<": Adding dynamic mesh group "<<id<<std::endl;
    opalRadio->addDynamicMeshGroup(id);
}

void VenerisServer::addDynamicMesh() {

    auto msg = readMsg<DynamicMesh>(msg_size);
    CHKOPAL();
    auto vertices=msg->vertices();
    auto indices=msg->indexes();
    //We are copying a lot...
    int vsize=vertices->size();

    std::vector<optix::float3> vo(vsize);
    for (int i=0; i<vsize; i++){

        vo[i]=optix::make_float3(vertices->Get(i)->x(),vertices->Get(i)->y(),vertices->Get(i)->z());
        // std::cout<<"v["<<i<<"]="<<vo[i]<<std::endl;
    }
    int isize=indices->size();
    std::vector<int> io(isize);
    for (int i=0; i<isize; i++){
        io[i]=indices->Get(i);
        // std::cout<<"i["<<i<<"]="<<io[i]<<std::endl;

    }
    auto id=msg->id();
    auto em=msg->material();
    std::cout<<simTime()<<": Adding dynamic mesh to group "<<id<<std::endl;
    MaterialEMProperties emo=opalRadio->ITUparametersToMaterial(em->a(),em->b(),em->c(),em->d());
    //std::cout<<simTime()<<": MaterialEMProperties"<<emo.dielectricConstant<<std::endl; //Does not work anymore
    opalRadio->addMeshToGroup(id, vsize, vo.data(), isize, io.data(), emo);

}
void VenerisServer::addDynamicMeshWithFaces() {

    auto msg = readMsg<DynamicMeshWithFaces>(msg_size);
    CHKOPAL();
    auto vertices=msg->vertices();
    auto indices=msg->indexes();
    //We are copying a lot...
    int vsize=vertices->size();

    std::vector<optix::float3> vo(vsize);
    for (int i=0; i<vsize; i++){

        vo[i]=optix::make_float3(vertices->Get(i)->x(),vertices->Get(i)->y(),vertices->Get(i)->z());
        // std::cout<<"v["<<i<<"]="<<vo[i]<<std::endl;
    }
    int isize=indices->size();
    std::vector<int> io(isize);
    for (int i=0; i<isize; i++){
        io[i]=indices->Get(i);
        // std::cout<<"i["<<i<<"]="<<io[i]<<std::endl;

    }
    auto faceids=msg->faceIds();

    int fosize=faceids->size();
    std::vector<int> fo(fosize);

    for (int i=0; i<fosize; i++){
        fo[i]=faceids->Get(i);
    }
    std::vector<std::pair<optix::int3,unsigned int> > faces;
    for (int i=0; i<io.size(); i=i+3){
        //  optix::int3 tri=;
        faces.push_back(std::make_pair<optix::int3,unsigned int>(make_int3(io[i],io[i+1],io[i+2]),static_cast<unsigned int>(fo[i])));

    }
    auto id=msg->id();
    auto em=msg->material();
    std::cout<<simTime()<<": Adding dynamic mesh to group "<<id<<std::endl;
    MaterialEMProperties emo=opalRadio->ITUparametersToMaterial(em->a(),em->b(),em->c(),em->d());
    //std::cout<<simTime()<<": MaterialEMProperties"<<emo.dielectricConstant<<std::endl; //Does not work anymore
    opalRadio->addMeshWithFacesToGroup(id,vo, faces, emo);

}

void VenerisServer::finishDynamicMeshGroup() {

    auto msg = readMsg<FinishDynamicMeshGroup>(msg_size);
    CHKOPAL();
    auto id=msg->id();
    opalRadio->finishDynamicMeshGroup(id);
}

void VenerisServer::removeDynamicMeshGroup() {

    auto msg = readMsg<RemoveDynamicMeshGroup>(msg_size);
    CHKOPAL();
    auto id=msg->id();
    std::cout<<simTime()<<": Removing Dynamic mesh group "<<id<<endl;
    opalRadio->removeDynamicMeshGroup(id);
}

void VenerisServer::updateTransformInGroup() {

    auto msg = readMsg<UpdateTransformInGroup>(msg_size);
    CHKOPAL();
    auto tm=msg->transform();
    optix::Matrix4x4 tmo;
    tmo.setRow(0, optix::make_float4(tm->r0().x(),tm->r0().y(),tm->r0().z(),tm->r0().w()));
    tmo.setRow(1, optix::make_float4(tm->r1().x(),tm->r1().y(),tm->r1().z(),tm->r1().w()));
    tmo.setRow(2, optix::make_float4(tm->r2().x(),tm->r2().y(),tm->r2().z(),tm->r2().w()));
    tmo.setRow(3, optix::make_float4(tm->r3().x(),tm->r3().y(),tm->r3().z(),tm->r3().w()));
    auto id=msg->id();
    //std::cout<<"transformation matrix "<<tmo<<" in group "<<id<<std::endl;
    opalRadio->updateTransformInGroup(id, tmo);

}

void VenerisServer::destroyVehicle() {

    auto msg = readMsg<DestroyVehicle>(msg_size);
    auto id =msg->id();

    try {
        VehicleInfo info=activeVehicles.at(id);
        info.module->callFinish();
        //Opal remove radio is called when removing the radio from radio medium in OpalRadioMedium
        info.module->deleteModule();
        activeVehicles.erase(id);
        std::cout<<simTime()<<": Destroying vehicle "<<id<<endl;
    } catch (std::out_of_range e) {
        std::stringstream s;
        s<<"destroyVehicle():: Vehicle "<<id<<" is not registered with opal";
        throw cRuntimeError(s.str().c_str());
        return;
    }


}




void VenerisServer::addOpalEdge() {
    auto msg = readMsg<OpalEdge>(msg_size); //Let message be read to remove from buffers
    CHKOPAL();
    auto p=msg->p();
    auto v=msg->v();
    auto face_a=msg->face_a();
    auto face_b=msg->face_b();
    auto normal_a=msg->normal_a();
    auto normal_b=msg->normal_b();
    auto em=msg->material();
    auto faid=msg->faid();
    auto fbid=msg->fbid();
    auto id=msg->id();
    MaterialEMProperties emo=opalRadio->ITUparametersToMaterial(em->a(),em->b(),em->c(),em->d());
    opalRadio-> addEdge(Vec3ToFloat3(p),Vec3ToFloat3(v),make_uint2(faid,fbid),Vec3ToFloat3(face_a),Vec3ToFloat3(face_b),Vec3ToFloat3(normal_a),Vec3ToFloat3(normal_b),emo,id);



}

void VenerisServer::addOpalEdgeToGroup() {
    auto msg = readMsg<OpalEdgeToGroup>(msg_size); //Let message be read to remove from buffers
    CHKOPAL();
    auto p=msg->p();
    auto v=msg->v();
    auto face_a=msg->face_a();
    auto face_b=msg->face_b();
    auto normal_a=msg->normal_a();
    auto normal_b=msg->normal_b();
    auto em=msg->material();
    auto faid=msg->faid();
    auto fbid=msg->fbid();
    auto id=msg->id();
    auto groupId=msg->groupId();
    //std::cout<<"groupId="<<groupId<<std::endl;
    MaterialEMProperties emo=opalRadio->ITUparametersToMaterial(em->a(),em->b(),em->c(),em->d());
    opalRadio-> addEdgeToGroup(Vec3ToFloat3(p),Vec3ToFloat3(v),make_uint2(faid,fbid),Vec3ToFloat3(face_a),Vec3ToFloat3(face_b),Vec3ToFloat3(normal_a),Vec3ToFloat3(normal_b),emo,id,groupId);


}
optix::float3 VenerisServer::Vec3ToFloat3(const Vec3* v) {
    return make_float3(v->x(), v->y(),v->z());
}

void VenerisServer::registerGain() {
    auto msg = readMsg<RegisterGain>(msg_size); //Let message be read to remove from buffers
    CHKOPAL();
    auto b=msg->path();
    std::string path;
    for (int i=0; i<b->size(); i++){
        path.append(reinterpret_cast<const char*>(b->Get(i)));
    }
    opalRadio->registerAntenna(path);

}

void VenerisServer::raySphereRange() {
    auto msg = readMsg<RaySphereRange>(msg_size); //Let message be read to remove from buffers
    CHKOPAL();
    auto initElevation=msg->initElevation();
    auto elevationDelta=msg->elevationDelta();
    auto endElevation=msg->endElevation();
    auto initAzimuth=msg->initAzimuth();
    auto azimuthDelta=msg->azimuthDelta();
    auto endAzimuth=msg->endAzimuth();

    opalRadio->createRaySphere2D(initElevation, elevationDelta, endElevation, initAzimuth, azimuthDelta, endAzimuth);



}

void VenerisServer::setRDNRayRange() {
    auto msg = readMsg<RDNRayRange>(msg_size); //Let message be read to remove from buffers
    CHKOPAL();
    auto initElevation=msg->initElevation();
    auto endElevation=msg->endElevation();
    auto initAzimuth=msg->initAzimuth();
    auto endAzimuth=msg->endAzimuth();
    auto rdnRays = msg->rayD();
    opalRadio->setRayRange(initElevation,endElevation,initAzimuth,endAzimuth,rdnRays,rdnRays);
}

void VenerisServer::registerReceiverGain() {
    auto msg = readMsg<RegisterReceiverGain>(msg_size); //Let message be read to remove from buffers
    CHKOPAL();
    auto rxId=msg->rxId();
    auto gainId=msg->gainId();
    opalRadio->registerReceiverGain(rxId, gainId);

}


void VenerisServer::processMessage(Veneris::Communications::VenerisMessageTypes type, uint32_t size) {
    ExecutionServer::processMessage(type,size);
    if (type==Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_ExternalTime) {
        return;
    }
    switch (type) {
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_ConfigOpal:
        configOpal();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_StaticMeshWithFaces:
        addStaticMeshWithFaces();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_OpalEdge:
        addOpalEdge();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_OpalEdgeToGroup:
        addOpalEdgeToGroup();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_RegisterGain:
        registerGain();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_RegisterReceiverGain:
        registerReceiverGain();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_RaySphereRange:
        raySphereRange();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_RDNRayRange:
        setRDNRayRange();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_UseOpal:
        createOpal();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_StaticMesh:
        addStaticMesh();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_StaticCurvedMesh:
        addStaticCurvedMesh();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_FinishOpalContext:
        finishOpalContext();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_End:
        endServer();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_Create:
        createVehicle();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_Destroy:
        destroyVehicle();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_VehicleState:
        updateVehicleState();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_AddDynamicMeshGroup:
        addDynamicMeshGroup();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_DynamicMesh:
        addDynamicMesh();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_DynamicMeshWithFaces:
        addDynamicMeshWithFaces();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_UpdateTransformInGroup:
        updateTransformInGroup();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_RemoveDynamicMeshGroup:
        removeDynamicMeshGroup();
        break;
    case Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_FinishDynamicMeshGroup:
        finishDynamicMeshGroup();
        break;
    default:
        std::cout<<"VenerisServer::processMessage(): Unknown message type "<<type<<std::endl;

        EV_ERROR<<"VenerisServer::processMessage(): Unknown message type "<<type<<std::endl;
        endServer();
    }
}

} //namespace
