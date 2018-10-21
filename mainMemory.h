#pragma once

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
	list <bitset<16>> getInstructionSet();//returns instruction set list
	bitset<16> getNextInstruction();//returns next instruction in instruction set list
	void printMemory();
private:
	list <bitset<16>> instructionSet;//all instructions loaded here from file
	vector <bitset<16>> memory;
};
#endif /*__MAINMEMORY_H__*/

