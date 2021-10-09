#include "ServerTCPSocket.hpp" 
#include "stdio.h"
	
ServerTCPSocket::ServerTCPSocket(int port)
{
    this->badSocket = false;
    int opt = 1;
    struct sockaddr_in address;
	if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        printf("socket failed");
        this->badSocket = true;
        return;
    }
       
    // Forcefully attaching socket to the port 8080
    if (setsockopt(socketDescriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        printf("setsockopt");
        this->badSocket = true;
        return;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );
       
    // Forcefully attaching socket to the port 8080
    if (bind(socketDescriptor, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        printf("bind failed");
        this->badSocket = true;
        return;
    }
    if (listen(socketDescriptor, 3) < 0)
    {
        printf("listen");
        this->badSocket = true;
        return;
    }
}
	
ServerTCPSocket::~ServerTCPSocket()
{
	
}

TCPSocket ServerTCPSocket::acceptConnection(){
    int new_socket;
    if (((new_socket = accept(socketDescriptor, NULL,NULL))<0))
    {
        printf("accept");
        this->badSocket = true;
        return TCPSocket(-1);
    }
    return TCPSocket(new_socket);
}