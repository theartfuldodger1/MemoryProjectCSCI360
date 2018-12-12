/*
Author: Cordell Hurst, Alex BOrtoc, Johnny Zhu
Course: CSCI 360, Computer Architecture III
Instructor: Xiaojie Zhang
Assignment: Software Simulator/Multi-Level Memory Memory Hierarchy
This program...

4 General Purpose Registers (GPRs), the four GPRs are numbered 0-3 and can be mnemonically referred to as R0 – R3. They may be used as accumulators.
1 Index Registers, the index register is referred to as X0, contains a 16-bit base address that supports base register addressing of memory.
1 Program Counter, address of next instruction to be executed, referred to as PC.
1 Instruction Register, holds the instruction to be executed, referred to as IR.
Memory Address Register MAR: holds the address of the word to be fetched from memory.
Memory Buffer Register MBR: holds the data just fetched from or stored into memory.
*/
/*
Opcode  I  IX AC  Address
000001  0  0  11  101100
15  10  9  8  76  5    0
*/

#include "cache.h"

cache::cache()
{
	for (int i = 0; i < 4; i++)
	{
		Register GPR;
		GeneralPurposeRegisters_GPRs[i] = GPR;
//cout << i << " = " << GPR.word << endl;
	}
}

//Postfix
bitset<16> operator++ (bitset<16> &setIn, int tempInt)
{
	tempInt = setIn.to_ulong();
	tempInt++;
	setIn = tempInt;
	return setIn;
}
//Prefix
bitset<16> operator++ (bitset<16> &setIn)
{
	int tempInt = setIn.to_ulong();
	tempInt++;
	setIn = tempInt;
	return setIn;
}
//holds 16 bit address of next instruction to be executed
bitset<16> cache::getProgramCounter_PC()
{
	return programCounter_PC;
}
//Returns list of registers
Register* cache::getGeneralPurposeRegisters_GPRs()
{
	return GeneralPurposeRegisters_GPRs;
}
//Returns selected General Purpose Register Word, 0-3
bitset<16> cache::getGeneralPurposeRegisters_GPRs(int intIn)
{
	return GeneralPurposeRegisters_GPRs[intIn].word;
}
//contains a 16-bit base address that supports base register addressing of memory
bitset<16> cache::getIndexRegister_X0()
{
	return IndexRegister_X0;
}
//holds the 16 bit instruction to be executed
bitset<16> cache::getInstructionRegister_IR()
{
	return InstructionRegister_IR;
}

bitset<16> cache::getMemoryAddressRegister_MAR()
{
	return MemoryAddressRegister_MAR;
}

bitset<16> cache::getMemoryBufferRegister_MBR()
{
	return MemoryBufferRegister_MBR;
}

bitset<1> cache::get_ZF()
{
	return ZF;
}

bitset<1> cache::get_CF()
{
	return CF;
}

bitset<1> cache::get_SF()
{
	return SF;
}

//Sets selected General Purpose Register, 0-3
//accepts an int, representing one of the four register elements, and a 16 bit bitset as the data/instruction
void cache::setGeneralPurposeRegisters_GPRs(int gprIn, bitset<16> setIn)
{
	GeneralPurposeRegisters_GPRs[gprIn].word = setIn;
}

void cache::setIndexRegister_X0(bitset<16> setIn)
{
	IndexRegister_X0 = setIn;
}

void cache::setInstructionRegister_IR(bitset<16> setIn)
{
	InstructionRegister_IR = setIn;
}
//set MemoryAddressRegister (0-2047) as bitset<16>
void cache::setMemoryAddressRegister_MAR(bitset<16> setIn)
{
	MemoryAddressRegister_MAR = setIn;
}

void cache::setMemoryBufferRegister_MBR(bitset<16> setIn)
{
	MemoryBufferRegister_MBR = setIn;
}



//sets programCounter_PC from a bitset<16>
void cache::set_ProgramCounter(bitset<16> instIn)
{
	programCounter_PC = instIn;
}
//Sets programCounter_PC from an int
void cache::set_ProgramCounter(int instPos)
{
	programCounter_PC = instPos;
}
void cache::increment_ProgramCounter()
{
	programCounter_PC++;
}


void cache::set_ZF(int bit)
{
	if (bit == 1)
		ZF.set();
	else if (bit == 0)
		ZF.reset();
}

void cache::set_CF(int bit)
{
	if (bit == 1)
		CF.set();
	else if (bit == 0)
		CF.reset();
}

void cache::set_SF(int bit)
{
	if (bit == 1)
		SF.set();
	else if (bit == 0)
		SF.reset();
}
//Resets all registers to all 0's
void cache::resetAllRegisters()
{
	for (int i = 0; i < 4; i++)
		GeneralPurposeRegisters_GPRs[i].word.reset();

	IndexRegister_X0.reset();
	InstructionRegister_IR.reset();
	MemoryAddressRegister_MAR.reset();
	MemoryBufferRegister_MBR.reset();
}

void cache::printRegisters(bool special)//param only needed for stepInstructions() in OS. otherwise, defaults to false
{
/*
	//'Q' option returns to main menu
	//'H' option provides explanation of the viewed environment	

					Registers
		------------------------------------
		GPRx4
		R0 == >	0000	0000	0000	0000
		R1 == >	0000	0000	0000	0000
		R2 == > 0000 	0000	0000	0000
		R3 == > 0000	0000	0000	0000

		IR == > 0000	0000	0000	0000
		PC == > 0000	0000	0000	0000
		X0 == >	0000 	0000 	0000	0000
		MA == > 0000 	0000	0000	0000
		MB == > 0000 	0000	0000	0000
		------------------------------------
		Enter Q for Menu or H for Help
*/
	cout << "\n";
	cout << right;
	cout << setw(38) << setfill(' ') << "Registers"
		<< "\n\t\t----------------------------------"
		<< "\n\t\tGPRx4";

	for (int i = 0; i < 4; i++)
	{
		cout << "\n\t\tR" << i << " ==>";
		for (int j = 15; j >= 0; j--)
		{
			if (j % 4 == 3)
				cout << "   ";
			cout << GeneralPurposeRegisters_GPRs[i].word[j];
		}
	}
	cout << "\n\t\tIR ==>";
	for (int i = 15; i >= 0; i--)
	{
		if (i % 4 == 3)
			cout << "   ";
		cout << InstructionRegister_IR[i];
	}
	cout << "\n\t\tXO ==>";
	for (int i = 15; i >= 0; i--)
	{
		if (i % 4 == 3)
			cout << "   ";
		cout << IndexRegister_X0[i];
	}
	cout << "\n\t\tMB ==>";
	for (int i = 15; i >= 0; i--)
	{
		if (i % 4 == 3)
			cout << "   ";
		cout << MemoryBufferRegister_MBR[i];
	}
	cout << "\n\t\tMA ==>";
	bool firstPass = 0;
	for (int i = 0; i < 6; i++)//(int i = 5; i < 0; i++)
	{
		if (i % 3 == 0)
		{
			if (firstPass == 0)
			{
				cout << "   ";
				firstPass = 1;
			}
			else
				cout << "    ";
		}
		cout << MemoryAddressRegister_MAR[i];
	}
	cout << "\n\t\tPC ==>";
	firstPass = 0;
	for (int i = 0; i < 6; i++)
	{
		if (i % 3 == 0)
			if (firstPass == 0)
			{
				cout << "   ";
				firstPass = 1;
			}
			else
				cout << "    ";
		cout << programCounter_PC[i];
	}

	cout << "\n\t\t----------------------------------";
	if(!special)
	{
		cout << "\n\t\t" << setw(10) << setfill(' ') << "Q. Menu" << setw(20) << setfill(' ') << "H. Help"
			<< "\n\n\t\t==>> ";

		char input;
		do
		{
			cin >> input;
			cin.ignore(255, '\n');
			failCheck(cin);

			//call help file needed
			if (input == 'H' || input == 'h')
				cout << "\t\nHelp File incomplete..." << endl;

		}while (input != 'Q' && input != 'q');
	}
}
//catches failed input cast and resets istream
void cache::failCheck(istream &cin)
{
	if (cin.fail())
	{
		cout << "Incorrect input:" << endl;
		cin.clear();
		cin.ignore(255, '\n');
	}
}


//cache design

void cache::setInstrCache(int set_assoc, int block_num, int word_num, vector<bitset<16>> memIn)
{
	temp = memIn;
	set_size = set_assoc;
	block_amount = block_num;
	word_amount = word_num;
	cache_table = new SET[set_size];
	for (int i = 0; i < set_size; i++)
	{
		cache_table[i].blocks = new BLOCK[block_amount];
	}

	offset = log2(word_amount);
	index = log2(set_size);
	tag = 16 - offset - index;
}
void cache::printCache()
{
	for (int i = 0; i < set_size; i++)
	{
		for (int j = 0; j < block_amount; j++)
		{
			cout << cache_table[i].blocks[j].instruction << " " << setw(4) << setfill(' ');
			cout << cache_table[i].blocks[j].block_tag << setw(4) << setfill(' ');
			cout << getIndexValue(cache_table[i].blocks[j].instruction) << setw(4) << setfill(' ');
			cout << cache_table[i].blocks[j].valid << setw(4) << setfill(' ');
			cout << cache_table[i].blocks[j].timer;
			cout << "	";
		}
		cout << endl;
	}
}
int cache::getOffset()
	{
		return offset;
	}

int cache::getIndex()
	{
		return index;
	}

int cache::getTag()
	{
		return tag;
	}

void cache::hitInc() {
		hit++;
	}
void cache::missInc() {
		miss++;
	}
void cache::replaceInc() {
		replace++;
	}

int cache::getTagValue(bitset<16> setIn)
{
	int ind_num = getIndex();
	int off_num = getOffset();
	int tag = 0;
	for (int i = 0; i < temp.size(); i++)
	{
		if (setIn == temp[i])
		{
			tag = i;
			break;
		}
	}
	bitset<16> tag_bits(tag);
	if (ind_num == 0)
	{
		int tag_value = tag_bits.to_ulong();
		return tag_value;
	}
	else if (ind_num == 1)
	{
		bitset<15> tag_bits1; //index 1
		for (int i = 14; i >= 0; i--)
		{
			tag_bits1[i] = tag_bits[i + 1];
		}
		int tag_value = tag_bits1.to_ulong();
		return tag_value;
	}
	else if (ind_num == 2)
	{
		bitset<14> tag_bits2; //index 2
		for (int i = 13; i >= 0; i--)
		{
			tag_bits2[i] = tag_bits[i + 2];
		}
		int tag_value = tag_bits2.to_ulong();
		return tag_value;
	}
	else if (ind_num == 3)
	{
		bitset<13> tag_bits3; //index 3
		for (int i = 12; i >= 0; i--)
		{
			tag_bits3[i] = tag_bits[i + 3];
		}
		int tag_value = tag_bits3.to_ulong();
		return tag_value;
	}
}

int cache::getIndexValue(bitset<16> setIn)
{
	int index_num = getIndex();
	int offset_num = getOffset();
	bitset<3> index_bits3;
	bitset<2> index_bits2;
	bitset<1> index_bits1;
	int index = 0;
	for (int i = 0; i < temp.size(); i++)
	{
		if (setIn == temp[i])
		{
			index = i;
			break;
		}
	}
	bitset<16> index_bits(index);
	if (index_num == 3)
	{
		for (int i = index_num - 1; i >= offset; i--)
		{
			if (index_bits[i] == 1)
			{
				index_bits3[i] = index_bits[i];
			}
		}
		int index_value = index_bits3.to_ulong();
		return index_value;
	}
	else if (index_num == 2)
	{
		for (int i = index_num - 1; i >= offset; i--)
		{
			if (index_bits[i] == 1)
			{
				index_bits2[i] = index_bits[i];
			}
		}
		int index_value = index_bits2.to_ulong();
		return index_value;
	}
	else if (index_num == 1)
	{
		for (int i = index_num - 1; i >= offset; i--)
		{
			if (index_bits[i] == 1)
			{
				index_bits1[i] = index_bits[i];
			}
		}
		int index_value = index_bits1.to_ulong();
		return index_value;
	}
	else
	{
		int index_value = 0;
		return index_value;
	}
}

bool cache::getNotFull()
{
	return not_full;
}

void cache::setNotFullTrue()
{
	not_full = true;
}

void cache::setNotFullFalse()
{
	not_full = false;
}

void cache::addInstruction(bitset<16> setIn)
{
	string result;
	int tag_value = getTagValue(setIn);
	int index_value = getIndexValue(setIn);
	setNotFullFalse();

	for (int j = 0; j < block_amount; j++)
	{
		cache_table[index_value].blocks[j].timer++;
		if (cache_table[index_value].blocks[j].valid == false) {
			setNotFullTrue();
		}
	}

	for (int j = 0; j < block_amount; j++)
	{
		if (getTagValue(cache_table[index_value].blocks[j].instruction) == getTagValue(setIn))
		{
			if (cache_table[index_value].blocks[j].valid == true)
			{
				cache_table[index_value].blocks[j].timer = 0;
				hitInc();
				return; //return block data
			}
			else {
				result = "MISS";
			}
		}
	}

	if (getNotFull() == true) { //result is a miss if the set is not full or the the sought after tag has a false valid
		missInc();
		result = "MISS";
	}
	else {	//if set is full we have to replace
		replaceInc();
		result = "REPLACE";
	}

	bool place_found = false;
	if (result == "MISS") {
		for (int j = 0; j < block_amount; j++) {
			if (place_found == false) {
				if (cache_table[index_value].blocks[j].valid == false) { //if the valid bit is 0 then block is empty
					cache_table[index_value].blocks[j].instruction = setIn;
					cache_table[index_value].blocks[j].block_tag = getTagValue(setIn);
					cache_table[index_value].blocks[j].valid = true;
					cache_table[index_value].blocks[j].timer = 0;
					place_found = true;
					break;
				}
			}
		}
	}
	else if (result == "REPLACE") {
		int max = 0;
		int y;
		for (int j = 0; j < block_amount; j++) {
			if (max < cache_table[index_value].blocks[j].timer) { //if there is a block with a bigger timer
				max = cache_table[index_value].blocks[j].timer;
				y = j;
			}
		}
		cache_table[index_value].blocks[y].instruction = setIn;
		cache_table[index_value].blocks[y].block_tag = getTagValue(setIn);
		cache_table[index_value].blocks[y].valid = true;
		cache_table[index_value].blocks[y].timer = 0;
	}
}

void cache::printHits()
{
	cout << "Hits: " << hit << " Miss: " << miss << " Replace: " << replace << endl;
}