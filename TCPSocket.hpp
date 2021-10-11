#pragma once
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Packet.hpp"
	
class TCPSocket  
{
	private:
		int socketDescriptor;
		bool badSocket;

		int buffWriteLen;
		char* dataStart;
		char* dataTillNow;
	public:
		TCPSocket(const char* address, int port);
		TCPSocket(int socketDescriptor);
		~TCPSocket();
	public:
		bool isBroken();
		bool sendMessage(Packet* packet);
		std::vector<PacketIn> readPackets();
		PacketIn readOnePacket();
};
