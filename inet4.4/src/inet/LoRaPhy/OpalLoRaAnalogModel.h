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

#ifndef __FLORA_OPALLORAANALOGMODEL_H_
#define __FLORA_OPALLORAANALOGMODEL_H_

#include "inet/physicallayer/wireless/common/medium/RadioMedium.h"
#include "LoRaAnalogModel.h"
#include "OpalLoRaRadioMedium.h"
#include "inet/physicallayer/wireless/common/analogmodel/packetlevel/ScalarReception.h"
#include "inet/common/IPrintableObject.h"
#include "Opal.h"

using namespace omnetpp;
using namespace opal;

/**
 * TODO - Generated class
 */
namespace inet {

namespace physicallayer {

class INET_API OpalLoRaAnalogModel : public LoRaAnalogModel
{
protected:
    virtual void initialize(int stage);
    virtual W computeReceptionPower(const IRadio *radio, const ITransmission *transmission, const IArrival *arrival) const override;
    OpalLoRaRadioMedium *analogModel;
};


} // namespace physicallayer

} // namespace inet

#endif // ifndef __INET_SCALARANALOGMODEL_H
