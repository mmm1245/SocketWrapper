#pragma once
#include <string>
#include <vector>

class PacketIn  
{
	private:
		std::vector<char> buffer;
	public:

		PacketIn(std::vector<char> buffer);
		~PacketIn();
	public:
		char readByte();
		int readInt();
		void readCharArray(char* arr, int size);
		char* readDynamicLengthCharArray(int* sizeAddr);
		int getSize();
};