#ifndef __BUS_H__
#define __BUS_H__

#include <bitset>
#include "mainMemory.h"
#include "OS.h"

class Bus
{
	public:
		Bus() {};
		~Bus() {};
		void loadAddress (unsigned long address) { addressBus = address;} // current code is placeholder, needs to search main memory for correct address
		bitset<16> loadData (unsigned long address) 
		{ 
			dataBus = MyMemory.search(address); 
			return dataBus;
		} // current code is placeholder, needs to set this to the value of what is in the fetched address 
	private:
		mainMemory MyMemory;
		unsigned long addressBus;
		bitset<16> dataBus;
};

#endif /*__BUS_H__*/