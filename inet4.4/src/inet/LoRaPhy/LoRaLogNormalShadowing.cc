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

#include "LoRaLogNormalShadowing.h"
#include "inet/common/INETMath.h"

namespace inet {

Define_Module(LoRaLogNormalShadowing);

LoRaLogNormalShadowing::LoRaLogNormalShadowing()
{
}

void LoRaLogNormalShadowing::initialize(int stage)
{
    FreeSpacePathLoss::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        sigma = par("sigma");
        gamma = par("gamma");
        d0 = m(par("d0"));
    }
}

std::ostream& LoRaLogNormalShadowing::printToStream(std::ostream& stream, int level, int evFlags) const
{
    stream << "LoRaLogNormalShadowing";
    if (level <= PRINT_LEVEL_TRACE)
        stream << ", alpha = " << alpha
               << ", systemLoss = " << systemLoss
               << ", sigma = " << sigma;
    return stream;
}

double LoRaLogNormalShadowing::computePathLoss(mps propagationSpeed, Hz frequency, m distance, double transmitterHeight, double receiverHeight) const
{
    // parameters taken from paper "Do LoRa Low-Power Wide-Area Networks Scale?"
    double PL_d0_db = -91.74;
    //    double PL_db = PL_d0_db + 10 * gamma * log10(unit(distance / d0).get()) + normal(14.33, sigma);
    //    double PL_db = PL_d0_db + 10 * gamma * log10(unit(distance / d0).get()) + normal(0.0, sigma);
    // double PL_db = - 10 * gamma * log10(distance.get()) + normal(0.0, sigma) - 57.1769779;
    // double PL_db = -65.1709 - 10 * gamma * log10(distance.get()) + normal(0.0, sigma) - 64.8435;

    double PL_db = -14 - 10 * gamma * log10(distance.get()) - 5.881 + normal(0.0, sigma);
    // double PL_db = PL_d0_db + 10 * gamma * log10(unit(distance / d0).get()) + normal(0.0, sigma);
    // std::cout << PL_db << std::endl;
    return math::dB2fraction(PL_db);
}

m LoRaLogNormalShadowing::computeRange(W transmissionPower) const
{
    // parameters taken from paper "Do LoRa Low-Power Wide-Area Networks Scale?"
    double PL_d0_db = 91.74;
    double max_sensitivity = -137;
    double trans_power_db = round(10 * log10(transmissionPower.get() * 1000));
    EV << "LoRaLogNormalShadowing transmissionPower in W = " << transmissionPower << " in dBm = " << trans_power_db << endl;
    double rhs = (trans_power_db - PL_d0_db - max_sensitivity) / (10 * gamma);
    double distance = d0.get() * pow(10, rhs);
    return m(distance);
}
}
