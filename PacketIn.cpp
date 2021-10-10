#include "PacketIn.hpp"  
	
PacketIn::PacketIn(std::vector<char> buffer)
{
	for(int i = 0;i < buffer.size();i++){
        this->buffer.push_back(buffer.at(buffer.size()-i-1));
    }
}
	
PacketIn::~PacketIn()
{
	
}

char PacketIn::readByte(){
    auto ret = this->buffer.back();
    this->buffer.pop_back();
    return ret;
}
int PacketIn::readInt(){
    int toRet;
    char* toRetP = ((char*)&toRet);
    for(int i = 0;i < 4;i++){
        toRetP[i] = readByte();
    }
    return toRet;
}
void PacketIn::readCharArray(char* arr, int size){
    if(size > this->buffer.size())
        return;
    for(int i = 0;i < size;i++){
        arr[i] = buffer.back();
        buffer.pop_back();
    }
}
char* PacketIn::readDynamicLengthCharArray(int* sizeAddr){
    int size = readInt();
    if(sizeAddr != nullptr)
        *sizeAddr = size;
    char* arr = new char[size];
    readCharArray(arr, size);
    return arr;
}

int PacketIn::getSize(){
    return this->buffer.size();
}