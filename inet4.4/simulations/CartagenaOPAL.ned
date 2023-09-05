package inet.simulations;

import inet.applications.udpapp.UdpBasicApp;
import inet.node.inet.Router;
import inet.node.internetcloud.InternetCloud;

import inet.LoRaPhy.OpalLoRaRadioMedium;

import inet.LoraNode.OpalLoRaNode;
import inet.LoraNode.OpalLoRaGW;
import inet.node.inet.StandardHost;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth1G;

@license(LGPL);
network CartagenaOPAL
{
    parameters:
        int numberOfNodes = default(1);
        int numberOfGateways = default(1);
        int networkSizeX = default(3000);
        int networkSizeY = default(3000);
        @display("bgb=3000,3000");
    submodules:
        loRaNodes[numberOfNodes]: OpalLoRaNode {
            @display("p=143,240");
            id = index;
        }
        loRaGW[numberOfGateways]: OpalLoRaGW {
            @display("p=143,149;is=s");
            id = parent.numberOfNodes+1+index;
        }
        OpalLoRaRadioMedium: OpalLoRaRadioMedium {
            @display("p=791,93");
        }
        networkServer: StandardHost {
            parameters:
                @display("p=618,27");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                assignDisjunctSubnetAddresses = false;
                @display("p=792,27");
        }
        internetCloud: InternetCloud {
            @display("p=362,27");
        }
        gwRouter[numberOfGateways]: Router {
            @display("p=268,27");
        }
        nsRouter: Router {
            @display("p=499,27");
        }
    connections:
        networkServer.ethg++ <--> Eth1G <--> nsRouter.ethg++;
        nsRouter.pppg++ <--> Eth1G <--> internetCloud.pppg++;
        for i=0..numberOfGateways-1 {
            internetCloud.pppg++ <--> Eth1G <--> gwRouter[i].pppg++;
            gwRouter[i].ethg++ <--> Eth1G <--> loRaGW[i].ethg++;
        }
}

