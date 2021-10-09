#include "TCPSocket.hpp"  
#include <fcntl.h>

TCPSocket::TCPSocket(const char* address, int port)
{
    this->badSocket = false;
	struct sockaddr_in serv_addr;
    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        this->badSocket = true;
        return;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, address, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        this->badSocket = true;
        return;
    }
    if (connect(socketDescriptor, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        this->badSocket = true;
    }
    int flags = fcntl(this->socketDescriptor, F_GETFL, 0);
    fcntl(this->socketDescriptor, F_SETFL, flags | O_NONBLOCK);
    this->dataTillNow = nullptr;
    this->dataStart = nullptr;
    this->buffWriteLen = 0;
}
TCPSocket::TCPSocket(int _socketDescriptor){
    if(_socketDescriptor == -1){
        this->badSocket = true;
        printf("socket is broken");
        return;
    }
    this->badSocket = false;
    this->socketDescriptor = _socketDescriptor;
    this->dataTillNow = nullptr;
    this->dataStart = nullptr;
    this->buffWriteLen = 0;
}
TCPSocket::~TCPSocket()
{
	if(this->dataStart != nullptr)
        delete this->dataStart;
}

bool TCPSocket::isBroken(){
    return badSocket;
}

bool TCPSocket::sendMessage(Packet& packet){
    if(isBroken()){
        printf("socket is broken");
        return false;
    }
    int len = packet.getLength();
    send(socketDescriptor , &len , sizeof(int) , 0 );
    send(socketDescriptor , packet.getData() , len , 0 );
}
std::vector<PacketIn> TCPSocket::readPackets(){
    bool shouldntStop = true;
    std::vector<PacketIn> vecPackets;
    do {
        PacketIn p = readOnePacket();
        if(p.getSize() > 0){
            vecPackets.push_back(p);
        }else{
            shouldntStop = false;
        }
    } while(shouldntStop);
    return vecPackets;
}

PacketIn TCPSocket::readOnePacket(){
    if(this->dataStart == nullptr){
        int ret = read( socketDescriptor , &this->buffWriteLen, sizeof(int));
        if(ret >= ((int)sizeof(int))){
            //printf("starting to receive packet of size: %d\n", ret);
            this->dataStart = new char[this->buffWriteLen];
            this->dataTillNow = dataStart;
        }
    }
    if(this->dataStart != nullptr){
        int ret = read( socketDescriptor , dataTillNow, (int)(this->dataStart + buffWriteLen - this->dataTillNow));
        if(ret > 0){
            //printf("received data chunk of size: %d\n", ret);
            this->dataTillNow += ret;
            if(this->dataStart + buffWriteLen >= this->dataTillNow){
                //printf("finished receiving: %s\n",this->dataStart);
                PacketIn toRet = PacketIn(std::vector<char>(dataStart,dataTillNow));
                this->buffWriteLen = 0;
                delete this->dataStart;
                this->dataStart = nullptr;
                this->dataTillNow = nullptr;
                return toRet;
            }
        }
    }
    return PacketIn(std::vector<char>());
}