package inet.simulations;

import inet.applications.udpapp.UdpBasicApp;
import inet.node.inet.Router;
import inet.node.internetcloud.InternetCloud;
import inet.LoRaPhy.LoRaMedium;
import inet.LoraNode.OpalLoRaNode;
import inet.LoraNode.OpalLoRaGW;
import inet.node.inet.StandardHost;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth1G;

@license(LGPL);
network LoRaNetworkTest
{
    parameters:
        int numberOfNodes = default(1);
        int numberOfGateways = default(1);
        int networkSizeX = default(500);
        int networkSizeY = default(500);
        @display("bgb=562,417");
    submodules:
        loRaNodes[numberOfNodes]: OpalLoRaNode {
            @display("p=400,304");
            id = index;
        }
        loRaGW[numberOfGateways]: OpalLoRaGW {
            @display("p=157,238;is=s");
            id = parent.numberOfNodes+1+index;
        }
        LoRaMedium: LoRaMedium {
            @display("p=309,102");
        }
        networkServer: StandardHost {
            parameters:
                @display("p=49,44");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                assignDisjunctSubnetAddresses = false;
                @display("p=318,27");
        }
        internetCloud: InternetCloud {
            @display("p=231,44");
        }
        gwRouter[numberOfGateways]: Router {
            @display("p=231,134");
        }
        nsRouter: Router {
            @display("p=137,44");
        }
    connections:
        networkServer.ethg++ <--> Eth1G <--> nsRouter.ethg++;
        nsRouter.pppg++ <--> Eth1G <--> internetCloud.pppg++;
        for i=0..numberOfGateways-1 {
            internetCloud.pppg++ <--> Eth1G <--> gwRouter[i].pppg++;
            gwRouter[i].ethg++ <--> Eth1G <--> loRaGW[i].ethg++;
        }
}

