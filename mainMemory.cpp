

#include "mainMemory.h"

mainMemory::mainMemory()
{
	bitset<16>temp;
	for (int i = 0; i < 24; i++)
	{
		memory.push_back(temp);
	}
}


mainMemory::~mainMemory()
{
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
	return temp;
}

void mainMemory::printMemory()
{
	memory[23].flip();
	for (int i = 0; i < 24; i++)
	{
		if ( i % 3 != 0)
		{
			cout << memory[i] << " ";
		}
		else
		{
			cout << endl;
			cout << memory[i] << " ";
		}
	}
}