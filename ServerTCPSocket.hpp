#pragma once
#include "TCPSocket.hpp"
class ServerTCPSocket  
{
	private:
		int socketDescriptor;
		bool badSocket;
	public:
		ServerTCPSocket(int port);
		~ServerTCPSocket();
	public:
		bool isBroken();
		TCPSocket acceptConnection();
};