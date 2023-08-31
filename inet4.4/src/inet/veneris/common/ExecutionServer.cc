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



#include "ExecutionServer.h"
#include "messages/BaseTypes_generated.h"
#include "messages/Header_generated.h"
#include "messages/ExternalTime_generated.h"

using namespace Veneris::Communications;

namespace inet {

Define_Module(ExecutionServer);

void ExecutionServer::initialize(int stage) {

    if (stage == INITSTAGE_LOCAL) {

        port = par("port");
        useFile=par("useFile").boolValue();
        if (useFile) {

            filePath=par("filePath").stdstringValue();
            std::cout<<"ExecutionServer::initialize() using file: "<<filePath<<endl;
            fs.open(filePath,std::fstream::in| std::fstream::binary);
            if (!fs.is_open()) {
                throw cRuntimeError("Error opening file: '%s' ; file cannot be found or cannot be opened, check filePath ",filePath.c_str());
            }
        }
        msg_type = Veneris::Communications::VenerisMessageTypes_Reserved;
        msg_size = 0;
        selfMsg = new cMessage("selfMsg");
        scheduleAt(simTime(), selfMsg);
        sch = check_and_cast<ExternalClockScheduler*>(getSimulation()->getScheduler());
        message=nullptr;

        EV_INFO << "Initializing stage 0 of  ExecutionServer."<<std::endl;
    }

}

void ExecutionServer::_ExternalTime() {
    auto msg = readMsg<ExternalTime>(msg_size);
    sch->setExternalTime(msg->time());
    //std::cout<<"time="<<msg->time()<<endl;

}

void ExecutionServer::initializeServer() {
    try {
        boost::asio::ip::tcp::acceptor acceptor(io_service,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port));
        EV_INFO << " Listening on port " << port << endl;
        EV_INFO << " Server will block until a connection is accepted. GUI is blocked until then. "<< endl;
        acceptor.accept(tcp_socket);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

}
void ExecutionServer::launchServer() {

    while (runServer) {


        auto headerMsg = readMsg<Header>(SIMULATOR_HEADER_SIZE);

        // Update global variables
        msg_type = headerMsg->type();
        msg_size = headerMsg->size();
        float msg_time=headerMsg->time();
        //Update external current time
        sch->setExternalTime(msg_time);

        //std::cout << "Header: type=" << msg_type << ", message size="<<msg_size<< endl;



        // Process all messages in FES. Our custom scheduler will stop it by returning null when event time is later than external time

        while (true) {
            cEvent *event = getSimulation()->takeNextEvent();

            if (event!=nullptr) {
                //std::cout<<simTime()<<":Executing next event: "<<event <<". eventTime="<<event->getArrivalTime()<<"ext_time="<<msg_time <<std::endl;
                getSimulation()->executeEvent(event);

            } else {
                break;
            }
        }

        processMessage(msg_type, msg_size);
        //Now simtime should be less or equal than external message time
        // std::cout << "Header: type=" << msg_type << ", message size="<<msg_size<<"ext_time="<<msg_time<<"simTime="<<simTime() <<endl;
        // Refresh GUI (if exist)
        if (getEnvir()->isGUI() && !getEnvir()->isExpressMode()) {
            try {
                getSimulation()->getSystemModule()->callRefreshDisplay();
                if (getEnvir()->idle()) {
                    endServer();
                }

            } catch (std::exception& e) {
                cException *ex = dynamic_cast<cException *>(&e);

                std::cout << "<!> " << ex->getFormattedMessage().c_str()<< endl;
                endServer();

            }
        }




    }
    //If we break out of the loop then end
    endServer();

}

void ExecutionServer::handleMessage(cMessage *msg) {
    if (msg == selfMsg) {
        if (!useFile) {
            initializeServer();
            EV_INFO << "Connection accepted " << endl;
        }

        runServer = true;
        launchServer();
    }

}

void ExecutionServer::endServer() {
    if (useFile) {
        fs.close();
    } else {
        tcp_socket.close();
    }
    EV_INFO<<"Closing Server"<<endl;
    runServer = false;
    endSimulation();


}

ExecutionServer::~ExecutionServer() {
    cancelAndDelete(selfMsg);



}
void ExecutionServer::processMessage( Veneris::Communications::VenerisMessageTypes type, uint32_t size) {
    // TIME

    if (type == Veneris::Communications::VenerisMessageTypes::VenerisMessageTypes_ExternalTime) {
        _ExternalTime();
        return;
    }
}



} //namespace
