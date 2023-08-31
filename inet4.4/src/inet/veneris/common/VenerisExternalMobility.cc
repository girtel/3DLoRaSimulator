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

#include "VenerisExternalMobility.h"

namespace inet {

Define_Module(VenerisExternalMobility);

void VenerisExternalMobility::initialize(int stage)
{
    MobilityBase::initialize(stage);
    nextChange=-1;
    //Do not call MovingMovilityBase::initialize. We do not use timers to schedule position updates

    // TODO - Generated method body
}

void VenerisExternalMobility::initializePosition() {
   // std::cout<<"Calling initializePosition"<<std::endl;
    //Do not do anything, otherwise we spoil VenerisServer setting of initial position
    //lastPosition=getRandomPosition();
}

void VenerisExternalMobility::setPosition(float x, float y, float z) {
    lastPosition.setX(x);
    lastPosition.setY(y);
    lastPosition.setZ(z);
    lastUpdate=simTime();
    emitMobilityStateChangedSignal();
}

void VenerisExternalMobility::setVelocity(float x, float y, float z) {
    lastVelocity.setX(x);
    lastVelocity.setY(y);
    lastVelocity.setZ(z);
    lastUpdate=simTime();
    emitMobilityStateChangedSignal();
}

void VenerisExternalMobility::setAcceleration(float x, float y, float z) {
    lastAcceleration.setX(x);
    lastAcceleration.setY(y);
    lastAcceleration.setZ(z);
    lastUpdate=simTime();
    emitMobilityStateChangedSignal();
}

void VenerisExternalMobility::move() {
    //Do not do anything;
}

void VenerisExternalMobility::refreshDisplay() const {
    //WARNING:Unity uses a left-handed coordinate system with Y axis as up, whereas INET uses Z axis as up
            //if meshes have been exported from Unity, or coordinates are provided by Unity, we have to interchange axis, to keep everything consistent
            //Transformation matrices coming from Unity also have to be kept consistent
            //Otherwise, we can just keep the INET coordinates

     //At the moment, since I am using Unity meshes, I switch axis just for representation purposes, otherwise, all the coordinates kept according to Unity
    DirectiveResolver directiveResolver(const_cast<VenerisExternalMobility *>(this));
      auto text = format.formatString(&directiveResolver);
      cDisplayString& displayString = this->getDisplayString();
      displayString.setTagArg("t", 0, text);
      if (subjectModule != nullptr && par("updateDisplayString")) {
          auto realposition = const_cast<VenerisExternalMobility *>(this)->getCurrentPosition();
          EV_TRACE << "current position = " << realposition << endl;
          Coord position=realposition;
          double y=position.y;
          position.y=position.z;
          position.z=y;

          EV_TRACE << "display current position = " << position << endl;
          auto subjectModulePosition = canvasProjection->computeCanvasPoint(position);
          char buf[32];
          snprintf(buf, sizeof(buf), "%lf", subjectModulePosition.x);
          buf[sizeof(buf) - 1] = 0;
          subjectModule->getDisplayString().setTagArg("p", 0, buf);
          snprintf(buf, sizeof(buf), "%lf", subjectModulePosition.y);
          buf[sizeof(buf) - 1] = 0;
          subjectModule->getDisplayString().setTagArg("p", 1, buf);
      }
}

Coord& VenerisExternalMobility::getCurrentPosition() {
    return lastPosition;
}

Coord& VenerisExternalMobility::getCurrentVelocity() {
    return lastVelocity;
}

Quaternion& VenerisExternalMobility::getCurrentAngularPosition() {
     return lastOrientation;
}

Quaternion& VenerisExternalMobility::getCurrentAngularVelocity() {
    return lastAngularVelocity;
}

Coord& VenerisExternalMobility::getCurrentAcceleration() {
    return lastAcceleration;
}

} //namespace
