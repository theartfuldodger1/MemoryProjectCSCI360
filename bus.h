/*
Author: Cordell Hurst, Alex BOrtoc, Johnny Zhu
Course: CSCI 360, Computer Architecture III
Instructor: Xiaojie Zhang
Assignment: Software Simulator/Multi-Level Memory Memory Hierarchy

System Bus class
*/
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
		void loadAddress (unsigned long address) { addressBus = address;} // simply holds the address that is being used in load/store instuctions
		bitset<16> loadData (unsigned long address) // uses mainMemory function to search the memory for the data, returns in bitset form
		{ 
			dataBus = MyMemory.search(address); 
			return dataBus;
		}
	private:
		mainMemory MyMemory;
		unsigned long addressBus;
		bitset<16> dataBus;
};

#endif /*__BUS_H__*/