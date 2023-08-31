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

#ifndef __INET_OPALLINEARPOLARIZATIONANTENNA_H_
#define __INET_OPALLINEARPOLARIZATIONANTENNA_H_

#include <omnetpp.h>
#include "inet/common/INETDefs.h"
#include "inet/physicallayer/wireless/common/base/packetlevel/AntennaBase.h"

using namespace omnetpp;
using namespace inet::physicallayer;
namespace inet {

/**
 * TODO - Generated class
 */
class INET_API OpalLinearPolarizationAntenna : public AntennaBase, public cListener
{

  protected:
    //Use a isotropic here in order not to add a gain in addition to Opal
      class AntennaGain : public IAntennaGain
      {
        public:
          virtual double getMinGain() const override { return 1; }
          virtual double getMaxGain() const override { return 1; }
          virtual double computeGain(const Quaternion& direction) const override { return 1; }
      };

    Ptr<AntennaGain> gain;
    Coord initialPolarization;
    Coord polarization;
    bool useAntennaGain;

    std::string gainFilePath; //Gain is going to be used for transmision and reception
    virtual void initialize(int stage) override;

  public:
    OpalLinearPolarizationAntenna();
    //Subscribe to position changes
    static simsignal_t mobilityStateChangedSignal;
    virtual Coord getPolarization() const;
    virtual std::ostream& printToStream(std::ostream& stream, int level, int evFlags = 0) const override;
    virtual Ptr<const IAntennaGain> getGain() const override { return  gain; }
    //Receive mobility signals to update polarizations in Opal
    virtual void receiveSignal(cComponent *source, simsignal_t signal, cObject *value, cObject *details) override;
    virtual bool useGain() const { return useAntennaGain;};
    virtual std::string getGainFilePath() const { return gainFilePath;};

};

} //namespace

#endif
