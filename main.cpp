#include "TCPSocket.hpp"
#include "ServerTCPSocket.hpp"
#include <string.h>
#include <stdio.h>
#include <vector>

int main(){
    ServerTCPSocket serverSocket(3000);
    TCPSocket connecting("127.0.0.1",3000);
    TCPSocket tcpSocket = serverSocket.acceptConnection();
    Packet pac;
    pac.addInt(16548);
    char* arr = "ahoj\0";
    pac.addDynamicLengthCharArray(arr,5);
    tcpSocket.sendMessage(pac);
    tcpSocket.sendMessage(pac);
    std::vector<PacketIn> packets = connecting.readPackets();
    for(int i = 0;i < packets.size();i++){
        printf("size of %d is %d\n", i, packets.at(i).getSize());
        printf("content of %d is %d\n", i, packets.at(i).readInt());
        printf("content of %d is %s\n", i, packets.at(i).readDynamicLengthCharArray(nullptr));
    }
}
