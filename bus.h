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
		//  stores the address that is being used in load/store instuctions into addressBus and uses mainMemory function to getInstruction the memory for the data and loads data into dataBus
		void setAddressBus (unsigned long address)
		{ 
			addressBus = address;
			dataBus = MyMemory.getInstruction(address);
		} 
		// uses mainMemory function to getInstruction the memory for the data, returns in bitset form
		bitset<16> loadDataBus(unsigned long address)
		{ 
			dataBus = MyMemory.getInstruction(address); 
			return dataBus;
		}
		bitset<16>getDataBus(){ return dataBus; }
		
	private:
		mainMemory MyMemory;
		unsigned long addressBus;
		bitset<16> dataBus;
		bool controlBus = 0; //0 == read, 1 == write
};

#endif /*__BUS_H__*/