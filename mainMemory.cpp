

#include "mainMemory.h"

mainMemory::mainMemory()
{
}


mainMemory::~mainMemory()
{
}
//removes all elements leaving the container with a size of 0
void mainMemory::clearInstructionSet()
{
	instructionSet.clear();
}
void mainMemory::set_InstructionSet(list<bitset<16>> &InstructionSet_In)
{
	instructionSet = InstructionSet_In;
}
//returns instruction set list
list <bitset<16>> mainMemory::getInstructionSet()
{
	return instructionSet;
}
//returns next instruction in instruction set list
bitset<16> mainMemory::getNextInstruction()
{
	list <bitset<16>>::iterator iter = instructionSet.begin();
	bitset<16> temp = *iter;
	instructionSet.pop_front();//deletes first element
	return temp;
}