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

//
// TODO auto-generated module
//
module OpalLoRaRadioMedium extends LoRaMedium
{
    parameters:
        @class(OpalLoRaRadioMedium);
        
        bool isStatic = default(false);
		string simulationType=default("Depolarization"); //Depolarization, Basic, RDN, Diffraction
        bool useDiffraction=default(true); //Diffraction can be used together with Depolarization, Basic and RDN. If Diffraction is used as simulationType only diffraction is computed
        string computeMode=default("Voltage"); //Voltage, Field
        int maxNumberOfReflections = default(10);
        double carrierFrequency @unit(Hz) = default(868MHz);
        double receptionRadius @unit(m) = default(1m);
        bool logTrace=default(false);
        bool useExactSpeedOfLight=default(true);
        bool generateRaysOnLaunch=default(true);
        bool enableMultiGPU=default(true);
        bool depolarization=default(true);
        bool enableFastMath=default(true);
        bool useAntennaGain=default(false);
        bool useOpalReport=default(false);
        string antennaGainFilePaths = default(""); //A file with a list of paths to antenna gain files as defined in Opal 
        //Only used with RDN
        int rdnRays=default(1000); //square root of total number of rays per solid angle. With 1000, we use 1 million rays
        int rdnFiltering = default(2); //Type of filtering used by RDN: 0-no filtering, 1-ignoring rays below expected density 2-not dividing by low density
        int rdnExecutionMode = default(1); //0-HitInfo, 1-No memory, 2-No atomic //Use 0 or 1 generally
        //
        //Ray generation
        double initAzimuth=default(0.0);
        double azimuthDelta = default(1.0); 				//For RDN azimuthDelta and elevationDelta are not used, the solid angle is given by init/end of azimuth and elevation 
        double endAzimuth=default(360.0);
        double initElevation=default(0.0);
        double elevationDelta = default(1.0);
        double endElevation=default(180.0);
        bool useDecimalDegreeDelta= default(false);
       
       //Utility to load scenario locally instead of receiving it from Veneris server
        bool loadMeshesFromFile = default(false);
        bool loadEdgesFromFile = default(false);
        string meshesPath = default("");
        string meshesFileList = default(""); //List of meshes names
        string meshes = default("");
        string edgesPath = default("");
        string edgesFileList = default(""); //List of meshes names
        
        bool useJson = default(false);
        bool useServer = default(false);

        
        string jsonFilePath = default("");
       
        double minEpsilon = default(0.001);
        analogModel.typename = default("ScalarAnalogModel");
        backgroundNoise.typename = default("IsotropicScalarBackgroundNoise");
        propagation.typename = default("ConstantSpeedPropagation");
        pathLoss.typename = default("FreeSpacePathLoss"); //Not actually using path loss, propagation is computed by Opal, but we need to provide some module
        backgroundNoise.power = default(-110dBm);
        mediumLimitCache.carrierFrequency = default(868MHz);
        mediumLimitCache.minReceptionPower = default(-85dBm);
        mediumLimitCache.minInterferencePower = default(-110dBm);
}
