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

package inet.examples.opal;
import inet.physicallayer.wireless.common.contract.packetlevel.IRadioMedium;
import inet.veneris.opal.OpalNode;
import inet.veneris.opal.test.INodeManager;


network OpalNodeManager
{
    parameters:
        @display("bgb=1400,400");
        @statistic[receptionPower](source="receptionMinSignalPower(radioMedium.signalArrivalStarted)"; record=last,vector);
        int nodes = default(2);
    submodules:
        node[nodes]: OpalNode {
            @display("p=144.37871,110.05918");
            id = index;
        }
        nodeManager: <default("")> like INodeManager if typename != "" {
            @display("p=170,50;is=vs");
        }


        radioMedium: <default("Ieee80211ScalarRadioMedium")> like IRadioMedium {
            @display("p=49.704147,85.20711");
        }

}
