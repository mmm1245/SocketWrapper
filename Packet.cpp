#include "Packet.hpp"  
	
Packet::Packet()
{
	
}
	
Packet::~Packet()
{
	
}

int Packet::getLength(){
    this->byteBuffer.size();
}
void Packet::addByte(char data){
    this->byteBuffer.push_back(data);
}
void Packet::addInt(int data){
    this->byteBuffer.push_back(((char*)&data)[0]);
    this->byteBuffer.push_back(((char*)&data)[1]);
    this->byteBuffer.push_back(((char*)&data)[2]);
    this->byteBuffer.push_back(((char*)&data)[3]);
}
void Packet::addCharArray(char* data,int length){
    for(int i = 0;i < length;i++){
        addByte(data[i]);
    }
}

void Packet::addDynamicLengthCharArray(char* data,int length){
    addInt(length);
    for(int i = 0;i < length;i++){
        addByte(data[i]);
    }
}

char* Packet::getData(){
    if(getLength() <= 0)
        return nullptr;
    return &this->byteBuffer[0];
}