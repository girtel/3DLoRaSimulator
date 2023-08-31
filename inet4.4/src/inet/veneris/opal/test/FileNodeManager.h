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

#ifndef INET_APPLICATIONS_VEHICULAR_FILENODEMANAGER_H_
#define INET_APPLICATIONS_VEHICULAR_FILENODEMANAGER_H_

#include <omnetpp.h>
#include "inet/common/InitStages.h"

using namespace omnetpp;

namespace inet {

class FileNodeManager : public cSimpleModule
{
public:
    virtual int getNumberOfNodes();
protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override {return NUM_INIT_STAGES;}

    std::string moduleType; /**< module type to be used in the simulation for each managed vehicle */
    std::string moduleName; /**< module name to be used in the simulation for each managed vehicle */
    std::string moduleDisplayString; /**< module displayString to be used in the simulation for each managed vehicle */
    double maxX;
    double separation;

    int nodeVectorIndex;
};

} /* namespace inet */

#endif /* INET_APPLICATIONS_VEHICULAR_FILENODEMANAGER_H_ */
