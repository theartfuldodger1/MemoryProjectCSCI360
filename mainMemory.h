#pragma once

#ifndef __MAINMEMORY_H__
#define __MAINMEMORY_H__

#include <bitset>
#include <list>

using namespace std;

//need to complete definition of this class according to procject spec
class mainMemory
{
public:
	mainMemory();
	~mainMemory();
	list <bitset<16>> getInstructionSet();//returns instruction set list
	bitset<16> getNextInstruction();//returns next instruction in instruction set list
	void clearInstructionSet();//removes all elements leaving the container with a size of 0
	void set_InstructionSet(list<bitset<16>> &);

private:
	list <bitset<16>> instructionSet;//all instructions loaded here from file
};
#endif /*__MAINMEMORY_H__*/

