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

package inet.veneris.opal;

import inet.physicallayer.wireless.common.medium.RadioMedium;
//
// TODO auto-generated module
//
module OpalRadioMedium extends RadioMedium
{
    parameters:
        @class(physicallayer::OpalRadioMedium);
        
        string simulationType=default("Depolarization"); //Depolarization, Basic, RDN, Diffraction
        bool useDiffraction=default(true); //Diffraction can be used together with Depolarization, Basic and RDN. If Diffraction is used as simulationType only diffraction is computed
        string computeMode=default("Voltage"); //Voltage, Field
        int maxNumberOfReflections = default(10);
        double carrierFrequency @unit(Hz) = default(5.9GHz);
        double receptionRadius @unit(m) = default(1m);
        bool logTrace=default(false);
        bool useExactSpeedOfLight=default(true);
        bool generateRaysOnLaunch=default(true);
        bool enableMultiGPU=default(true);
        bool depolarization=default(true);
        bool enableFastMath=default(true);
        bool useAntennaGain=default(false);
        string antennaGainFilePaths = default(""); //A file with a list of paths to antenna gain files as defined in Opal 
        //Only used with RDN
        int rdnRays=default(1000); //square root of total number of rays per solid angle. With 1000, we use 1 million rays
        int rdnFiltering = default(2); //Type of filtering used by RDN: 0-no filtering, 1-ignoring rays below expected density 2-not dividing by low density
        int rdnExecutionMode = default(1); //0-HitInfo, 1-No memory, 2-No atomic //Use 0 or 1 generally
        //
        //Ray generation
        double initAzimuth=default(0.0);
        double azimuthDelta = default(0.1); //For RDN azimuthDelta and elevationDelta are not used, the solid angle is given by init/end of azimuth and elevation 
        double endAzimuth=default(360.0);
        double initElevation=default(0.0);
        double elevationDelta = default(0.1);
        double endElevation=default(180.0);
        bool useDecimalDegreeDelta= default(false);
       
       //Utility to load scenario locally instead of receiving it from Veneris server
       	bool useServer = default(false);
       	//Switch Y axis: Unity uses Y as "up", while omnet tend to use Z. It is usually preferrable not to swicht and keep
       	//everything consistent, that is, for instance if the scenario comes from Opal/Veneris, make omnet nodes movement/position using Y as "Up"  
       	bool switchCoordinates =default(false);
       	
       	//To emit a signal with the electric field in addition o the power
       	bool recordElectricField=default(false);
       	bool useJson = default(true);
       	string jsonFilePath = default(""); //Preferred way to load scenarios
        bool loadMeshesFromFile = default(false);
        bool loadEdgesFromFile = default(false);
        string meshesPath = default("");
        string meshesFileList = default(""); //List of meshes names
        string meshes = default("");
        string edgesPath = default("");
        string edgesFileList = default(""); //List of meshes names
        
        //Optimization to be used when all the EM interactable elements in the environment are static and the nodes always transmit with same power, frequency and polarization
        //Nodes can move (as long as they do not have any attached interactable element)
        //In doubt keep it false
        bool isStatic=default(false);
       
        double minEpsilon = default(0.001);
        
        //Used to record on a  CSV info of individual rays that hit on a receiver, to compute delay profiels or RMS delay spread or other 
        //Warning: intended to be used just with one or a few transmissions, the size of the files can be very large as well and there is at least one file per receiver and transmitter
        bool recordHits = default(false);
        //path to save csv hit files
        string hitFilesPath=default("hitFiles");
        
        analogModel.typename = default("ScalarAnalogModel");
        backgroundNoise.typename = default("IsotropicScalarBackgroundNoise");
        propagation.typename = default("ConstantSpeedPropagation");
        pathLoss.typename = default("FreeSpacePathLoss"); //Not actually using path loss, propagation is computed by Opal, but we need to provide some module
        backgroundNoise.power = default(-110dBm);
        mediumLimitCache.carrierFrequency = default(5.9GHz);
        mediumLimitCache.minReceptionPower = default(-85dBm);
        mediumLimitCache.minInterferencePower = default(-110dBm);
        @signal[electricFieldRealSignal](type=double);
        @signal[electricFieldImaginarySignal](type=double);
        
        @statisticTemplate[electricFieldReal](record=vector);
        @statisticTemplate[electricFieldImaginary](record=vector);
}
