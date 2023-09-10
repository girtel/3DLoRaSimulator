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

#include "HataOkumura.h"

namespace inet {

Define_Module(HataOkumura);

HataOkumura::HataOkumura()
{
}

void HataOkumura::initialize(int stage)
{
    FreeSpacePathLoss::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        K1 = par("K1");
        K2 = par("K2");
        small = par("small");
        suburban = par("suburban");
        GW = par("GW");
        Node = par("Node");
    }
}

std::ostream& HataOkumura::printToStream(std::ostream& stream, int level, int evFlags) const
{
    stream << "HataOkumura";
    return stream;
}

double HataOkumura::computePathLoss(mps propagationSpeed, Hz frequency, m distance) const
{
    double ahed;
    double A;
    double B;
    double PL_db;
    /*if(receiverHeight == 38.31) {
        std::cout << transmitterHeight << std::endl;
        std::cout << receiverHeight << std::endl;
    }*/
    // receiverHeight = receiverHeight - transmitterHeight + 1.5;
    double rH = 24.24; // Altura de referencia.
    //transmitterHeight = 1.5;
    double tH = 1.5;
    if(small){
        ahed = 0.8 + (1.1 * log10(frequency.get() / 1000000) - 0.7) * tH - 1.56 * log10(frequency.get() / 1000000);
        //std::cout << "Small Configuration" << std::endl;
    }
    else {
        if(frequency.get()/1000000 < 200) {
            ahed = 8.29 * pow(log10(1.54 * tH),2) - 1.1;
            //std::cout << "Less 200MHz Configuration" << std::endl;
        }
        else {
            ahed = 3.2 * pow(log10(11.75 * tH),2) - 4.97;
            //std::cout << "More 200MHz Configuration" << std::endl;
        }
    }

    A = 69.55 + 26.16 * log10(frequency.get() / 1000000) - 13.82 * log10(rH);
    B = 44.9 - 6.55 * log10(rH);

    //std::cout << "-- A:" << A << "\n-- B:" << B << "\n-- ahed: " <<  ahed << std::endl;

    PL_db = A - ahed + B * log10(distance.get()/1000);

    if(suburban == 1) {
        PL_db = PL_db - 2 * pow(log10(frequency.get() / (1000000 * 28)),2) - 5.4;
        //std::cout << "Suburban 1" << std::endl;
    }
    else if (suburban == 2) {
        PL_db = PL_db - 4.78 * pow(log10(frequency.get() / 1000000),2) + 18.33 * log10(frequency.get() / 1000000) - 40.94;
        //std::cout << "Suburban 2" << std::endl;
    }

    //PL_db = 127.09 + 35.74 * log10(distance.get()/1000);

    //std::cout << "-- Hata Okumura --" << "\n-- Distance: " << distance.get()/1000 << "\n-- Freq: "<< frequency.get()/1000000 <<" \n-- receiverHeight: " << rH << " \n-- transmitterHeight: " << tH << " \n-- power: " << math::dB2fraction(-PL_db) << std::endl;
    // std::cout << "HO" << std::endl;
    // build based on documentation from Actility
    return math::dB2fraction(-PL_db);
}

}
