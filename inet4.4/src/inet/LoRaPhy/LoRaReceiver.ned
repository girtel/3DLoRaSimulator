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

package inet.LoRaPhy;

package inet.physicallayer.wireless.common.base.packetlevel;
import inet.physicallayer.wireless.common.base.packetlevel.NarrowbandReceiverBase;

//
// TODO auto-generated module
//
 module LoRaReceiver extends NarrowbandReceiverBase
 {
        parameters:
        @signal[LoRaReceivedPower](type=double); // Potencia recibida
        @statistic[LoRaReceivedPower](source=LoRaReceivedPower; record=mean,vector);
        
        @signal[LoRaRP*From*](type=double); // note the wildcard
		@statisticTemplate[LoRaRP](record=mean,vector);  
		
        @signal[LoRaReceptionCollision](type=bool); // optional
        @statistic[LoRaReceptionCollision](source=LoRaReceptionCollision; record=count);
        errorModel.typename = default("");
        modulation = default("BPSK"); // not used for the lora module 
        bool alohaChannelModel = default(false);
        @class(LoRaReceiver);
        @display("i=block/wrx");
}
