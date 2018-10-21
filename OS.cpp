/*
Author: Cordell Hurst
Course: 340, Operating Systems
Instructor: Prof Pavel Shostak
Assignment: OperatingSystem/Memory Management Simulation
computer
*/
/*             R
Opcode  I  IX AC  Address
000001  0  0  11  101100
15  10  9  8  76  5    0
*/

#include "OS.h"

using namespace std;

OS::OS()
{
	
}
//Destructor
OS::~OS()
{
}
//Switch - where all the magic happens. 
void OS::switchGo(/*processor CPU, main_memory memory_module, HDD HDDArray*/)
{
	/*
	Initialization Menu
	----------------------------------------------------
	1. Add Instruction File
	2. Add Instruction Line By Line
	3. Display Empty Registers
	4. Display Instruction Display with Default Values
	5. Display Empty Memory
	6. Help
	7. Quit

	==>>
	*/
	unsigned short int param = 0;
	do
	{
		cout << "\n";
		initializationMenu();
		cin >> param;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		failCheck(cin);

		if (param <= 0 || param > 8)
		{
			cout << "\n\tIncorrect input:" << endl;
			param = 0;
		}

		if (param > 0 || param < 9)
			switch (param)
			{
			case 1: //Add Instruction File
			{
				param = menu1A();
			}
			break;
			case 2: //Add Instruction Line By Line
			{
				param = menu1B();
			}
			break;
			case 3: //Display Empty Registers
			{

			}
			break;
			case 4: //Display Instruction Display with Default Values
			{

			}
			break;
			case 5: //Display Empty Memory
			{

			}
			break;
			case 6: //Help
			{

			}
			break;
			case 7: //Quit
			{
				//exit
				cout << "Bye!" << endl;
			}
			break;
			}
	} while (param != 7);

	//for testing BEGIN
	int temp = 0;
	list <bitset<16>>::iterator iter = InstructionSet_OS.begin();
	while (iter != InstructionSet_OS.end())
	{
		cout << "List position:: " << temp << ", Item:: " << *iter << endl;
		cout << "\tposition:: " << temp << ", size:: " << iter->size() << endl;
		iter++;
		temp++;
	}
	//for testing END
}
//catches failed input cast and resets istream
void OS::failCheck(istream &cin)
{
	if (cin.fail())
	{
		cout << "Incorrect input:" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}

void OS::initializationMenu()
{
	/*
					Initialization Menu
	----------------------------------------------------
	1. Add Instruction File
	2. Add Instruction Line By Line
	3. Load Program to Main Memory
	4. Display Empty Registers
	5. Display Instruction Display with Default Values
	6. Display Empty Memory
	7. Help
	8. Quit

	==>>
	*/

	cout << right;
	cout << setw(45) << "Initialization Menu"
		<< "\n\t----------------------------------------------------"
		<< "\n\t1. Add Instruction File"
		<< "\n\t2. Add Instruction Line By Line"
		<< "\n\t3. Display Empty Registers"
		<< "\n\t4. Display Instruction Display with Default Values"
		<< "\n\t5. Display Empty Memory"
		<< "\n\t6. Help"
		<< "\n\t7. Quit"
		<< "\n\n\t==>> ";
}
//add instruction file from Menu1, choice 1
unsigned short int OS::menu1A()
{
	/*
				 Add an Instruction File
	---------------------------------------------------
	Please ensure usage of proper case.

	=>>
	*/
	string fileIn;
	ifstream instructionFile;
	bool fileFail = 1;
	do
	{
		cout << right;
		cout << setw(45) << "Add an Instruction File"
			<< "\n\t---------------------------------------------------"
			<< "\n\tPlease ensure usage of proper case."
			<< "\n\n\t==>> ";
		
		cin >> fileIn;
		instructionFile.open(fileIn);

		if (!instructionFile.is_open())
			cerr << "\n\tCould not open file\n\n";


	} while (!instructionFile.is_open());

	processFile(instructionFile, InstructionSet_OS);
	unsigned short int paramOut = menu2();
	return paramOut;
}
void OS::processFile(istream &cin)
{
	/*             R
	Opcode  I  IX AC  Address
	000001  0  0  11  101100
	15  10  9  8  76  5    0
	*/
	bitset<16> buildSet;
	bool firstPass = 1;
	bool stringFlag = 1;
	//int peek;
	string inFile;
	//cin >> inFile;
	//inFile = scrollWhiteSpace(cin);
	cout <<"IN Proc File" <<endl;
	//while (peek != EOF && peek != 10)
	{
		buildSet.reset();

		//Acquire and encode opCode - BEGIN
		bitset<6> opCode = streamToOpCode(cin);
		int j = 10;
		for (int i = 0; i < 6; i++)
		{
		cout << "in opcode loop" << endl;
			buildSet[j] = opCode[i];
			j++;
		}
		cout << "opCode: " << opCode << endl;
		//Acquire and encode opCode - END

		//Load/Store Instructions //Comparison Instruction -> LDR(1), STR(2), AMR(4), SMR(5), CMP(17) //Form --> opCode r, i, x, address
		if (opCode == 1 || opCode == 2 || opCode == 4 || opCode == 5 || opCode == 17)
			codeRIXA(cin, buildSet, stringFlag);
		//Load/Store Instructions //Transfer Instructions -> LDX(41), STX(42), JE(10), JNE(11), JG(12), JGE(14), JL(15), JLE(16), JUMP(13) //Form --> opCode i, x, address
		else if (opCode == 41 || opCode == 42 || opCode == 10 || opCode == 11 || opCode == 12 || opCode == 13 || opCode == 14 || opCode == 15 || opCode == 16)
			codeIXA(cin, buildSet, stringFlag);
		//Basic Arithmetic and Logic Instructions -> AIR(6), SIR(7) //Form --> opCode, r, immed
		else if (opCode == 6 || opCode == 7)
			codeRimmed(cin, buildSet, stringFlag);
		//-> DEC(8), INC(9) //Form --> opCode, r, immed
		else if (opCode == 8 || opCode == 9)
			codeR(cin, buildSet, stringFlag);
		//Advanced Arithmetic and Logical Instructions -> MUL(20), DIV(21), TER(22), AND(23), ORR(24) //form --> opCode, rx, ry
		else if (opCode == 20 || opCode == 21 || opCode == 22 || opCode == 23 || opCode == 24)
			codeRxRy(cin, buildSet, stringFlag);
		//-> NOT(25) //form --> opCode, rx
		else if (opCode == 25)
			codeRx(cin, buildSet, stringFlag);
		//-> ADD(26), SUB(27) //form --> opCode, rx, ry, i, ix
		else if (opCode == 26 || opCode == 26)
			codeRRII(cin, buildSet, stringFlag);

		InstructionSet_OS.push_back(buildSet);
		cout << "pushed processFile!" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		failCheck(cin);
		cout << "Cleared processFile" << endl;
	}

	cout << "second Cleared processFile" << endl;
	//for testing BEGIN
	int tempTest = 0;
	list <bitset<16>>::iterator iter = InstructionSet_OS.begin();
	while (iter != InstructionSet_OS.end())
	{
		cout << "List position:: " << tempTest << ", Item:: " << *iter << endl;
		cout << "\tposition:: " << tempTest << ", size:: " << iter->size() << endl;
		iter++;
		tempTest++;
	}
	//for testing END
	cout << "passed testing processFile" << endl;
}
// add individual instructions from Menu1, choice 2
unsigned short int OS::menu1B()
{
	/*
	Add Individual Instructions
	---------------------------------------------------
	Enter Instructions in the following form: MOV 0100 0011
	Enter Q if you are finished.

	=>>
	*/
	cout << right;
	cout << setw(45) << "Add Individual Instructions"
		<< "\n\t---------------------------------------------------"
		<< "\n\tEnter Instructions in the following form: MOV 0100 0011"
		<< "\n\tand Enter after each instruction."
		<< "\n\tEnter Q if you are finished."
		<< "\n\n\t=>> ";
	string instructionIn;
	//cin >> instructionIn;0

	int peek = cin.peek();
	cout << "PEEK: " << peek << endl;
	do
	//while (peek != 81 && peek != 113)
	{
		peek = cin.peek();
		cout << "PEEK2: " << peek << endl;
		processFile(cin);

		cout << "\n\t=>>";
		cin >> instructionIn;
		cout << "INSTRUCTION IN: " << instructionIn << endl;
		peek = cin.peek();
		cout << "PEEK3: " << peek << endl;
	}while (instructionIn != "Q" && instructionIn != "q");

	unsigned short int paramOut = menu2();
	return paramOut;
}
//simulation menu, follows addition of instructions (menu1A or 1B). Choice 1 returns the user to Menu 1 (Initialization Menu)
unsigned short int OS::menu2()
{
	/*
	Simulation Menu
	---------------------------------------------------
	1. 	Clear All Data and Start Over
	2. 	Add Instruction Line to End of Queue
	3.	Load Program into Main Memory
	4.	Display Empty Registers
	5.	Display Instruction with Default Values
	6. 	Display Empty Memory
	7.	Help
	8. 	Quit

	==>>
	*/

	unsigned short int paramOut = 0;
	unsigned short int param = 0;
	do
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		failCheck(cin);
		char cleaner[256];
		cin.getline(cleaner, 256);

		cout << "\n";
		cout << "MENU2: " << param << endl;
		cout << right;
		cout << setw(40) << "Simulation Menu"
			<< "\n\t---------------------------------------------------"
			<< "\n\t1. Clear All Data and Start Over"
			<< "\n\t2. Add Instruction Line to End of Queue"
			<< "\n\t3. Load Program into Main Memory"
			<< "\n\t4. Display Empty Registers"
			<< "\n\t5. Display Instruction with Default Values"
			<< "\n\t6. Display Empty Memory"
			<< "\n\t7. Help"
			<< "\n\t8. Quit" 
			<< "\n\n\t=>> ";
//		initializationMenu();
		cin >> param;
		cout << "POST: " << param << endl;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		failCheck(cin);
		//cout << "You entered: " << input << endl;

		if (param <= 0 || param > 8)
		{
			cout << "\n\tIncorrect input:" << endl;
			param = 0;
		}

		else //if (param > 0 || param < 9)
			switch (param)
			{
				case 1://1. Clear All Data and Start Over ////Return to Initialization Menu
				{
					MyCache.clear_AllRegisters();//resets all bitsets via bitset<x>.reset()
					InstructionSet_OS.clear();//removes all elements leaving the container with a size of 0
					//paramOut = 0;
					param = 8;
				}
				break;
				case 2://2. Add Instruction Line to End of Queue
				{
						menu1B();
						cout << "OUT OF MENU1B" << endl;
				}
				break;
				case 3://3. Load Program into Main Memory
				{

					if (InstructionSet_OS.size() == 0)
						cout << "Instruction Set is empty."
						<< "\nPlease add instructions before attempting to load to main memory" << endl;
					else
						MyMemory.set_InstructionSet(InstructionSet_OS);
				}
				break;
				case 4://4. Display Empty Registers
				{

				}
				break;
				case 5://5. Display Instruction with Default Values
				{

				}
				break;
				case 6://6. Display Empty Memory
				{

				}
				break;
				case 7://7. Help
				{

				}
				break;
				case 8://8. Quit
				{
					paramOut = 7;
					param = 8;
				}
				break;
			}
		cout << "POST - POST@@@@: " << param << endl;
	} while (param != 8);
	return paramOut;
}
//follows loading of program into main memory - choice 3 from menu2/simulation menu
//if user selects choice 1, return to Menu 1, initializatinMenu()
unsigned short int  OS::menu2A()
{
	/*
	Simulation Menu
	---------------------------------------------------
	1. 	Clear all data and start over
	2. 	Add Instruction Line to End of Queue
	3.	Display Registers
	4.	Display Instructions
	5. 	Display Memory
	6.	Help
	7. 	Quit

	==>>
	*/
	unsigned short int paramOut = 0;
	unsigned short int param = 0;
	do
	{
		cout << "\n";
		cout << right;
		cout << setw(40) << "Simulation Menu"
			<< "\n\t---------------------------------------------------"
			<< "\n\t1. Clear All Data and Start Over"
			<< "\n\t2. Add Instruction Line to End of Queue"

			<< "\n\t3. Display Empty Registers"
			<< "\n\t4. Display Instruction with Default Values"
			<< "\n\t5. Display Empty Memory"
			<< "\n\t6. Help"
			<< "\n\t7. Quit"
			<< "\n\n\t=>> ";
		//		initializationMenu();
		cin >> param;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		failCheck(cin);
		//cout << "You entered: " << input << endl;

		if (param <= 0 || param > 8)
		{
			cout << "\n\tIncorrect input:" << endl;
			param = 0;
		}

		if (param > 0 || param < 9)
			switch (param)
			{
			case 1://1. Clear All Data and Start Over ////Return to Initialization Menu
			{
				MyCache.clear_AllRegisters();
				InstructionSet_OS.clear();//removes all elements leaving the container with a size of 0
				
				//paramOut = 0;
				param = 7;
			}
			break;
			case 2://2. Add Instruction Line to End of Queue
			{
				param = menu1B();
			}
			break;
			case 3://3. Display Empty Registers
			{

			}
			break;
			case 4://4. Display Instruction with Default Values
			{

			}
			break;
			case 5://5. Display Empty Memory
			{

			}
			break;
			case 6://6. Help
			{

			}
			break;
			case 7://7. Quit
			{
				paramOut = 7;
			}
			break;
			}
	} while (param != 7);
	return paramOut;
}

void OS::processFile(ifstream &inFile, list <bitset<16>> &instructions)
{
	/*             R
	Opcode  I  IX AC  Address
	000001  0  0  11  101100
	15  10  9  8  76  5    0
	*/
	bitset<16> buildSet;
	bool firstPass = 1;
	bool stringFlag = 0;
	
	while(!inFile.eof())
	{ 
		buildSet.reset();
		
		//Acquire and encode opCode - BEGIN
		bitset<6> opCode = streamToOpCode(inFile);
		int j = 10;
		for (int i = 0; i < 6; i++)
		{
			buildSet[j] = opCode[i];
			j++;
		}
		//opCode = opCode;
		//Acquire and encode opCode - END

		//Load/Store Instructions //Comparison Instruction -> LDR(1), STR(2), AMR(4), SMR(5), CMP(17) //Form --> opCode r, i, x, address
		if (opCode == 1 || opCode == 2 || opCode == 4 || opCode == 5 || opCode == 17 )
			codeRIXA(inFile, buildSet, stringFlag);
		//Load/Store Instructions //Transfer Instructions -> LDX(41), STX(42), JE(10), JNE(11), JG(12), JGE(14), JL(15), JLE(16), JUMP(13) //Form --> opCode i, x, address
		else if (opCode == 41 || opCode == 42 || opCode == 10 || opCode ==11 || opCode == 12 || opCode == 13 || opCode == 14 || opCode == 15 || opCode == 16)
			codeIXA(inFile, buildSet, stringFlag);
		//Basic Arithmetic and Logic Instructions -> AIR(6), SIR(7) //Form --> opCode, r, immed
		else if (opCode == 6 || opCode == 7)
			codeRimmed(inFile, buildSet, stringFlag);
		//-> DEC(8), INC(9) //Form --> opCode, r, immed
		else if (opCode == 8 || opCode == 9)
			codeR(inFile, buildSet, stringFlag);
		//Advanced Arithmetic and Logical Instructions -> MUL(20), DIV(21), TER(22), AND(23), ORR(24) //form --> opCode, rx, ry
		else if (opCode == 20 || opCode == 21 || opCode == 22 || opCode == 23 || opCode == 24)
		    codeRxRy(inFile, buildSet, stringFlag);
		 //-> NOT(25) //form --> opCode, rx
		else if (opCode == 25)
		    codeRx(inFile, buildSet, stringFlag);
		//-> ADD(26), SUB(27) //form --> opCode, rx, ry, i, ix
        else if (opCode == 26 || opCode == 26 )
            codeRRII(inFile, buildSet, stringFlag);

		instructions.push_back(buildSet);
	}

	//for testing BEGIN
	int tempTest = 0;
	list <bitset<16>>::iterator iter = instructions.begin();
	while (iter != instructions.end())
	{
		cout << "List position:: " << tempTest << ", Item:: " << *iter << endl;
		cout << "\tposition:: " << tempTest << ", size:: " << iter->size() << endl;
		iter++;
		tempTest++;
	}
	//for testing END
}
//Encodes 16 bit instruction for LDR, STR, AMR, SMR, CMP
void OS::codeRIXA(istream &inFile, bitset<16> &buildSet, bool stringFlag)
{
	/*             R
	Opcode  I  IX AC  Address
	000001  0  0  11  101100
	15  10  9  8  76  5    0
	*/
cout << "codeRIXA!" << endl;
//int temp = scrollWhiteSpace(cin);
	char delim = ',';
	//Acquire and encode R - BEGIN
	bitset<2> twoBits;
	string rCode = fileIterator(inFile, delim);
	twoBits = stoi(rCode);
	buildSet[6] = twoBits[0];
	buildSet[7] = twoBits[1];
	//Acquire and encode R - END
	cout << "HERE 1!" << endl;
	//Acquire and encode I - BEGIN
	delim = ',';
	string iCode = fileIterator(inFile, delim);
	buildSet[9] = stoi(iCode);
	//Acquire and encode I - END
	cout << "HERE 2!" << endl;
	//Acquire and encode X - BEGIN
	delim = ',';
	string xCode = fileIterator(inFile, delim);
	buildSet[8] = stoi(xCode);
	//Acquire and encode X - END
	cout << "HERE 3!" << endl;
	//Acquire and encode address BEGIN
	encodeAddress(inFile, buildSet, stringFlag);
	//Acquire and encode address END
	cout << "HERE 4!" << endl;
	//for testing BEGIN
		cout << "BUILD SET in codeRIXA: " << buildSet << endl;
	//for testing END
}
//Encodes 16 bit instruction for LDX, LDX, JE, JNE, JG, JGE, JL, JLE, JUMP //Form --> opCode i, x, address
void OS::codeIXA(istream &inFile, bitset<16> &buildSet, bool stringFlag)
{
	/*             R
	Opcode  I  IX AC  Address
	000001  0  0  11  101100
	15  10  9  8  76  5    0
	*/
	cout << "codeIXA!" << endl;
	//if (stringFlag)
	//	int temp = scrollWhiteSpace(cin);

	char delim = ',';

	//Acquire and encode I - BEGIN
	delim = ',';
	string iCode = fileIterator(inFile, delim);
	buildSet[9] = stoi(iCode);
	//Acquire and encode I - END

	//Acquire and encode X - BEGIN
	delim = ',';
	string xCode = fileIterator(inFile, delim);
	buildSet[8] = stoi(xCode);
	//Acquire and encode X - END

	//Acquire and encode address BEGIN
	encodeAddress(inFile, buildSet, stringFlag);
	//Acquire and encode address END
	//for testing BEGIN
	cout << "BUILD SET in codeIXA: " << buildSet << endl;
	//for testing END
}
void OS::codeRimmed(istream &inFile, bitset<16> &buildSet, bool stringFlag)//Form --> opCode r, immed;
{

}
void OS::codeR(istream &inFile, bitset<16> &buildSet, bool stringFlag)//Form --> opCode r;
{

}
void OS::codeRxRy(istream &inFile, bitset<16> &buildSet, bool stringFlag)//Form --> opCode rx, ry;
{

}
void OS::codeRx(istream &inFile, bitset<16> &buildSet, bool stringFlag)//Form --> opCode rx;
{

}
void OS::codeRRII(istream &inFile, bitset<16> &buildSet, bool stringFlag)//Form --> opCode, r, r, i, i;
{

}

//encodes 6 bit address from user input or file
void OS::encodeAddress(istream &inFile, bitset<16> &buildSet, bool stringFlag)
{
	//if (stringFlag)
	//	temp = scrollWhiteSpace(inFile);
	cout << "HERE 1.1 encodeAddress!" << endl;
	char delim = '\n';
	string addyCode;
	if (stringFlag)
		cin >> addyCode;
	else
		addyCode = fileIterator(inFile, delim);
	cout << "HERE 2.1 encodeAddress!" << endl;
	bitset<6> sixBits(stoi(addyCode));
cout << "addyCode:: ! " << addyCode /*<< " addyInt:: " <<  addyInt */<< " sixBits:: " << sixBits << endl;
	for (int i = 0; i < 6; i++)
		buildSet[i] = sixBits[i];
}
/*
01
LDR r, i, x, address
Load Register From Memory : r << c(EA)

02
STR r, i, x, address
Store Register To Memory : EA << c(r)

41 
LDX i, x, address
Load Index Register from Memory : X0 << c(EA)

42
STX i, x, address
Store Index Register to Memory : EA << c(X0)
*/
bitset<6> OS::streamToOpCode(istream &input)
{
cout << "streamToOpCode begin" << endl;
	char delim = ' ';
	string opCode = fileIterator(input, delim);
	bitset<6> bitOpCode;

	if (opCode == "LDR")//Form --> opCode r, i, x, address --> uses codeRIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 1;
	else if (opCode == "STR")//Form --> opCode r, i, x, address --> uses codeRIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 2;
	else if (opCode == "LDX")//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 41;
	else if (opCode == "STX")//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 42;
	//Comparison Instruction
	else if (opCode == "CMP")//Form --> opCode r, i, x, address --> uses codeRIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 17;
	//Transfer Instructions
	else if (opCode == "JE")//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 10;
	else if (opCode == "JNE")//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 11;
	else if (opCode == "JG")//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 12;
	else if (opCode == "JGE")//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 14;
	else if (opCode == "JL")//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 15;
	else if (opCode == "JLE")//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 16;
	else if (opCode == "JUMP")//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 13;
	//Basic Arithmetic and Logic Instructions
	else if (opCode == "AMR")//Form --> opCode r, i, x, address --> uses codeRIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 4;
	else if (opCode == "SMR")//Form --> opCode r, i, x, address --> uses codeRIXA(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 5;

//below has no encoder function fully defined as of yet
	else if (opCode == "AIR")//Form --> opCode, r, immed --> usus codeRimmed(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 6;
	else if (opCode == "SIR")//Form --> opCode, r, immed --> usus codeRimmed(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 7;
	else if (opCode == "DEC")//form --> opCode, r --> usus codeR(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 8;
	else if (opCode == "INC")//form --> opCode, r --> usus codeR(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 9;
	//Advanced Arithmetic and Logical Instructions
	else if (opCode == "MUL")//form --> opCode, rx, ry -->uses codeRxRy(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 20;
	else if (opCode == "DIV")//form --> opCode, rx, ry -->uses codeRxRy(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 21;
	else if (opCode == "TER")//form --> opCode, rx, ry -->uses codeRxRy(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 22;
	else if (opCode == "AND")//form --> opCode, rx, ry -->uses codeRxRy(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 23;
	else if (opCode == "ORR")//form --> opCode, rx, ry -->uses codeRxRy(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 24;
	else if (opCode == "NOT")//form --> opCode, rx -->uses codeRx(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 25;
	else if (opCode == "ADD")//form --> opCode, rx, ry, i, ix -->uses codeRRII(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 26;
	else if (opCode == "SUB")//form --> opCode, rx, ry, i, ix -->uses codeRRII(istream &inFile, bitset<16> &buildSet)
		bitOpCode = 27;
cout << "streamToOpCode end" << endl;
	return bitOpCode;
}

/*
//Scrolls through file data for processing specific fields as required
//Returns next data field as a string
string OS::fileIterator(istream &instructionFile, int skip)
{
	string newString;
	int endFlag = 0;

	for (int i = 0; i < skip; i++)
	{
		getline(instructionFile, newString, ',');
		endFlag = scrollChars(instructionFile);
	}
	return newString;
}
*/
//Scrolls through file data for processing specific fields as required
//Returns next data field as a string.
string OS::fileIterator(istream &input, char delim)
{
	string newString;
	int endFlag = 0;

	getline(input, newString, delim);
	endFlag = scrollChars(input);

	return newString;
}
//allows skipping of parenthesis and iterates through whitespace after a word that may be 
//or is expected to be the last entry in order to find next entry or eof
//used only in fileIterator(). Returns next char as int
int OS::scrollChars(istream &instructionFile)
{
	int temp = instructionFile.peek();
	//catch parenthesis here
	if (temp == '"')
	{
		do
		{
			instructionFile.ignore();
			temp = instructionFile.peek();
		} while (temp != '"');
	}
	//9 == horizontal tab
	while (temp == ' ' || temp == 9)//skip trailing white space
	{
		instructionFile.ignore();
		temp = instructionFile.peek();
	}
	return temp;
}
//iterates through whitespace after a word that may be or is expected to be the last entry
//in order to find eof. Used by UserPrompt() for user input processing (cin). Returns next char as int
//Precondition: 2nd or 3rd word of search term input
//Postcondition: cin loaded with next non-whitespace data
int OS::scrollWhiteSpace(istream &cin)
{
	int temp = cin.peek();
	//9 == horizontal tab
	while (temp == ' ' || temp == 9)
	{
		cin.ignore();
		temp = cin.peek();
	}
	return temp;
}
