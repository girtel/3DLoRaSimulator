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

#ifndef __INET4_OpalLoRaRadioMedium_H_
#define __INET4_OpalLoRaRadioMedium_H_

#include <omnetpp.h>
#include "inet/physicallayer/wireless/common/medium/RadioMedium.h"
#include "LoRaMedium.h"
#include "inet/physicallayer/wireless/common/analogmodel/packetlevel/ScalarReception.h"
#include "inet/common/IPrintableObject.h"
#include "Opal.h"
#include <unordered_set>
using namespace omnetpp;
using namespace opal;
namespace inet::physicallayer {

    /**
     * TODO - Generated class
     */
    class OpalLoRaRadioMedium; //forward declaration

   /* class FieldComponent: public cObject {
    public:
        FieldComponent(double r, double i);
        double re;
        double im;
    };
*/

    //Class that will be notified by Opal when some transmission is received
    class OpalReceiverCallback : public IPrintableObject {
    public:
        OpalReceiverCallback(OpalLoRaRadioMedium* medium ,int id, const IRadio* radio);

        OpalLoRaRadioMedium* myMedium;
        bool hasReceivedPower;
        int opalReceiverId;
        float lastPower;
        int lastTransmitterId;
        float rxRadius;
        const ITransmission *transmission;
        std::string hitFilesPath;
        //Callback methods
        void operator()(float p, int id);
        void getPower(float p, int id);
        void createReception(float p, int id);
        void getField(ResultRecord r, int id);
        void saveHits(ResultRecord rr, int id);
        void reset();
        const IRadio* radio;
        virtual std::ostream& printToStream(std::ostream& stream, int level) const {
            stream << "opalReceiverId=" << opalReceiverId << ",hasReceivedPower=" << hasReceivedPower<<",lastPower="<<lastPower<<",lastTransmissionId="<<lastTransmitterId; // no endl!
            return stream;
        }
        std::function<void(float,int)> myCallback;
        std::function<void(ResultRecord,int)> extendedCallback;


    };

    //Uses OpalSceneManager because we only consider single transmitter (and multiple receivers). Computation of multi transmitter in
    //parallel requires further changes and it is complex in the INET context (if possible at all) since it requires delayed
    //computation of received power. But then one cannot know if the radio should change to reception mode...

    class INET_API OpalLoRaRadioMedium : public LoRaMedium, public OpalSceneManager
    {





    protected:



        OpalSimulation* sim;

        //Parameters to be passed to Opal
        std::string simulationType;
        std::string computeMode;
        double  carrierFrequency;
        float receptionRadius;
        bool useServer;
        bool useJson;
        double initAzimuth;
        double azimuthDelta;
        double endAzimuth;
        double initElevation;
        double elevationDelta;
        double endElevation;
        int maxNumberOfReflections;
        int rdnRays;
        bool loadFromFiles;
        bool useDiffraction;
        bool generateRaysOnLaunch;
        bool enableMultiGPU;
        bool depolarization;
        bool enableFastMath;
        bool useExactSpeedOfLight;
        bool useAntennaGain;
        bool logTrace;
        bool switchCoordinates;
        bool useExtendedCallback;
        bool recordHits;
        std::string hitFilesPath;


        std::map<const IRadio*, OpalReceiverCallback*> receiversRadios;




        //Pending transmissions
        std::map<int, int> pendingTransmissions; //transmissionId, opalId;

        //Location of Optix Programs: change to your source directory (can be read as a parameter)
        //Leave  empty to use default directory: optix SDK opal sample directory
        const char* cudaDir = "";


        //Optimize for static environments
        bool isStatic;
        typedef struct {float power; ResultRecord rr;} CachedPowerData;
        typedef std::map<const IRadio*,CachedPowerData> CachedPowerEntry; //Received powers for a given receiver
        typedef std::map<const IRadio*, CachedPowerEntry*> CachedPowerMap;  //Received powers from a given transmitter to all receivers

        CachedPowerMap mapReceptions;



        virtual void initialize(int stage);
        virtual int numInitStages() const override { return NUM_INIT_STAGES; }



        void transmitInOpal(const IRadio *radio, const ITransmission *transmission);
       void  transmitStatic(const IRadio *radio, const ITransmission *transmission );

        void loadAntennaGainFiles();

        //Keep map of registered antenna gains
        std::map<std::string,int> registeredGains;


        //Utility methods to load simple scenarios
        void loadMeshesFromFiles();
        void loadEdgesFromFiles();
        //std::vector<optix::float3> loadVerticesFromFile(const char* file);
        //std::vector<int>  loadTrianglesFromFile(const char* file);
        optix::Matrix4x4 loadTransformFromFile(const char* file);
        MaterialEMProperties loadEMFromFile(const char* file);
        void loadEdgeFromFile(const char* file);
        std::vector<std::pair<optix::int3,unsigned int> > loadFaceIdsFromFile(std::ifstream& infile);
        optix::float3 readFloat3(std::string line);
        optix::float4 readFloat4(std::string line);
        optix::int4 readInt4(std::string line);
        //Transmission methods

        virtual  void sendToAffectedRadios(IRadio *transmitter, const IWirelessSignal *signal) override;

    public:
        static simsignal_t electricFieldRealSignal;
        static simsignal_t electricFieldImaginarySignal;

        OpalLoRaRadioMedium();
        virtual ~OpalLoRaRadioMedium();

        virtual const W opalComputeReception(const IRadio *receiver, const ITransmission *transmission) const;

        //Translate Opal to OMNET coordinates
        optix::float3 getOpalCoordinates(Coord c) const;
        //Add  a new transceiver
        virtual void addRadio(const IRadio *radio) override;
        //Remove a transceiver
        virtual void removeRadio(const IRadio *radio) override;
        //Transmit packet with Opal
        virtual IWirelessSignal *transmitPacket(const IRadio *radio, Packet *packet)  override;
        //Send to all radios
        //virtual void sendToRadio(IRadio *trasmitter, const IRadio *receiver, const ISignal *signal) override;
        virtual void sendToRadio(IRadio *trasmitter, const IRadio *receiver, const IWirelessSignal *signal) override;
        //Finish context and build scene
        void finishOpalContext();
        //Receive mobility signals to change receivers positions in Opal
        virtual void receiveSignal(cComponent *source, simsignal_t signal, cObject *value, cObject *details) override;
        //Get gain id from path
        virtual  int getAntennaGainId(std::string path);
        void registerAntenna(std::string line);
        void updateCachedRecord(const IRadio *receiver, const ITransmission *transmission, ResultRecord record);
        void clearPowerCache();
    };

} //namespace

#endif
