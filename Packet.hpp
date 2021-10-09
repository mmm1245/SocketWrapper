#pragma once
#include <vector>
#include <string>
#include "PacketIn.hpp"
	
class Packet  
{
	private:
		std::vector<char> byteBuffer;
	public:
		Packet();
		~Packet();
	public:
		int getLength();
		void addByte(char data);
		void addInt(int data);
		void addCharArray(char* data,int length);
		void addDynamicLengthCharArray(char* data,int length);
		char* getData();
		
};