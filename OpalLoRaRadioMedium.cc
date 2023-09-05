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

#include "OpalRadioMedium.h"
#include "basicSimulation.h"
#include "flatSimulation.h"
#include "rayDensityNormalizationSimulation.h"
#include "singleDiffraction.h"
#include "util.h"


#include "inet/veneris/opal/OpalLinearPolarizationAntenna.h"
#include "inet/common/ModuleAccess.h"
#include "inet/mobility/base/MobilityBase.h"
#include "inet/physicallayer/wireless/common/communicationcache/VectorCommunicationCache.h"
#include "inet/mobility/contract/IMobility.h"
#include "inet/physicallayer/wireless/common/base/packetlevel/NarrowbandTransmissionBase.h"

#include <functional>
using namespace opal;
namespace inet::physicallayer {

    Define_Module(OpalRadioMedium);

    simsignal_t OpalRadioMedium::electricFieldRealSignal=cComponent::registerSignal("electricFieldRealSignal");
    simsignal_t OpalRadioMedium::electricFieldImaginarySignal=cComponent::registerSignal("electricFieldImaginarySignal");

    /*
    FieldComponent::FieldComponent(double r, double i ){
        this->re=r;
        this->im=i;

    }*/

    OpalReceiverCallback::OpalReceiverCallback(OpalRadioMedium* medium, int id, const IRadio* radio) {
        this->myMedium=medium;
        this->opalReceiverId=id;
        this->radio=radio;
        this->rxRadius=1.0f;
        this->lastPower=0.0f;
        this->lastTransmitterId=-1;
        this->hasReceivedPower=false;
        this->transmission=nullptr;
        this->hitFilesPath=".";
        //Set the callback to be called among the suitable members of this class, or add your own custom callback
        this->myCallback=std::bind(&inet::physicallayer::OpalReceiverCallback::createReception, this, std::placeholders::_1,std::placeholders::_2);
        this->extendedCallback=std::bind(&inet::physicallayer::OpalReceiverCallback::getField, this, std::placeholders::_1,std::placeholders::_2);


    }
    void OpalReceiverCallback::operator()(float p, int id)  {
        //  std::cout<<"OpalReceiverCallback["<< opalReceiverId<<"].p="<<p<<"transmitter id="<<id<<std::endl;
        this->lastPower=p;
        this->lastTransmitterId=id;
        this->hasReceivedPower=true;
        //std::cout<<"OpalReceiverCallback["<< opalReceiverId<<"].p="<<this->lastPower<<"transmissionId="<<this->lastTransmissionId<<"hasReceivedPower="<<this->hasReceivedPower<<std::endl;
        //printf("Address of this is %p\n", (void *)this);
    }
    void OpalReceiverCallback::getPower(float p, int id)  {

        this->lastPower=p;
        this->lastTransmitterId=id;
        this->hasReceivedPower=true;

        //printf("Address of this is %p\n", (void *)this);
    }
    void OpalReceiverCallback::createReception(float p, int id)  {
        //With this callback we create a new Reception when power is received
        std::cout<<"OpalReceiverCallback["<< opalReceiverId<<"].p="<<p<<" from transmitter  with id="<<id<<std::endl;
        this->lastPower=p;
        this->lastTransmitterId=id;
        this->hasReceivedPower=true;
        /* if (this->transmission!=nullptr) {

            std::cout<<"t="<<simTime()<<":Opal::Reception created for  OpalReceiverCallback["<< opalReceiverId<<"], power="<<this->lastPower<<", transmitter="<<this->lastTransmitterId<<",  hasReceivedPower="<<this->hasReceivedPower<<std::endl;
        }
         */
        myMedium->getReception(this->radio,this->transmission);


        // printf("Address of this is %p\n", (void *)this);
    }
    //Emit here the field
    void OpalReceiverCallback::getField(ResultRecord r, int id) {
        if (!r.isField) {
            //optix::float2 E=r.E;

            //FieldComponent* E = new FieldComponent(r.E.x,r.E.y);
            //FieldComponent E(r.E.x,r.E.y);
            std::cout<<"OpalReceiverCallback["<< opalReceiverId<<"].E=["<<r.E.x<<","<<r.E.y<<"] from transmitter  with id="<<id<<std::endl;
            //Cast radio to base receiver and emit field...
            //This will not work because the signal is not declared in the receiver NED, have to use --check-signals=false option in DEBUG
            //With check-signals property it is supposed not to be checked in RELEASE mode
            auto comp=check_and_cast<const cComponent*>(this->radio->getReceiver());
            const_cast<cComponent*> (comp)->emit(OpalRadioMedium::electricFieldRealSignal, r.E.x);
            const_cast<cComponent*> (comp)->emit(OpalRadioMedium::electricFieldImaginarySignal, r.E.y);
            myMedium->updateCachedRecord(this->radio,this->transmission,r);

        }
    }
    void OpalReceiverCallback::saveHits(ResultRecord rr, int id) {
        std::string path=this->hitFilesPath+"/"+std::to_string(this->opalReceiverId)+"-"+std::to_string(id)+"-"+std::to_string(this->transmission->getId())+"-hits.csv";
        std::ofstream myfile;
        myfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            myfile.open(path);
            myfile<<"txId,rxId,E.re,E.im,unfolded_path,doa.x,doa.y,doa.z,dod.x,dod.y,dod.z,diff"<<endl;
            for (auto r: rr.hitRecords) {
                int type=0;
                if (r.diffraction) {
                    type=1;
                }
               // std::cout<<id<<","<<opalReceiverId<<","<<r.E.x<<","<<r.E.y<<","<<r.unfoldedPath<<","<<r.directionOfArrival.x<<","<<r.directionOfArrival.y<<","<<r.directionOfArrival.z<<","<<r.directionOfDeparture.x<<","<<r.directionOfDeparture.y<<","<<r.directionOfDeparture.z<<","<<type<<endl;

                myfile<<id<<","<<opalReceiverId<<","<<r.E.x<<","<<r.E.y<<","<<r.unfoldedPath<<","<<r.directionOfArrival.x<<","<<r.directionOfArrival.y<<","<<r.directionOfArrival.z<<","<<r.directionOfDeparture.x<<","<<r.directionOfDeparture.y<<","<<r.directionOfDeparture.z<<","<<type<<endl;
            }
            myfile.close();

        }   catch (std::ifstream::failure e) {

            throw cRuntimeError("Exception opening/reading/closing hit file (%s) for rx=%d and tx=%d\n",path,opalReceiverId,id);
        }
    }


    void  OpalReceiverCallback::reset() {
        this->lastPower=0.0f;
        this->lastTransmitterId=-1;
        this->hasReceivedPower=false;
    }





    OpalRadioMedium::OpalRadioMedium() : RadioMedium(), OpalSceneManager()
    {
        std::cout<<"OpalRadioMedium() with global called"<<std::endl;
    }

    void OpalRadioMedium::initialize(int stage)
    {
        RadioMedium::initialize(stage);
        if (stage == INITSTAGE_LOCAL) {
            //First, set the environment to read the CUDA program files from our custom directory.
            std::string pf(cudaDir);
            if (!pf.empty()) {
#ifdef _WIN32
                _putenv_s("OPTIX_SAMPLES_SDK_DIR", cudaDir);

#else
                setenv("OPTIX_SAMPLES_SDK_DIR", cudaDir, 1);
#endif // _WIN32
                setBaseDir(cudaDir);
            }


            std::cout<<"baseDir="<<this->baseDir<<std::endl;
            //Initialize opal
            simulationType=par("simulationType").stdstringValue();
            computeMode=par("computeMode").stdstringValue();
            useDiffraction=par("useDiffraction").boolValue();
            carrierFrequency = par("carrierFrequency");
            double r= par("receptionRadius");
            maxNumberOfReflections = par("maxNumberOfReflections");
            double me=par("minEpsilon");
            receptionRadius= (float)r;
            minEpsilon=(float)me;
            setMaxReflections(static_cast<unsigned int>(maxNumberOfReflections));
            useExactSpeedOfLight=par("useExactSpeedOfLight").boolValue();
            generateRaysOnLaunch=par("generateRaysOnLaunch").boolValue();
            enableMultiGPU=par("enableMultiGPU").boolValue();
            enableFastMath=par("enableFastMath").boolValue();
            useAntennaGain=par("useAntennaGain").boolValue();
            logTrace=par("logTrace").boolValue();
            useJson=par("useJson").boolValue();
            switchCoordinates =par("switchCoordinates").boolValue();
            useExtendedCallback=par("recordElectricField").boolValue();
            isStatic = par("isStatic");
            recordHits=par("recordHits").boolValue();
            hitFilesPath = par("hitFilesPath").stdstringValue();
            if (isStatic) {
                //With static we store all the information as ResultRecord in the map, so we have to use extended callback
                useExtendedCallback=true;

                std::cout<<"Assuming static environment"<<std::endl;
                EV<<"Assuming static environment"<<std::endl;
            }


            //Enable multichannel since each transmitter may use different frequencies
            enableMultiChannel();

            //Enable to see detailed info on std::cout per transmission
            //setPrintRecords(true);

            if (!useExactSpeedOfLight) {
                useApproximateSpeedLight();
            }
            if (generateRaysOnLaunch) {
                enableGenerateRaysOnLaunch();
            }
            if (!enableMultiGPU) {
                disableMultiGPU();
            }
            if (!enableFastMath) {
                disableFastMath();
            }

            setUseAntennaGain(useAntennaGain);
            int simType=0;
            if (simulationType.compare("Depolarization")==0) {
                simType=1;
            } else  if (simulationType.compare("RDN")==0) {
                simType=2;
            } else  if (simulationType.compare("Diffraction")==0) {
                simType=4;
            }

            switch (simType) {
            case 0:
                sim= new BasicFlatMeshReflectionSimulation(this);
                break;
            case 1:
                sim= new LPFlatMeshReflectionSimulation(this);
                break;
            case 2:
            {
                sim= new RayDensityNormalizationSimulation(this);
                RDNExecutionMode execMode=RDNExecutionMode::NOMEM;
                int rdnExecutionMode=par("rdnExecutionMode");
                if (rdnExecutionMode==0) {
                    execMode=RDNExecutionMode::HITINFO;
                } else if(rdnExecutionMode==2) {
                    execMode=RDNExecutionMode::NOATOMIC;
                }
                ((RayDensityNormalizationSimulation*)sim)->setExecutionMethod(execMode);
                break;
            }
            case 3:
                sim= new SingleDiffraction(this);
                break;
            }

            ComputeMode cm= ComputeMode::VOLTAGE;
            if (computeMode.compare("Field")==0) {
                std::cout<<computeMode<<std::endl;
                cm= ComputeMode::FIELD;
                //Disable this option at the moment
                throw cRuntimeError("Field mode computes the electric field at the receiver point. It is not intended to be used with INET at the current implementation stage. Voltage, on the contrary, computes the induced power on the receiver antenna");

            }
            setExecuteCallback(true);
            setSimulation(sim);
            sim->setComputeMode(cm);
            sim->setEnableTraceLog(logTrace);
            if (useDiffraction) {
                if (simType != 3) {
                    SingleDiffraction* simd= new SingleDiffraction(this);
                    setSimulation(simd);
                    simd->setComputeMode(cm);
                    simd->setEnableTraceLog(logTrace);
                }
            }
            initContext(carrierFrequency);

            if (useAntennaGain) {
                loadAntennaGainFiles();
            }
            if (recordHits) {
                setRecordHits(recordHits);
            }

            std::cout<<"Opal initContext called"<<endl;


        }
        if (stage==INITSTAGE_PHYSICAL_ENVIRONMENT) {
            //Subscribe here to let nodes subscribe first and update the position with signals prior to manager
            getParentModule()->subscribe(IMobility::mobilityStateChangedSignal, this);
            //Load meshes from server (from Unity), any other framework or load your own files
            useServer=par("useServer").boolValue();
            if (!useServer) {
                //Build static meshes

                if (useJson) {
                    //Much easier and better way to load
                    ScenarioLoader* loader= new ScenarioLoader(this);
                    std::string path=par("jsonFilePath").stdstringValue();
                    if (!path.empty()) {
                        loader->loadJSONScenario(path);
                    }
                } else {
                    loadFromFiles=par("loadMeshesFromFile").boolValue();
                    if (loadFromFiles) {
                        loadMeshesFromFiles();
                        EV_DEBUG<<"Loaded static meshes into scene"<<endl;

                    }
                    if (par("loadEdgesFromFile").boolValue()) {
                        loadEdgesFromFiles();
                    }
                }
            }
            //else static meshes will be loaded by Veneris server or any other framework
        }
        if (stage== INITSTAGE_LAST ) {
            if (!useServer) {

                //if we have read the static meshes from files we can end it now, otherwise, let the server or framework call it when available.
                finishOpalContext();

            }
            //Print configuration

            std::cout<<"RadioMedium configuration:"<<getCompleteStringRepresentation()<<std::endl;
            std::cout<< check_and_cast<inet::IPrintableObject*>(getModuleByPath(".backgroundNoise"))->getCompleteStringRepresentation()<<std::endl;
            std::cout<< check_and_cast<inet::IPrintableObject*>(getModuleByPath(".mediumLimitCache"))->getCompleteStringRepresentation()<<std::endl;
        }
    }

    OpalRadioMedium::~OpalRadioMedium()
    {
        for (auto r : receiversRadios) {
            delete r.second;
        }

    }
    void OpalRadioMedium::loadAntennaGainFiles() {
        std::string gainsFileList = par("antennaGainFilePaths");
        std::vector<std::string> results;//Read meshes names from file with list
        std::ifstream infile(gainsFileList);
        if (!infile.good()){
            throw cRuntimeError("Antenna gain files path not available");
        }
        std::string line;


        while (std::getline(infile, line)) {
            std::cout<<"Reading antenna gains from "<<line<<std::endl;
            //AntennaGain gains=loadGainsFromFileIndBPower(line.c_str());
            //int gainId=registerAntennaGain(gains);
            //registeredGains.insert({line,gainId});
            registerAntenna(line);

        }
        infile.close();
    }
    void OpalRadioMedium::registerAntenna(std::string line) {
        std::cout<<"Reading antenna gains from "<<line<<std::endl;
        AntennaGain gains=loadGainsFromFileIndBPower(line.c_str());
        int gainId=registerAntennaGain(gains);
        registeredGains.insert({line,gainId});
    }
    void OpalRadioMedium::loadMeshesFromFiles() {
        //Our own simple mesh format
        std::string path=par("meshesPath");
        std::string meshesFileList = par("meshesFileList");
        std::string meshesNames;
        std::stringstream iss;
        std::vector<std::string> results;
        if (meshesFileList.empty()) {
            meshesNames = par("meshes").stdstringValue();
            iss.str(meshesNames);
            results.assign(std::istream_iterator<std::string>{iss},
                    std::istream_iterator<std::string>());
            std::cout<<"path="<<path<<"meshesNames="<<meshesNames<<endl;
        } else {
            //Read meshes names from file with list
            std::ostringstream pl;
            pl<<path<<"/"<<meshesFileList;
            std::cout<<"Reading meshes from path="<<pl.str()<<endl;
            std::ifstream infile(pl.str());

            std::string line;


            while (std::getline(infile, line)) {
                //std::cout<<line<<std::endl;
                results.push_back(line);
            }
            infile.close();
        }
        //std::string meshesNames = par("meshes");

        //std::istringstream iss(meshesNames);
        //std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

        for (auto n : results) {
            std::ostringstream vf;
            std::ostringstream inf;
            std::ostringstream tf;
            std::ostringstream emf;
            std::ostringstream fi;

            std::cout<<"Loading mesh from "<<n<<endl;
            //Assume all files use the same suffixes
            vf<<path<<"/"<<n<<"-v.txt";
            inf<<path<<"/"<<n<<"-i.txt";
            tf<<path<<"/"<<n<<"-t.txt";
            emf<<path<<"/"<<n<<"-em.txt";
            fi<<path<<"/"<<n<<"-fi.txt";
            std::vector<optix::float3> v=loadVerticesFromFile(vf.str().c_str());
            std::vector<int> ind=loadTrianglesFromFile(inf.str().c_str());
            optix::Matrix4x4 tm=loadTransformFromFile(tf.str().c_str());
            //emProp1.dielectricConstant = optix::make_float2(3.75f, -60.0f*defaultChannel.waveLength*0.038f);
            MaterialEMProperties emProp1 =loadEMFromFile(emf.str().c_str());

            //Check for faces...
            std::ifstream fid(fi.str().c_str());
            if(fid.good()) {
                std::vector<std::pair<optix::int3,uint> > faces=loadFaceIdsFromFile(fid);
                addStaticMeshWithFaces(v,faces,tm,emProp1);
                fid.close();
            } else {
                addStaticMesh(static_cast<int>(v.size()), v.data(), static_cast<int>(ind.size()), ind.data(), tm, emProp1);
            }
            //add faces here...

        }

    }
    std::vector<std::pair<optix::int3,unsigned int> > OpalRadioMedium::loadFaceIdsFromFile(std::ifstream& infile) {
        std::vector<std::pair<optix::int3,unsigned int> > faces;
        std::string line;
        while (std::getline(infile, line) ){
            optix::int4 v=readInt4(line);
            faces.push_back(std::make_pair<optix::int3,unsigned int>(make_int3(v.x,v.y,v.z),v.w));
        }
        return faces;
    }
    void OpalRadioMedium::loadEdgesFromFiles() {
        //Our own simple edge format
        std::string path=par("edgesPath").stdstringValue();
        std::string edgesFileList = par("edgesFileList").stdstringValue();
        std::ostringstream pl;
        pl<<path<<"/"<<edgesFileList;
        std::cout<<"Reading edges from path="<<pl.str()<<endl;

        std::stringstream iss;
        std::vector<std::string> results;

        //Read meshes names from file with list
        std::ifstream infile(pl.str());

        std::string line;


        while (std::getline(infile, line)) {

            results.push_back(line);
        }
        infile.close();



        for (auto n : results) {
            std::ostringstream vf;
            std::cout<<"Loading edge  "<<n<<endl;
            //Assume all files use the same suffixes
            vf<<path<<"/"<<n<<"-ed.txt";
            loadEdgeFromFile(vf.str().c_str());

        }

    }
    void OpalRadioMedium::loadEdgeFromFile(const char* file) {
        std::ifstream infile(file);
        std::string line;
        //In this order
        std::getline(infile, line);
        float3 v=readFloat3(line);
        std::getline(infile, line);
        float3 a=readFloat3(line);
        std::getline(infile, line);
        float3 b=readFloat3(line);
        std::getline(infile, line);
        float3 o=readFloat3(line);
        std::getline(infile, line);
        float3 n_a=readFloat3(line);
        std::getline(infile, line);
        float3 n_b=readFloat3(line);

        std::string delimiters("\t");
        std::istringstream iline;
        std::string val;
        std::getline(infile, line);
        iline.str(line);
        getline(iline,val,'\t');
        uint face_a=std::stoul(val);
        getline(iline,val,'\t');
        uint face_b=std::stoul(val);
        getline(iline,val,'\t');
        uint id=std::stoul(val);
        std::getline(infile, line);
        iline.str(line);
        getline(iline,val,'\t');
        float n=std::stof(val);

        std::getline(infile, line);
        float4 em=readFloat4(line);
        MaterialEMProperties prop=ITUparametersToMaterial(em.x,em.y,em.z,em.w);

        addEdge(o,v,make_uint2(face_a,face_b),a,b,n_a,n_b,prop,id);
        infile.close();

    }
    optix::int4 OpalRadioMedium::readInt4(std::string line) {

        std::string delimiters("\t");
        std::istringstream iline;
        std::string val;

        iline.str(line);
        optix::int4 v;
        getline(iline,val,'\t');
        v.x=std::stoul(val);
        getline(iline,val,'\t');
        v.y=std::stoul(val);
        getline(iline,val,'\t');
        v.z=std::stoul(val);
        getline(iline,val,'\t');
        v.w=std::stoul(val);
        return v;

    }
    optix::float3 OpalRadioMedium::readFloat3(std::string line) {

        std::string delimiters("\t");
        std::istringstream iline;
        std::string val;

        iline.str(line);
        optix::float3 v;
        getline(iline,val,'\t');
        v.x=std::stof(val);
        getline(iline,val,'\t');
        v.y=std::stof(val);
        getline(iline,val,'\t');
        v.z =std::stof(val);
        return v;
    }
    optix::float4 OpalRadioMedium::readFloat4(std::string line) {

        std::string delimiters("\t");
        std::istringstream iline;
        std::string val;

        iline.str(line);
        optix::float4 v;
        getline(iline,val,'\t');
        v.x=std::stof(val);
        getline(iline,val,'\t');
        v.y=std::stof(val);
        getline(iline,val,'\t');
        v.z =std::stof(val);
        getline(iline,val,'\t');
        v.w =std::stof(val);
        return v;
    }
    MaterialEMProperties OpalRadioMedium::loadEMFromFile(const char* file) {
        std::ifstream infile(file);

        float a,b,c,d=0;
        //cha
        infile>>a;
        infile>>b;
        infile>>c;
        infile>>d;
        return ITUparametersToMaterial(a,b,c,d);



    }
    optix::Matrix4x4  OpalRadioMedium::loadTransformFromFile(const char* file) {
        std::ifstream infile(file);
        float x, y, z, w=0;
        //char c;
        optix::Matrix4x4 tm;
        std::string line;
        int row=0;

        while (std::getline(infile, line)) {
            if (row==4) {
                break;
            }
            //std::cout << line << std::endl;
            std::string delimiters = "\t";
            size_t current;
            size_t next = -1;
            int p = 0;
            do
            {
                current = next + 1;
                next = line.find_first_of(delimiters, current);
                if (p == 0) {
                    x = std::stof(line.substr(current, next - current));
                }
                if (p == 1) {
                    y = std::stof(line.substr(current, next - current));
                }
                if (p == 2) {
                    z = std::stof(line.substr(current, next - current));
                }
                if (p == 3) {
                    w = std::stof(line.substr(current, next - current));
                }

                //std::cout << line.substr(current, next - current) <<"\t"<< std::endl;
                p++;
            } while (next != std::string::npos);

            tm.setRow(row, optix::make_float4(x, y, z,w));
            row++;
        }
        std::cout << "Loaded matrix" << tm << "  from " << file << std::endl;
        infile.close();
        return tm;

    }
    /* std::vector<optix::float3>  OpalRadioMedium::loadVerticesFromFile(const char* file) {
        std::ifstream infile(file);
        float x, y, z;
        //char c;
        std::vector<optix::float3> vertices;
        std::string line;


        while (std::getline(infile, line)) {

            //std::cout << line << std::endl;
            std::string delimiters = "\t";
            size_t current;
            size_t next = -1;
            int p = 0;
            do
            {
                current = next + 1;
                next = line.find_first_of(delimiters, current);
                if (p == 0) {
                    x = std::stof(line.substr(current, next - current));
                }
                if (p == 1) {
                    y = std::stof(line.substr(current, next - current));
                }
                if (p == 2) {
                    z = std::stof(line.substr(current, next - current));
                }

                //std::cout << line.substr(current, next - current) <<"\t"<< std::endl;
                p++;
            } while (next != std::string::npos);

            vertices.push_back(optix::make_float3(x, y, z));
        }
        std::cout << "Loaded " << vertices.size() << " vertices from " << file << std::endl;
        infile.close();

        return vertices;
    }




    std::vector<int>  OpalRadioMedium::loadTrianglesFromFile(const char* file) {
        std::ifstream infile(file);
        int i;
        std::vector<int> triangles;

        while (infile>>i) {
            //std::cout << i << std::endl;
            triangles.push_back(i);
        }
        std::cout << "Loaded " << triangles.size() << "indices from " << file << std::endl;
        infile.close();
        return triangles;
    }
     */

    optix::float3  OpalRadioMedium::getOpalCoordinates(Coord c) const {
        if (switchCoordinates) {
            //WARNING:Unity uses a left-handed coordinate system with Y axis as up, whereas INET uses Z axis as up
            //if meshes have been exported from Unity, or coordinates are provided by Unity, we have to interchange axis, to keep everything consistent
            //Transformation matrices coming from Unity also have to be kept consistent
            //Otherwise, we can just keep the INET coordinates


            return optix::make_float3((float) c.x,(float) c.z, (float) c.y);
        } else {
            return optix::make_float3((float) c.x,(float) c.y, (float) c.z);
        }
    }

    void OpalRadioMedium::addRadio(const IRadio *radio)
    {

        RadioMedium::addRadio(radio);
        IMobility* mob= radio->getAntenna()->getMobility();
        if (mob) {
            Coord c=mob->getCurrentPosition();
            cModule *radioModule = const_cast<cModule *>(check_and_cast<const cModule *>(radio));
            int id =getContainingNode(radioModule)->par("id");
            double  rxRadius =getContainingNode(radioModule)->par("receptionRadius");
            OpalReceiverCallback* rc = new OpalReceiverCallback(this,id,radio);
            rc->rxRadius=rxRadius;
            std::cout<<"Adding receiver "<<id<<" with Coord="<<c<<endl;
            std::cout<<"Receiver["<<id<<"]->radioId= "<<radio->getId()<<endl;
            receiversRadios.insert(std::pair<const IRadio*,OpalReceiverCallback*>(radio,rc));

            //Radios are both transmitter and receivers

            optix::float3 posrx=getOpalCoordinates(c);



            if (useAntennaGain) {
                const OpalLinearPolarizationAntenna* antenna= check_and_cast<const OpalLinearPolarizationAntenna*>(radio->getAntenna());
                addReceiver(id,posrx,getOpalCoordinates(antenna->getPolarization()),rxRadius,(rc->myCallback));
                if (antenna->useGain()) {
                    int gainId=getAntennaGainId(antenna->getGainFilePath());
                    registerReceiverGain(id,gainId);
                    //Assuming the transmitter is going to use the same gain
                    registerTransmitterGain(id,gainId);
                }
            } else {
                //Use a default vertical polarization
                addReceiver(id,posrx,optix::make_float3(0.0f,1.0f,0.0f),rxRadius,(rc->myCallback));
            }
            if (useExtendedCallback) {
                setReceiverExtendedCallback(id,(rc->extendedCallback));
                //Create the corresponding statistic
                cProperty *statisticTemplate =
                        getProperties()->get("statisticTemplate", "electricFieldReal");
                getEnvir()->addResultRecorders(radioModule, electricFieldRealSignal, "electricFieldReal", statisticTemplate);
                cProperty *statisticTemplateIm =
                        getProperties()->get("statisticTemplate", "electricFieldImaginary");
                getEnvir()->addResultRecorders(radioModule, electricFieldImaginarySignal, "electricFieldImaginary", statisticTemplateIm);


            }
            if (recordHits) {
                rc->hitFilesPath=this->hitFilesPath;
                setReceiverExtendedCallback(id,std::bind(&inet::physicallayer::OpalReceiverCallback::saveHits, rc, std::placeholders::_1,std::placeholders::_2));
            }


        } else {
            throw cRuntimeError("Radio does not have mobility coordinates");
        }

    }



    void OpalRadioMedium::removeRadio(const IRadio *radio) {



        RadioMedium::removeRadio(radio);
        OpalReceiverCallback* rc;
        try {
            rc=receiversRadios.at(radio);
            //Check if there is an ongoing transmission for this radio
            //std::cout<<simTime()<<":OpalRadioMedium::removeRadio. Removing "<<rc->opalReceiverId<<"(radioId="<<radio->getId()<<"). transmissions.size="<<transmissions.size()<<endl;
            std::cout<<simTime()<<":OpalRadioMedium::removeRadio. Removing "<<rc->opalReceiverId<<"(radioId="<<radio->getId()<<"). transmissions.size="<<communicationCache->getNumTransmissions()<<endl;
            int i=0;
            communicationCache->mapTransmissions([&] (const ITransmission *transmission) {
                //for (auto t : transmissions){
                // std::cout<<i<<":. Transmission stored for "<<t->getTransmitterId()<<" with id="<<t->getId()<<endl;

                if (transmission->getTransmitterId()==radio->getId()){
                    //store a pending transmission
                    std::cout<<"Radio "<<rc->opalReceiverId<<"has ongoing transmissions."<<transmission->getId()<<endl;
                    pendingTransmissions.insert(std::pair<int,int>(transmission->getId(), rc->opalReceiverId));
                    return;
                }
                ++i;
                //}
            });
        } catch (std::out_of_range e) {
            throw cRuntimeError("Radio is not registered with opal");
            return;
        }

        removeReceiver(rc->opalReceiverId);
        receiversRadios.erase(radio);
        //Delete the callback
        delete rc;

    }


    IWirelessSignal *OpalRadioMedium::transmitPacket(const IRadio *radio, Packet *packet)
    {
        Enter_Method("transmitPacket");
        auto signal = createTransmitterSignal(radio, packet);
        auto transmission = signal->getTransmission();
        addTransmission(radio, transmission);
        if (recordTransmissionLog)
            communicationLog.writeTransmission(radio, signal);




        //We can change order, first transmit(), only receivers that actually receive something then are sendToRadio in their callback
        //Or just we leave as it is and receivers will get 0 power which is below energyDetection... less performance. Keep it this way at the moment

        //std::cout<<"OpalRadioMedium::transmitPacket(): transmission="<<transmission<<endl;
        sendToAffectedRadios(const_cast<IRadio *>(radio), signal);
        communicationCache->setCachedSignal(transmission, signal);

        //Optimization for static enviroments

        if(isStatic){
            transmitStatic(radio,transmission);
        }  else {


            //Execute transmit launch with Opal
            transmitInOpal(radio,transmission);
        }



        return signal;
    }
    void OpalRadioMedium::transmitStatic(const IRadio *radio, const ITransmission *transmission ) {
        auto tx = mapReceptions.find(transmission->getTransmitter());
        if (tx!=mapReceptions.end()) {
            //std::cout << "transmitPacket() -> Transmitter " << receiversRadios.at(tx->first)->opalReceiverId << " already exist on the map. Searching CPE"<<endl;
            CachedPowerEntry* CPE = tx->second;
            int txOpalid = receiversRadios.at(tx->first)->opalReceiverId;
            for (auto rx = CPE->begin(); rx != CPE->end(); ++rx){
                if(rx->second.power != 0){
                    OpalReceiverCallback* callback;
                    try  {
                        callback=receiversRadios.at(rx->first);
                        callback->createReception(rx->second.power, txOpalid);
                        callback->getField(rx->second.rr, txOpalid);
                        if (recordHits) {
                            callback->saveHits(rx->second.rr, txOpalid);
                        }
                        //std::cout<<"transmitPacket() -> Reception created between "<< txOpalid << " and " << receiversRadios.at(rx->first)->opalReceiverId << " . Power: "<< rx->second <<endl;

                    } catch (std::out_of_range &e) {
                        std::stringstream s;
                        s<<"sendToRadio():: radio "<<radio<<" is not registered with opal";
                        throw cRuntimeError(s.str().c_str());
                    }
                }
            }
        }
        else {
            //std::cout<<"transmitPacket() -> Transmitter " << transmission->getTransmitter()->getId() << " doesnt exist on CachedPowerMap "<< " . Executing transmitInOpal"<<endl;;
            CachedPowerEntry* CPE = new CachedPowerEntry();
            mapReceptions.insert(std::pair<const IRadio*, CachedPowerEntry*>(transmission->getTransmitter(), CPE));
            transmitInOpal(radio,transmission);
        }

    }
    void OpalRadioMedium::sendToAffectedRadios(IRadio *radio, const IWirelessSignal *transmittedSignal)
    {
        //const Signal *signal = check_and_cast<const Signal *>(transmittedSignal);
        //std::cout << " OpalRadioMedium::sendToAffectedRadios(): Sending " << transmittedSignal << " with " << signal->getBitLength() << " bits in " << signal->getDuration() * 1E+6 << " us transmission duration"
        //<< " from " << radio << " on " << (IRadioMedium *)this << ". receivers.size=" <<receiversRadios.size()<< endl;
        const WirelessSignal *signal = check_and_cast<const WirelessSignal *>(transmittedSignal);
        EV_DEBUG << "Sending " << transmittedSignal << " with " << signal->getBitLength() << " bits in " << signal->getDuration() * 1E+6 << " us transmission duration"
                << " from " << radio << " on " << (IRadioMedium *)this << "." << endl;
        //Send to all radios: opal will callback the ones receiving power
        for (auto r : receiversRadios) {

            r.second->reset();
            sendToRadio(radio,r.first,signal);

        }

    }


    void OpalRadioMedium::transmitInOpal(const IRadio *radio, const ITransmission *transmission) {



        int id;
        try  {
            id=receiversRadios.at(radio)->opalReceiverId;
        } catch (std::out_of_range e) {
            std::stringstream s;
            s<<"transmitInOpal():: radio "<<radio<<" is not registered with opal";
            throw cRuntimeError(s.str().c_str());
            return;
        }
        //Transmitter position
        Coord txpos=transmission->getStartPosition();
        //Transmitter power
        const IScalarSignal *scalarSignalAnalogModel = check_and_cast<const IScalarSignal *>(transmission->getAnalogModel());
        W transmissionPower = scalarSignalAnalogModel->getPower();
        optix::float3 postx=getOpalCoordinates(txpos);

        //TODO: set polarization according to antenna orientation from antenna mobility instead of module mobility
        //Let us keep this simple here : The OpalAntenna module has to handle change of orientations and everything else
        const IAntenna* antenna_mob=radio->getAntenna();
        Coord pol= check_and_cast<const OpalLinearPolarizationAntenna*>(antenna_mob)->getPolarization();
        //Perpendicular to the floor (Y axis up)
        //optix::float3 polarization=optix::make_float3(0.0f,1.0f,0.0f);
        //Have to be changed to a unit vector indicating the antenna orientation

        optix::float3 polarization=getOpalCoordinates(pol);
        //std::cout<<simTime()<<":Opal radio id="<<id<<" transmitting. txid="<<transmission->getTransmitterId()<<"txPower="<<transmissionPower.get()<<endl;
        //std::cout<<simTime()<<":"<<transmission <<endl;


        const NarrowbandTransmissionBase *narrowbandTransmission = check_and_cast<const NarrowbandTransmissionBase *>(transmission);
        auto centerFrequency = narrowbandTransmission->getCenterFrequency();

        transmit(id, (float) transmissionPower.get(),postx,polarization, centerFrequency.get(),false,false);


    }

    void OpalRadioMedium::sendToRadio(IRadio *transmitter, const IRadio *receiver, const IWirelessSignal *transmittedSignal)
    {
        const Radio *transmitterRadio = check_and_cast<const Radio *>(transmitter);
        const Radio *receiverRadio = check_and_cast<const Radio *>(receiver);
        const ITransmission *transmission = transmittedSignal->getTransmission();
        if (receiver != transmitter && receiver->getReceiver() != nullptr && isPotentialReceiver(receiver, transmission)) {
            // if (receiverRadio != transmitterRadio && isPotentialReceiver(receiverRadio, transmission)) {
            auto transmitterRadio = const_cast<cSimpleModule *>(check_and_cast<const cSimpleModule *>(transmitter));
            cMethodCallContextSwitcher contextSwitcher(transmitterRadio);
            contextSwitcher.methodCall("sendToRadio");
            const IArrival *arrival = getArrival(receiver, transmission);
            simtime_t propagationTime = arrival->getStartPropagationTime();

            EV_DEBUG << " OpalRadioMedium::sendToRadio(): Sending " << transmittedSignal
                    << " from " << transmitter << " at " << transmission->getStartPosition()
                    << " to " << receiver << " at " << arrival->getStartPosition()
                    << " in " << propagationTime * 1E+6 << " us propagation time." << endl;
            auto receivedSignal = static_cast<WirelessSignal *>(createReceiverSignal(transmission));


            //Set this transmission in callback
            std::cout<<"OpalRadioMedium::sendToRadio(): transmission"<<transmission<<endl;
            OpalReceiverCallback* callback;
            try  {
                callback=receiversRadios.at(receiver);

            } catch (std::out_of_range e) {
                std::stringstream s;
                s<<"sendToRadio():: radio "<<receiver<<" is not registered with opal";
                throw cRuntimeError(s.str().c_str());
                return;
            }


            callback->transmission=transmission;



            cGate *gate = receiver->getRadioGate()->getPathStartGate();
            transmitterRadio->sendDirect(receivedSignal, propagationTime, transmission->getDuration(), gate);
            communicationCache->setCachedSignal(receiverRadio, transmission, receivedSignal);
            signalSendCount++;

            /////



        }

    }

    //Executed in the callbacks when power is received

    const IReception *OpalRadioMedium::computeReception(const IRadio *receiver, const ITransmission *transmission) const {
        receptionComputationCount++;
        //Create a RadioScalar directly, no need for ScalarAnalogModel at the moment
        const IArrival* arrival= getArrival(receiver, transmission);
        const INarrowbandSignal *narrowbandSignalAnalogModel = check_and_cast<const INarrowbandSignal *>(transmission->getAnalogModel());
        const simtime_t receptionStartTime = arrival->getStartTime();
        const simtime_t receptionEndTime = arrival->getEndTime();
        const Quaternion receptionStartOrientation = arrival->getStartOrientation();
        const Quaternion receptionEndOrientation = arrival->getEndOrientation();
        const Coord receptionStartPosition = arrival->getStartPosition();
        const Coord receptionEndPosition = arrival->getEndPosition();


        //Get power from callback
        OpalReceiverCallback* ocb=nullptr;
        int txId;
        try  {
            ocb=receiversRadios.at(receiver);

        } catch (std::out_of_range e) {
            std::stringstream s;
            s<<"computeReception():: radio "<<receiver<<" is not registered with opal";
            throw cRuntimeError(s.str().c_str());
            //return nullptr;
        }

        if (transmission->getTransmitter()==nullptr) {
            //Transmitter may have been removed
            std::stringstream s;
            ocb=receiversRadios.at(receiver);
            std::cout<<"computeReception():: transmitter is  null transmitterId="<<transmission->getTransmitterId()<<"transmissionId"<<transmission->getId()<<endl;
            s<<"computeReception():: transmitter is  null. Receiver="<<ocb->opalReceiverId;
            try{
                txId=pendingTransmissions.at(transmission->getId());
            } catch (std::out_of_range e) {
                std::stringstream s;
                s<<"computeReception():: pending transmission "<<transmission->getId()<<" not found";
                throw cRuntimeError(s.str().c_str());
            }

            //return nullptr;
        } else{

            try  {
                txId=receiversRadios.at(transmission->getTransmitter())->opalReceiverId;

            } catch (std::out_of_range e) {
                std::stringstream s;
                if (transmission->getTransmitter()==nullptr) {
                    std::cout<<"computeReception():: out of range transmitter is  null";
                    s<<"computeReception():: receiver "<<ocb->opalReceiverId<<". transmitter is not registered with opal";
                } else {
                    s<<"computeReception():: receiver "<<ocb->opalReceiverId<<". transmitter "<<transmission->getTransmitter()<<" is not registered with opal";
                }
                throw cRuntimeError(s.str().c_str());
                // return nullptr;
            }
        }

        double p=0.0;
        if (ocb->hasReceivedPower) {
            if (ocb->lastTransmitterId==txId) {
                p=(double)ocb->lastPower;
                //std::cout<<"OpalRadioMedium::computeReception(): Power received="<< p << endl;
                ocb->reset();
            }else {
                throw cRuntimeError("%f: R[%d]: Received power from unknown transmitter %d, expected transmitter %d",simTime().dbl(),ocb->opalReceiverId, ocb->lastTransmitterId,txId);
            }
            if (ocb->opalReceiverId==txId) {
                throw cRuntimeError("%f: R[%d]: Received power from my own transmitter %d",simTime().dbl(),ocb->opalReceiverId,txId);

            }
        }
        //Update cache
        if (isStatic) {

            auto tx = mapReceptions.find(transmission->getTransmitter());
            if (tx != mapReceptions.end()) {
                // Transmitter exists inside map
                OpalReceiverCallback* ocb=receiversRadios.at(transmission->getTransmitter());
                int idtx = ocb->opalReceiverId;
                //std::cout<<"opalComputeReception() -> Transmitter " << idtx << " already exist on the map. Searching CPE"<<endl;
                CachedPowerEntry* CPE = tx->second;
                auto rx = CPE->find(receiver);
                if (rx == CPE->end()) {
                    ocb=receiversRadios.at(receiver);
                    int idrx = ocb->opalReceiverId;
                    //std::cout<<"opalComputeReception() -> Power between "<< idrx << " and " << idtx << " doesnt exist. Inserting power: "<< (float)receptionPower.get() <<endl;
                    CachedPowerData cpd;
                    cpd.power=p;

                    CPE->insert(std::pair<const IRadio*,CachedPowerData>(receiver, cpd ));
                }
                else {
                    //ocb=receiversRadios.at(receiver);
                    //int idrx = ocb->opalReceiverId;
                    //std::cout<<"opalComputeReception() -> Power between "<< idrx << " and " << idtx << " exists. Power: "<< (float)rx->second <<endl;
                }
            }
        }
        W receptionPower(p);
        return new ScalarReception(receiver, transmission, receptionStartTime, receptionEndTime, receptionStartPosition, receptionEndPosition, receptionStartOrientation, receptionEndOrientation, narrowbandSignalAnalogModel->getCenterFrequency(), narrowbandSignalAnalogModel->getBandwidth(), receptionPower);

    }
    void OpalRadioMedium::updateCachedRecord(const IRadio *receiver, const ITransmission *transmission, ResultRecord record) {
        if (isStatic) {

            auto tx = mapReceptions.find(transmission->getTransmitter());
            if (tx != mapReceptions.end()) {
                // Transmitter exists inside map
                OpalReceiverCallback* ocb=receiversRadios.at(transmission->getTransmitter());
                int idtx = ocb->opalReceiverId;
                //std::cout<<"opalComputeReception() -> Transmitter " << idtx << " already exist on the map. Searching CPE"<<endl;
                CachedPowerEntry* CPE = tx->second;
                auto rx = CPE->find(receiver);
                if (rx == CPE->end()) {
                    //ocb=receiversRadios.at(receiver);
                    //int idrx = ocb->opalReceiverId;
                    //std::cout<<"opalComputeReception() -> Power between "<< idrx << " and " << idtx << " doesnt exist. Inserting power: "<< (float)receptionPower.get() <<endl;
                    // CachedPowerData cpd;
                    // cpd.power=p;

                    //CPE->insert(std::pair<const IRadio*,CachedPowerData>(receiver, cpd ));
                }
                else {
                    rx->second.rr=record;
                    //ocb=receiversRadios.at(receiver);
                    //int idrx = ocb->opalReceiverId;
                    //std::cout<<"opalComputeReception() -> Power between "<< idrx << " and " << idtx << " exists. Power: "<< (float)rx->second <<endl;
                }
            }
        }
    }
    void OpalRadioMedium::finishOpalContext()
    {

        //First finish the context, then create rays
        finishSceneContext();

        initAzimuth = par("initAzimuth").doubleValue();
        endAzimuth = par("endAzimuth").doubleValue();
        initElevation = par("initElevation").doubleValue();
        endElevation = par("endElevation").doubleValue();
        elevationDelta=par("elevationDelta").doubleValue();
        azimuthDelta=par("azimuthDelta").doubleValue();

        bool useDecimalDegreeDelta=par("useDecimalDegreeDelta").boolValue();
        if (useDecimalDegreeDelta) {

            if (elevationDelta<1 || azimuthDelta<1) {
                elevationDelta=1;
                azimuthDelta=1;
            }
            createRaySphere2DSubstep(elevationDelta, azimuthDelta);

        } else {
            if (simulationType.compare("RDN")==0) {

                rdnRays=par("rdnRays");
                setRayRange(initElevation,endElevation,initAzimuth,endAzimuth,rdnRays,rdnRays);
                ((RayDensityNormalizationSimulation*)sim)->setInitialDensity(getRaySphere().rayCount,initAzimuth,endAzimuth,initElevation,endElevation);
                ((RayDensityNormalizationSimulation*)sim)->setFiltering(par("rndFiltering"));
            } else {

                createRaySphere2D(initElevation,elevationDelta, endElevation,initAzimuth, azimuthDelta,endAzimuth);

            }
        }


        //setPrintEnabled(1024*1024*1024);



        WATCH_MAP(receiversRadios);
        EV_INFO << "Initialized " << printSceneReport() << endl;
        std::cout<<"Opal Initialized"<<endl;
    }

    void OpalRadioMedium::receiveSignal(cComponent* source, simsignal_t signal,
            cObject* value, cObject* details) {
        Enter_Method("%s", cComponent::getSignalName(signal));
        if (signal==IMobility::mobilityStateChangedSignal) {

            MobilityBase* mob=check_and_cast<MobilityBase*>(value);
            int id=mob->getParentModule()->par("id").intValue();
            for (std::map<const IRadio*, OpalReceiverCallback*>::iterator it=receiversRadios.begin(); it!=receiversRadios.end(); ++it) {
                if (it->second->opalReceiverId==id) {
                    Coord p=mob->getCurrentPosition();
                    optix::float3 pos=getOpalCoordinates(p);

                    //If mobility has changed, polarization may have changed
                    const IAntenna* antenna_mob=it->first->getAntenna();
                    Coord pol= check_and_cast<const OpalLinearPolarizationAntenna*>(antenna_mob)->getPolarization();
                    optix::float3 polarization=getOpalCoordinates(pol);
                    //If used with GUI, every time the refreshDisplay is called, a getCoordinate is called which emits a mobilityStateChanged for the node
                    //This function is going to be called many times
                    //std::cout<<simTime()<<":OpalRadioMedium::receiveSignal() Updating position of "<<id<<" to "<<p<<" and polarization="<<pol<<endl;
                    updateReceiver(id,pos,polarization,it->second->rxRadius);
                    //Clear cache. Directly clearing all cache, instead for looking for specific changes
                    if (isStatic) {
                        clearPowerCache();
                    }


                    break;
                }
            }

            //Get the id


        } else {
            RadioMedium::receiveSignal(source,signal,value,details);
        }

    }
    void  OpalRadioMedium::clearPowerCache() {
        auto it = mapReceptions.begin();
        while (it!=mapReceptions.end()) {
            it->second->clear();
            delete it->second;
            it=mapReceptions.erase(it);
        }
    }

    int OpalRadioMedium::getAntennaGainId(std::string path)
    {
        return registeredGains.at(path);
    }

}
//namespace

