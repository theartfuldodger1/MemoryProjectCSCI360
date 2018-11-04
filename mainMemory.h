/*
Author: Cordell Hurst, Alex BOrtoc, Johnny Zhu
Course: CSCI 360, Computer Architecture III
Instructor: Xiaojie Zhang
Assignment: Software Simulator/Multi-Level Memory Memory Hierarchy
This program...
*/

#ifndef __MAINMEMORY_H__
#define __MAINMEMORY_H__

#include <bitset>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

//need to complete definition of this class according to procject spec
class mainMemory
{
public:
	mainMemory();
	~mainMemory();
	//vector <bitset<16>> getInstructionSet();//returns instruction set list
	bitset<16> getInstruction(bitset<16> &);//returns instruction in instruction set list at input param address
	void insertInstruction(bitset<16> &, bitset<16> &);//accepts bitset<16> instruction and bitseet<16> effectiveAddress. Inserts instruction into MM vector
	void insertInstruction(bitset<16> &, int);//accepts bitset<16> instruction and int sequential count. Inserts instruction into MM vector
	void clearMemory();
	void printMemory();
	void failCheck(istream &cin);
	bitset<16> getInstruction(unsigned long address); //getInstruction function that simply navigates to the specified place in the vector
	void setMemoryElement(unsigned long address, bitset<16> setIn); //sets indicated memory location to specified value

private:
	//vector <bitset<16>> instructionSet;//all instructions loaded here from file, 2048 words/4096 bytes
	vector <bitset<16>> memory;
};
#endif /*__MAINMEMORY_H__*/

