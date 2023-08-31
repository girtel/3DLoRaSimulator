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

package inet.veneris.common;
//
// TODO auto-generated module
//
simple VenerisServer extends ExecutionServer
{
    parameters:
        @class(VenerisServer);
        string opalModule = default("inet.veneris.opal.OpalRadioMedium");

        //Modules to be used with Opal need, must have at least an id and receptionRadius parameters. Any other submodule can be used inside
        string vehicleModule = default("inet.veneris.opal.test.OpalNode");

        string mobilityModule = default("inet.common.veneris.VenerisExternalMobility");

        bool forceNotUsingOpal = default(false); //Ignore Opal-related messages. Useful to replay with different propagation modules from a file with Opal messages.
        bool overrideConfigurationMessage = default(false); //Ignore Opal configuration message. Use to replay from a file with Opal messages and different configurations
        int maxReflections = default(10);
        double carrierFrequency @unit(Hz) = default(5.9 GHz);
        bool printEnabled = default(false);
        double minEpsilon = default(1e-3);

}
