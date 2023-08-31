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

#ifndef __INET4_EXECUTIONSERVER_H_
#define __INET4_EXECUTIONSERVER_H_

#include <omnetpp.h>
#include "inet/common/INETDefs.h"
#include <vector>
#include <boost/asio.hpp>
#include "messages/flatbuffers/flatbuffers.h"
#include "ExternalClockScheduler.h"
#include "messages/BaseTypes_generated.h"

#include <fstream>



using namespace omnetpp;

namespace inet {
//This size needs to be updated if the flatbuffer messages changes
#define SIMULATOR_HEADER_SIZE 32

/**
 * The execution server receives messages from a external entity and advances simulation time. Other types of messages are handled by derived classes.
 * Messages can be read from a file or from a socket.
 * Assumes the ExternalClockScheduler is being used
 */
class ExecutionServer : public cSimpleModule
{
protected:
    void _ExternalTime();

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket tcp_socket{io_service};

    virtual void initializeServer();
    virtual void launchServer();

    virtual int numInitStages() const override {return NUM_INIT_STAGES;}
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg);


    uint32_t msg_size;
    Veneris::Communications::VenerisMessageTypes msg_type;
    bool runServer;
    int port;

    bool useFile;
    std::string filePath;
    std::fstream fs;

    cMessage* selfMsg;
    ExternalClockScheduler *sch;
    std::vector<uint8_t>* message;
    void endServer();

    //Template to handle the messages
    template<class T> const T *readMsg(uint32_t size)
    {

        //Clear previous buffer. We should do this in other way ...
        if (message!=nullptr) {
            delete message;
        }
        message = new std::vector<uint8_t>(size);

        //Read message from file
        if (useFile) {
            fs.read(reinterpret_cast<char* >(message->data()),size);
            if (fs.eof()) {
                runServer=false; //Break loop and finish
            }
        } else {

            boost::system::error_code error;
            auto r=tcp_socket.read_some(boost::asio::buffer(*message),error);
            if (r==0) {
                std::cout<<"Error reading. "<<error.value()<<std::endl;
            }
        }




        return flatbuffers::GetRoot<T>(message->data());

    };

public:
    virtual ~ExecutionServer();
    virtual void processMessage( Veneris::Communications::VenerisMessageTypes type, uint32_t size);

};

} //namespace

#endif
