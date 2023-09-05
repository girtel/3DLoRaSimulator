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

#include "OpalLinearPolarizationAntenna.h"
#include "inet/common/ModuleAccess.h"
#include "inet/mobility/base/MobilityBase.h"
namespace inet {
namespace physicallayer {
simsignal_t OpalLinearPolarizationAntenna::mobilityStateChangedSignal = cComponent::registerSignal("mobilityStateChanged");

Define_Module(OpalLinearPolarizationAntenna);

OpalLinearPolarizationAntenna::OpalLinearPolarizationAntenna() : AntennaBase(), gain(makeShared<AntennaGain>())
{

}

void OpalLinearPolarizationAntenna::initialize(int stage)
{
    AntennaBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        initialPolarization.x=par("polarizationX");
        initialPolarization.y=par("polarizationY");
        initialPolarization.z=par("polarizationZ");
        polarization=initialPolarization;


        getContainingNode(this)->subscribe(mobilityStateChangedSignal, this);
        useAntennaGain=par("useAntennaGain").boolValue();
        if (useAntennaGain) {
            gainFilePath = par("gainFilePath").stdstringValue();

        }
    }
}
 std::ostream& OpalLinearPolarizationAntenna::printToStream(std::ostream& stream, int level, int evFlags) const
{
    stream << "OpalLinearPolarizationAntenna";
    if (level <= PRINT_LEVEL_DETAIL)
        stream << ", Polarization = " << polarization;
    return AntennaBase::printToStream(stream, level);
}

Coord OpalLinearPolarizationAntenna::getPolarization() const {
    return polarization;
}

void OpalLinearPolarizationAntenna::receiveSignal(cComponent* source,
        simsignal_t signal, cObject* value, cObject* details) {
    //At the moment, apply changes of orientation here
        if (signal==mobilityStateChangedSignal) {
              MobilityBase* mob=check_and_cast<MobilityBase*>(value);
              Quaternion orientation=mob->getCurrentAngularPosition();
              polarization=orientation.rotate(initialPolarization);
        }
}

}
}//namespace
