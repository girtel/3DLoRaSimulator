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

#ifndef __INET_VENERISEXTERNALMOBILITY_H_
#define __INET_VENERISEXTERNALMOBILITY_H_

#include <omnetpp.h>
#include "inet/mobility/base/MovingMobilityBase.h"
using namespace omnetpp;

namespace inet {

/**
 * A mobility class to adapt OMNET positions to Unity positions. Could be extended with additional information
 */
class VenerisExternalMobility : public MovingMobilityBase
{
protected:
    Coord lastAcceleration;
    virtual void initialize(int stage) override;
    /** @brief Initializes mobility position. */
    virtual void initializePosition() override;
    virtual void move() override;

    /** @brief Moves the visual representation module's icon to the new position on the screen. */
    virtual void refreshDisplay() const override;
public:
    //Override to avoid emitting signals continuosly
    virtual Coord& getCurrentPosition() override;
    virtual Coord& getCurrentVelocity() override;
    virtual Quaternion& getCurrentAngularPosition() override;
    virtual Quaternion& getCurrentAngularVelocity() override;
    void setPosition(float x, float y, float z);
    void setVelocity(float x, float y, float z);
    void setAcceleration(float x, float y, float z);
    virtual Coord& getCurrentAcceleration() override;

};

} //namespace

#endif
