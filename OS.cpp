/*
Author: Cordell Hurst, Alex BOrtoc, Johnny Zhu
Course: CSCI 360, Computer Architecture III
Instructor: Xiaojie Zhang
Assignment: Software Simulator/Multi-Level Memory Memory Hierarchy
This program...
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
	4. Display Instructions
	5. Display Empty Memory
	6. Help
	7. Quit

	==>>
	*/
	unsigned short int param = 0;
	bool check = 0;
	do
	{
		cout << "\n";
		param = 0;
		if (param < 0 || param > 8)
		{
			cout << "\n\tIncorrect input:" << endl;
			param = 0;
		}
		if (param == 0)
		{
			if (check == 0)
				initializationMenu();
			cin >> param;
		}

		check = 0;
		if (cin.fail())
		{
			//cout << "check!:" << endl;
			check = 1;
			cin.clear();
			cin.ignore(255, '\n');
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
				MyCache.printRegisters();
			}
			break;
			case 4: //Display Instructions
			{
				printInstructions();//no stepping
			}
			break;
			case 5: //Display Empty Memory
			{
				MyMemory.printMemory();
			}
			break;
			case 6: //Help
			{
				//call help file needed
				cout << "\t\nHelp File incomplete..." << endl;
				bitset<16> tt("0000010011010111");
				LDR(tt);
				bitset<16> aa = MyCache.get_GeneralPurposeRegisters_GPRs(3);
				STR(aa);
				//bitset<16> dd("1010010000001001");
				//LDX(dd);
				//bitset<16> xx("1010100000110010");
				//STX(xx);
				bitset<16> comp("0100010000000000");
				CMP(comp);
				cout << "ZF: " << MyCache.get_ZF() << " CF: " << MyCache.get_CF() << " SF: " << MyCache.get_SF() << endl;
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
	/*
	//for testing BEGIN
	int temp = 0;
	vector <bitset<16>>::iterator iter = instructionSet_OS.begin();
	while (iter != instructionSet_OS.end())
	{
		cout << "vector position:: " << temp << ", Item:: " << *iter << endl;
		cout << "\tposition:: " << temp << ", size:: " << iter->size() << endl;
		iter++;
		temp++;
	}
	//for testing END
	*/
}
//catches failed input cast and resets istream
void OS::failCheck(istream &cin)
{
	if (cin.fail())
	{
		cout << "Incorrect input:" << endl;
		cin.clear();
		cin.ignore(255, '\n');
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
	5. Display Instructions
	6. Display Empty Memory
	7. Help
	8. Quit

	==>>
	*/

	cout << right;
 	cout << setw(45) << setfill(' ') << "Initialization Menu"
		<< "\n\t----------------------------------------------------"
		<< "\n\t1. Add Instruction File"
		<< "\n\t2. Add Instruction Line By Line"
		<< "\n\t3. Display Empty Registers"
		<< "\n\t4. Display Instructions"
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

	processFile(instructionFile, instructionSet_OS);
	unsigned short int paramOut = menu2();
	return paramOut;
}
// add individual instructions from Menu1, choice 2
unsigned short int OS::menu1B()
{
	/*
	Add Individual Instructions
	---------------------------------------------------
	Enter Instructions in the following form: 
	LDR 3, 1, 1, 54 or LDR 3,1,1,54
	Press Enter after each instruction.
	Enter Q if you are finished.

	=>>
	*/
	cin.ignore(255, '\n');
	cout << right;
	cout << setw(45) << "Add Individual Instructions"
		<< "\n\t---------------------------------------------------"
		<< "\n\tEnter Instructions in the following form: "
		<< "\n\tLDR 3, 1, 1, 54 or LDX 1,0,54 as appropriate"
		<< "\n\tPress Enter after each instruction."
		<< "\n\tEnter Q if you are finished."
		<< "\n\n\t=>> ";
	string instructionIn;

	int peek = cin.peek();
//cout << "PEEK IND INST: " << peek << endl;
	//do
	while (peek != 81 && peek != 113)
	{
		peek = cin.peek();
//cout << "PEEK2 IND INST: " << peek << endl;
	if(peek != 81 && peek != 113)//(s[0] == 'Q' || s[0] == 'q')	
	{ 
		processFile(cin);
		cout << "\n\t=>> ";
	}
		
		//string s;
		//cin >> s;
		else
		{
			unsigned short int paramOut = menu2();	//allows user to quit after indiv input;
			return paramOut;
		}
//		peek = cin.peek();
//		cout << "PEEK3 IND INST: " << peek << endl;
	}//while (instructionIn != "81" && instructionIn != "113");

	unsigned short int paramOut = 0;//menu2();
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
	string inFile;

//	cout <<"IN Proc File" <<endl;
	//while (peek != EOF && peek != 10)
	{
		buildSet.reset();

		//Acquire and encode opCode - BEGIN
		bitset<6> opCode = streamToOpCode(cin);
		int j = 10;
		for (int i = 0; i < 6; i++)
		{
//cout << "in opcode loop" << endl;
			buildSet[j] = opCode[i];
			j++;
		}
//cout << "opCode: " << opCode << endl;
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

		instructionSet_OS.push_back(buildSet);
//cout << "pushed processFile!" << endl;
		cin.clear();
		cin.ignore(255, '\n');
//cout << "Cleared processFile" << endl;
	}

//cout << "second Cleared processFile" << endl;
/*
	//for testing BEGIN
	int tempTest = 0;
	vector <bitset<16>>::iterator iter = instructionSet_OS.begin();
	while (iter != instructionSet_OS.end())
	{
		cout << "vector position:: " << tempTest << ", Item:: " << *iter << endl;
		cout << "\tposition:: " << tempTest << ", size:: " << iter->size() << endl;
		iter++;
		tempTest++;
	}
	//for testing END
	cout << "passed testing processFile" << endl;
*/
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
	5.	Display Instructions
	6. 	Display Empty Memory
	7.	Help
	8. 	Quit

	==>>
	*/
	unsigned short int paramOut = 0;
	unsigned short int param = 0;
//cout << "MENU2: " << param << endl;
//cout << "Stuck 1?" << endl;

		int temp2 = scrollWhiteSpace(cin);
//		int peek;
//cout << "Stuck 2?" << endl;
	bool check = 0;
	int first = 0;
	do
	{
	/*
		//cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		failCheck(cin);

		peek = cin.peek();
		cout << "PEEK:: " << peek << " temp2::  " << temp2 << endl;
		//failCheck(cin);
		//char cleaner[256];
		//cin.getline(cleaner, 256);
		param = 0;
		//cin.clear();
		cout << "\n";
		cout << right;
		cout << setw(40) << setfill(' ') << "Simulation Menu"
			<< "\n\t---------------------------------------------------"
			<< "\n\t1. Clear All Data and Start Over"
			<< "\n\t2. Add Instruction Line to End of Queue"
			<< "\n\t3. Load Program into Main Memory"
			<< "\n\t4. Display Empty Registers"
			<< "\n\t5. Display Instructions"
			<< "\n\t6. Display Empty Memory"
			<< "\n\t7. Help"
			<< "\n\t8. Quit" 
			<< "\n\n\t=>> ";
//		initializationMenu();
//cout << "MENU2.1: " << param << endl;
		cin >> param;
		cout << "POST: " << param << endl;
	//	int temp2 = scrollWhiteSpace(cin);
		peek = cin.peek();
		cout << "PEEK 2:: " << peek << " temp2.2::  " << temp2 << endl;
		
		//cin.ignore(255, '\n');cin.clear();
		//cin.clear();
		//cin.ignore(255, '\n');
		//char cleaner[256];
		//cin.fail();
		//cin.getline(cleaner, 256);
		
		//failCheck(cin);
		//cout << "You entered: " << input << endl;

		if (param <= 0 || param > 8)
		{
			cout << "\n\tIncorrect input:" << endl;
			param = 0;
		}
		*/
		
		//if (first == 0)
		{
			if (cin.fail())
			{
//cout << "check!:" << endl;
				check = 1;
				cin.clear();
				cin.ignore(255, '\n');
			}
			//first = 1;
		}cin.clear();
		cout << "\n";
		//initializationMenu();
		//cin >> param;

		param = 0;
//cout << "param TOP: " << param << endl;
		
		if (param < 0 || param > 8)
		{
			cout << "\n\tIncorrect input:" << endl;
			param = 0;
		}
		if (param == 0)
		{
			if (check == 0)
			{
				cout << right;
				cout << setw(40) << setfill(' ') << "Simulation Menu"
					<< "\n\t---------------------------------------------------"
					<< "\n\t1. Clear All Data and Start Over"
					<< "\n\t2. Add Instruction Line to End of Queue"
					<< "\n\t3. Load Program into Main Memory"
					<< "\n\t4. Display Empty Registers"
					<< "\n\t5. Display Instructions"
					<< "\n\t6. Display Empty Memory"
					<< "\n\t7. Help"
					<< "\n\t8. Quit"
					<< "\n\n\t=>> ";
			}
			cin >> param;
		}
		check = 0;
		if (cin.fail())
		{
			check = 1;
			cin.clear();
			cin.ignore(255, '\n');
		}
		else //if (param > 0 || param < 9)
			switch (param)
			{
				case 1://1. Clear All Data and Start Over ////Return to Initialization Menu
				{
					clearAllData();
					param = 8;
				}
				break;
				case 2://2. Add Instruction Line to End of Queue
				{
						menu1B();
				}
				break;
				case 3://3. Load Program into Main Memory
				{
					loadInstructionsIntoMain();
					paramOut = menu2A();
					if(paramOut == 7)
						param = 8;
				}
				break;
				case 4://4. Display Empty Registers
				{
					MyCache.printRegisters();
				}
				break;
				case 5://5. Display Instructions
				{
					printInstructions();//no stepping
				}
				break;
				case 6://6. Display Empty Memory
				{
					MyMemory.printMemory();
				}
				break;
				case 7://7. Help
				{
					//call help file needed
					cout << "\t\nHelp File incomplete..." << endl;
				}
				break;
				case 8://8. Quit
				{
					paramOut = 7;
					param = 8;
				}
				break;
			}
//cout << "POST - POST@@@@: " << param << endl;
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
	bool check = 0;
	do
	{
		if (cin.fail())
		{
			check = 1;
			cin.clear();
			cin.ignore(255, '\n');
		}
		cin.clear();
		cout << "\n";

		param = 0;
//cout << "param TOP: " << param << endl;

		if (param < 0 || param > 8)
		{
			cout << "param: " << param << endl;
			cout << "\n\tIncorrect input:" << endl;
			cout << "param: " << param << endl;
			param = 0;
		}
		if (param == 0)
		{
			if (check == 0)
			{
				cout << setw(40) << setfill(' ') << "Simulation Menu"
					<< "\n\t---------------------------------------------------"
					<< "\n\t1. Clear All Data and Start Over"
					<< "\n\t2. Add Instruction Line to End of Queue"

					<< "\n\t3. Display Registers"
					<< "\n\t4. Display Instructions"
					<< "\n\t5. Display Memory"
					<< "\n\t6. Help"
					<< "\n\t7. Quit"
					<< "\n\n\t=>> ";
			}
			cin >> param;
		}
		check = 0;
		if (cin.fail())
		{
//cout << "check!:" << endl;
			check = 1;
			cin.clear();
			cin.ignore(255, '\n');
		}
		if (param > 0 || param < 9)
			switch (param)
			{
			case 1://1. Clear All Data and Start Over ////Return to Initialization Menu
			{
				clearAllData();
				param = 7;
			}
			break;
			case 2://2. Add Instruction Line to End of Queue
			{
				param = menu1B();
			}
			break;
			case 3://3. Display Registers
			{
				MyCache.printRegisters();	
			}
			break;
			case 4://4. Display Instructions WITH stepping
			{
				stepInstructions();
				//printInstructions();//no stepping
			}
			break;
			case 5://5. Display Memory
			{
				MyMemory.printMemory();
			}
			break;
			case 6://6. Help
			{
				//call help file needed
				cout << "\t\nHelp File incomplete..." << endl;
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

void OS::processFile(ifstream &inFile, vector <bitset<16>> &instructions)
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
        else if (opCode == 26 || opCode == 27 )
            codeRRII(inFile, buildSet, stringFlag);

		instructions.push_back(buildSet);
	}
/*
	//for testing BEGIN
	int tempTest = 0;
	vector <bitset<16>>::iterator iter = instructions.begin();
	while (iter != instructions.end())
	{
		cout << "vector position:: " << tempTest << ", Item:: " << *iter << endl;
		cout << "\tposition:: " << tempTest << ", size:: " << iter->size() << endl;
		iter++;
		tempTest++;
	}
	//for testing END
*/
}
//Encodes 16 bit instruction for LDR, STR, AMR, SMR, CMP
void OS::codeRIXA(istream &inFile, bitset<16> &buildSet, bool stringFlag)
{
	/*             R
	Opcode  I  IX AC  Address
	000001  0  0  11  101100
	15  10  9  8  76  5    0
	*/
//cout << "codeRIXA!" << endl;
	char delim = ',';
	//Acquire and encode R - BEGIN
	bitset<2> twoBits;
	string rCode = fileIterator(inFile, delim);
	twoBits = stoi(rCode);
	buildSet[6] = twoBits[0];
	buildSet[7] = twoBits[1];
	//Acquire and encode R - END

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
//cout << "BUILD SET in codeRIXA: " << buildSet << endl;
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
//cout << "codeIXA!" << endl;
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
//cout << "BUILD SET in codeIXA: " << buildSet << endl;
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
//cout << "HERE 1.1 encodeAddress!" << endl;
	char delim = '\n';
	string addyCode;
	if (stringFlag)
		cin >> addyCode;
	else
		addyCode = fileIterator(inFile, delim);
//cout << "HERE 2.1 encodeAddress!" << endl;
	bitset<6> sixBits(stoi(addyCode));
//cout << "addyCode:: ! " << addyCode /*<< " addyInt:: " <<  addyInt */<< " sixBits:: " << sixBits << endl;
	for (int i = 0; i < 6; i++)
		buildSet[i] = sixBits[i];
}
//accepts a bitset<16> instruction. The instruction's effective address is calculated based on values of I and IX
//A new bitset<16> is returned with the effective address
bitset<16> OS::effectiveAddress_EA(bitset<16> & instructionIn)
{
	/*             R
	Opcode  I  IX AC  Address
	000001  0  0  11  101100
	15  10  9  8  76  5    0
	*/
	bitset<16> address;
	bool IX = instructionIn[8];
	bool I = instructionIn[9];
	bitset<16> effectiveAddress_EA;

	//Acquire and encode address - BEGIN
	//address  = streamToOpCode(inFile);
	//int j = 10;
	for (int i = 0; i < 6; i++)
	{
		address[i] = instructionIn[i];
		//j++;
	}
	// Acquire and encode address - END
	if (I == 0)
	{
		if (IX == 0) 
			effectiveAddress_EA = address;
		if (IX == 1)
			effectiveAddress_EA = MyCache.get_IndexRegister_X0().to_ulong() + address.to_ulong();
	}
	if (I == 1)
	{
		if (IX == 0)
			effectiveAddress_EA = address;
		if (IX == 1)
			effectiveAddress_EA = MyCache.get_IndexRegister_X0().to_ulong() + address.to_ulong();
	}
	return effectiveAddress_EA;
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
//cout << "streamToOpCode begin" << endl;
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
//cout << "streamToOpCode end" << endl;
	return bitOpCode;
}

string OS::opCodeToString(bitset<6>&opCode)
{
	string opCodeString;
	if (opCode == 1)//Form --> opCode r, i, x, address --> uses codeRIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "LDR";
	else if (opCode == 2)//Form --> opCode r, i, x, address --> uses codeRIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "STR";
	else if (opCode == 41)//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "LDX";
	else if (opCode == 42)//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "STX";
	//Comparison Instruction
	else if (opCode == 17)//Form --> opCode r, i, x, address --> uses codeRIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "CMP";
	//Transfer Instructions
	else if (opCode == 10)//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "JE";
	else if (opCode == 11)//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "JNE";
	else if (opCode == 12)//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "JG";
	else if (opCode == 14)//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "JGE";
	else if (opCode == 15)//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "JL";
	else if (opCode == 16)//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "JLE";
	else if (opCode == 13)//Form --> opCode i, x, address --> uses codeIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "JUMP";
	//Basic Arithmetic and Logic Instructions
	else if (opCode == 4)//Form --> opCode r, i, x, address --> uses codeRIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "AMR";
	else if (opCode == 5)//Form --> opCode r, i, x, address --> uses codeRIXA(istream &inFile, bitset<16> &buildSet)
		opCodeString = "SMR";

	//below has no encoder function fully defined as of yet
	else if (opCode == 6)//Form --> opCode, r, immed --> usus codeRimmed(istream &inFile, bitset<16> &buildSet)
		opCodeString = "AIR";
	else if (opCode == 7)//Form --> opCode, r, immed --> usus codeRimmed(istream &inFile, bitset<16> &buildSet)
		opCodeString = "SIR";
	else if (opCode == 8)//form --> opCode, r --> usus codeR(istream &inFile, bitset<16> &buildSet)
		opCodeString = "DEC";
	else if (opCode == 9)//form --> opCode, r --> usus codeR(istream &inFile, bitset<16> &buildSet)
		opCodeString = "INC";
	//Advanced Arithmetic and Logical Instructions
	else if (opCode == 20)//form --> opCode, rx, ry -->uses codeRxRy(istream &inFile, bitset<16> &buildSet)
		opCodeString = "MUL";
	else if (opCode == 21)//form --> opCode, rx, ry -->uses codeRxRy(istream &inFile, bitset<16> &buildSet)
		opCodeString = "DIV";
	else if (opCode == 22)//form --> opCode, rx, ry -->uses codeRxRy(istream &inFile, bitset<16> &buildSet)
		opCodeString = "TER";
	else if (opCode == 23)//form --> opCode, rx, ry -->uses codeRxRy(istream &inFile, bitset<16> &buildSet)
		opCodeString = "AND";
	else if (opCode == 24)//form --> opCode, rx, ry -->uses codeRxRy(istream &inFile, bitset<16> &buildSet)
		opCodeString = "ORR";
	else if (opCode == 25)//form --> opCode, rx -->uses codeRx(istream &inFile, bitset<16> &buildSet)
		opCodeString = "NOT";
	else if (opCode == 26)//form --> opCode, rx, ry, i, ix -->uses codeRRII(istream &inFile, bitset<16> &buildSet)
		opCodeString = "ADD";
	else if (opCode == 27)//form --> opCode, rx, ry, i, ix -->uses codeRRII(istream &inFile, bitset<16> &buildSet)
		opCodeString = "SUB";

	return opCodeString;
	//cout << opCodeString;
}

void OS::loadInstructionsIntoMain()
{
	if (instructionSet_OS.empty())
		cout << "Instruction Set is empty."
		<< "\nPlease add instructions before attempting to load to main memory" << endl;
	else
	{
		vector<bitset<16>>::iterator iterInstSet = instructionSet_OS.begin();
		while (iterInstSet != instructionSet_OS.end())
		{
			MyMemory.insertInstruction(*iterInstSet, effectiveAddress_EA(*iterInstSet));
			iterInstSet++;
		}
	}
//cout << "In OS::loadInstructionIntoMain()" << endl;
}
//when isntructions are not yet loaded
void OS::printInstructions()
{
//This function is NOT TO STEP because it is for before instructions are loaded to MM
/*
							 Instructions
		------------------------------------------------------
		0 PC ==>> LDR  R0, 0, 0, 63   000000  0  0  00  000000
		1         STR  R1, 0, 0, 5    000000  0  0  00  000000
		------------------------------------------------------
		     R.Run	     S.Step       Q.Menu    	H.Help
*/
	/*             R
	Opcode  I  IX AC  Address
	000001  0  0  11  101100
	15  10  9  8  76  5    0
	*/
	bitset<6> opCode;
	bitset<2> reg;
	bitset<6> addy;
	vector<bitset<16>>::iterator iSetIter = instructionSet_OS.begin();
	bitset<16> instruction;
	string opCodeString;
	char input;
	do
	{
		
		cout << right;
		cout << setw(40) << "Instructions"
			<< "\n\t\t----------------------------------";
		if (instructionSet_OS.empty())
		{
			cout << "\n";
			//cout << right;
			cout << setw(45) << "Instructions not loaded" << endl;
			bitset<1> OneBitZeroed = 0;
			cout << "\t\t" << setw(4) << setfill(' ') << "1" << "       " << "N/A"
				<< " R" << reg.to_ulong() << ", " << OneBitZeroed << ", "
				<< OneBitZeroed << ", " << addy;
		}
		else
		{
			int count = 0;
			while (iSetIter != instructionSet_OS.end())
			{
				instruction = *iSetIter;
				int z = 0;
				for (int i = 10; i < 16; i++)
				{
					opCode[z] = instruction[i];
					z++;
				}
				z = 0;
				for (int i = 6; i < 8; i++)
				{
					reg[z] = instruction[i];
					z++;
				}
				z = 0;
				for (int i = 0; i < 6; i++)
				{
					addy[z] = instruction[i];
					z++;
				}
				cout << "\n\t\t" << setw(4) << setfill(' ') << count << "       " << opCodeToString(opCode)
					<< " R" << reg.to_ulong() << ", " << instruction[9] << ", " 
					<< instruction[8] << ", " << addy;
				count++;
				iSetIter++;
			}
		}
		cout << "\n\t\t----------------------------------"
			<< "\n\t" << setw(21) << setfill(' ') << "Q. Menu" 
			<< setw(15) << setfill(' ') << "H. Help"
			<< "\n\n\t\t==>> ";

		cin >> input;
		cin.ignore(255, '\n');
		failCheck(cin);

		//call help file needed
		if (input == 'H' || input == 'h')
			cout << "\t\nHelp File incomplete..." << endl;

	} while (input != 'Q' && input != 'q');
}
//instructions already loaded in main memory. this function can step or run through the instructions
void OS::stepInstructions()
{
	/*
						 Instructions
	------------------------------------------------------
	0 PC ==>> LDR  R0, 0, 0, 63   000000  0  0  00  000000
	1         STR  R1, 0, 0, 5    000000  0  0  00  000000
	------------------------------------------------------
		R.Run	     S.Step       Q.Menu    	H.Help
	*/
	/*             R
	Opcode  I  IX AC  Address
	000001  0  0  11  101100
	15  10  9  8  76  5    0
	*/
	bitset<6> opCode;
	bitset<2> reg;
	bitset<6> addy;
	bitset<16> addyPC;
	//vector <bitset<16>> instructionSet_OS = instructionSet_OS;//MyMemory.getInstructionSet();
	vector<bitset<16>>::iterator iSetIter;
	vector<bitset<16>>::iterator itExe = instructionSet_OS.begin();
	bitset<16> instruction;
	bitset<16> instructionPC;
	string opCodeString;
	char input;
	bool runFlag = 0;
	bool firstPassFlag = 0;
	unsigned int count = 0;

	do
	{	
		iSetIter = instructionSet_OS.begin();
		if (iSetIter != instructionSet_OS.end())//(count < instructionSet_OS.size())
			for (unsigned int i = 0; i < count; i++)
				itExe++;
		firstPassFlag = 0;

		cout << "\n";
		cout << right;
		cout << setw(40) << "Instructions"
			<< "\n\t\t----------------------------------";
		
		while (iSetIter != instructionSet_OS.end())
		{
			instruction = *iSetIter;
			int z = 0;
			for (int i = 10; i < 16; i++)
			{
				opCode[z] = instruction[i];
				z++;
			}
			z = 0;
			for (int i = 6; i < 8; i++)
			{
				reg[z] = instruction[i];
				z++;
			}
			z = 0;
			
			for (int i = 0; i < 6; i++)
			{
				addy[z] = instruction[i];
				z++;
			}
			

			/*
			MyCache.set_ProgramCounter(addyPC);
			int zPC = 0;
			instructionPC = *itExe;
			for (int i = 0; i < 6; i++)
			{
				addyPC[zPC] = instructionPC[i];
				zPC++;
			}
			*/
			//cout << "addyPC: " << addyPC << endl;
			//bitset<6> PC = MyCache.get_ProgramCounter_PC();
			if(MyCache.get_ProgramCounter_PC().to_ulong() == addy.to_ulong() && firstPassFlag == 0)
			{
				cout << "\n\t\t" << setw(4) << setfill(' ') << count << "  PC==>" << opCodeToString(opCode)
					<< " R" << reg.to_ulong() << ", " << instruction[9] << ", "
					<< instruction[8] << ", " << addy; 
				firstPassFlag = 1;
			}

			else
			{
				cout << "\n\t\t" << setw(4) << setfill(' ') << count << "       " << opCodeToString(opCode)
					<< " R" << reg.to_ulong() << ", " << instruction[9] << ", "
					<< instruction[8] << ", " << addy;
			}
			count++;
			iSetIter++;
		}

		cout << "\n\t\t----------------------------------"
			<< "\n\t" << setw(13) << setfill(' ') << "R. Run" << setw(10) << setfill(' ')
			<< setw(10) << setfill(' ') << "S. Step" << setw(10) << setfill(' ') << "Q. Menu"
			<< setw(10) << setfill(' ') << "H. Help"
			<< "\n\n\t\t==>> ";
		
		if (runFlag != 1)
		{
			cin >> input;
			cin.ignore(255, '\n');
			failCheck(cin);
			if(input == 'R' || input == 'r')
				runFlag = 1;
		}
		if (input == 'R' || input == 'r' || input == 'S' || input == 's')
			if (itExe != instructionSet_OS.end()) 
			{
				executeInstruction(*itExe);

				count++;
				itExe++;
			}
		//call help file needed
		if (input == 'H' || input == 'h')
			cout << "\t\nHelp File incomplete..." << endl;

	} while (input != 'Q' && input != 'q');
}

void OS::instructionDisplaySwitch(bitset<16> &instructionIn)
{
	int j = 0;
	bitset<6> opCode;
	for (int i = 10; i < 16; i++)
	{
		opCode[j] = instructionIn[i];
		j++;
	}
	//Load/Store Instructions //Comparison Instruction -> LDR(1), STR(2), AMR(4), SMR(5), CMP(17) //Form --> opCode r, i, x, address
	if (opCode == 1 || opCode == 2 || opCode == 4 || opCode == 5 || opCode == 17)
		printCodeRIXA(instructionIn);
	//Load/Store Instructions //Transfer Instructions -> LDX(41), STX(42), JE(10), JNE(11), JG(12), JGE(14), JL(15), JLE(16), JUMP(13) //Form --> opCode i, x, address
	else if (opCode == 41 || opCode == 42 || opCode == 10 || opCode == 11 || opCode == 12 || opCode == 13 || opCode == 14 || opCode == 15 || opCode == 16)
		printCodeIXA(instructionIn);
	//Basic Arithmetic and Logic Instructions -> AIR(6), SIR(7) //Form --> opCode, r, immed
	else if (opCode == 6 || opCode == 7)
		printCodeRimmed(instructionIn);
	//-> DEC(8), INC(9) //Form --> opCode, r, immed
	else if (opCode == 8 || opCode == 9)
		printCodeR(instructionIn);
	//Advanced Arithmetic and Logical Instructions -> MUL(20), DIV(21), TER(22), AND(23), ORR(24) //form --> opCode, rx, ry
	else if (opCode == 20 || opCode == 21 || opCode == 22 || opCode == 23 || opCode == 24)
		printCodeRxRy(instructionIn);
	//-> NOT(25) //form --> opCode, rx
	else if (opCode == 25)
		printCodeRx(instructionIn);
	//-> ADD(26), SUB(27) //form --> opCode, rx, ry, i, ix
	else if (opCode == 26 || opCode == 27)
		printCodeRRII(instructionIn);
}
//for instruction display
void OS::printCodeRIXA(bitset<16> &instructionIn/*, int count*/)//for instruction display
{
/*
	if (MyCache.get_ProgramCounter_PC().to_ulong() == addy.to_ulong() && firstPassFlag == 0)
	{
		cout << "\n\t\t" << setw(4) << setfill(' ') << count << "  PC==>" << opCodeToString(opCode)
			<< " R" << reg.to_ulong() << ", " << instructionIn[9] << ", "
			<< instruction[8] << ", " << addy;
		firstPassFlag = 1;
	}

	else
	{
		cout << "\n\t\t" << setw(4) << setfill(' ') << count << "       " << opCodeToString(opCode)
			<< " R" << reg.to_ulong() << ", " << instruction[9] << ", "
			<< instruction[8] << ", " << addy;
	}
*/
}
//for instruction display
void OS::printCodeIXA(bitset<16> &instructionIn)
{

}
//for instruction display
void OS::printCodeRimmed(bitset<16> &instructionIn)
{

}
//for instruction display
void OS::printCodeR(bitset<16> &instructionIn)
{

}
//for instruction display
void OS::printCodeRxRy(bitset<16> &instructionIn)
{

}
//for instruction display
void OS::printCodeRx(bitset<16> &instructionIn)
{

}
//for instruction display
void OS::printCodeRRII(bitset<16> &instructionIn)
{

}

void OS::executeInstruction(bitset<16> &instructionIn)
{
	bitset<6> opCode;
	int a = 0;

	for (int i = 10; i < 16; i++)
	{
		opCode[a] = instructionIn[i];
		a++;	
	}

	if (opCode == 1)		//LDR
		LDR(instructionIn);
	else if (opCode == 2)	//STR
		STR(instructionIn);
	else if (opCode == 41)	//LDX
		LDX(instructionIn);
	else if (opCode == 42)	//STX
		STX(instructionIn);
	/*
	else if (opCode == 10)	//JE
		JE(instructionIn);
	else if (opCode == 11)	//JNE
		JNE(instructionIn);
	else if (opCode == 12)	//JG
		JG(instructionIn);
	else if (opCode == 13)	//JUMP
		JUMP(instructionIn);
	else if (opCode == 14)	//JGE
		JGE(instructionIn);
	else if (opCode == 15)	//JL
		JL(instructionIn);
	else if (opCode == 16)	//JLE
		JLE(instructionIn);
	*/
	else if (opCode == 17)	//CMP
		CMP(instructionIn);
	//else if (opCode == 18)	

	//else if (opCode == 19)
	/*
	else if (opCode == 4)	//AMR
		AMR(instructionIn);
	else if (opCode == 5)	// SMR
		SMR(instructionIn);
	else if (opCode == 6)	//AIR
		AIR(instructionIn);
	else if (opCode == 7)	//SIR
		SIR(instructionIn);
	else if (opCode == 8)	//DEC
		DEC(instructionIn);
	else if (opCode == 9)	//INC
		INC(instructionIn);
	else if (opCode == 20)	//MUL
		MUL(instructionIn);
	else if (opCode == 21)	//DIV 
		DIV(instructionIn);
	else if (opCode == 22)	//TER 
		TER(instructionIn);
	else if (opCode == 23)	//AND 
		AND(instructionIn);
	else if (opCode == 24)	//ORR
		ORR(instructionIn);
	else if (opCode == 25)	//NOT
		NOT(instructionIn);
	else if (opCode == 26)	//ADD 
		ADD(instructionIn);
	else if (opCode == 27)	//SUB
		SUB(instructionIn);
	*/
}

void OS::clearAllData()
{
	MyCache.reset_AllRegisters();//resets all bitsets to 0's
	instructionSet_OS.clear();//removes all elements leaving the container with a size of 0
	MyMemory.clearMemory();//removes all elements leaving the container with a size of 0
}
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


//////////////
/*Adds 2 bitsets. Helper function.*/
bitset<16> addBitSets(std::bitset<16> a, std::bitset<16> b) //adds bitsets
{
	std::bitset<16> const m("1");
	std::bitset<16> result;
	for (unsigned int i = 0; i < result.size(); ++i) {
		std::bitset<16> const diff(((a >> i)&m).to_ullong() + ((b >> i)&m).to_ullong() + (result >> i).to_ullong());
		result ^= (diff ^ (result >> i)) << i;
	}
	return result;
}
//////////////////////////////////////////////////////////////////IS EA SUPPOSED TO ONLY BE 6 BITS?
/*Load Register to memory. Takes a 16 bitset and extracts necessary bits to calculate the
effective address. Bus class is used to temporarily hold address and data.*/
void OS::LDR(bitset<16> temp)
{
	bitset<2> reg; //holds bits that identify the register
	bitset<16> mar;
	reg[1] = temp[7];
	reg[0] = temp[6];
	unsigned long gpr_num = reg.to_ulong();
	bitset<16> effectiveAddress_EA; //indexed addressing requires 16, i believe it is okay to simply bufffer the unused bits with 0s
	bitset<16> content; //holds values that are being transferred
	if (temp[9] == 0)
	{
		if (temp[8] == 0)
		{
			for (int i = 5; i >= 0; i--)
			{
				effectiveAddress_EA[i] = temp[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			mar = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = SystemBus.loadData(effective_address);
			MyCache.set_GeneralPurposeRegisters_GPRs(gpr_num, content);
			MyCache.set_MemoryAddressRegister_MAR(mar);
			MyCache.set_MemoryBufferRegister_MBR(content);
		}
		else if (temp[8] == 1)
		{
			bitset<16> index = MyCache.get_IndexRegister_X0();
			bitset<16> address;
			for (int i = 5; i >= 0; i--)
			{
				address[i] = temp[i];
			}
			address = addBitSets(address, index);
			for (int i = 15; i >= 0; i--)
			{
				effectiveAddress_EA[i] = address[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			mar = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = SystemBus.loadData(effective_address);
			MyCache.set_GeneralPurposeRegisters_GPRs(gpr_num, content);
			MyCache.set_MemoryAddressRegister_MAR(mar);
			MyCache.set_MemoryBufferRegister_MBR(content);
		}
	}
	else if (temp[9] == 1)
	{
		if (temp[8] == 0)
		{
			for (int i = 5; i >= 0; i--)
			{
				effectiveAddress_EA[i] = temp[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			mar = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = SystemBus.loadData(effective_address);
			MyCache.set_GeneralPurposeRegisters_GPRs(gpr_num, content);
			MyCache.set_MemoryAddressRegister_MAR(mar);
			MyCache.set_MemoryBufferRegister_MBR(content);
		}
		else if (temp[8] == 1)
		{
			bitset<16> index = MyCache.get_IndexRegister_X0();
			bitset<16> address;
			for (int i = 5; i >= 0; i--)
			{
				address[i] = temp[i];
			}
			address = addBitSets(address, index);
			for (int i = 15; i >= 0; i--)
			{
				effectiveAddress_EA[i] = address[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			mar = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = SystemBus.loadData(effective_address);
			MyCache.set_GeneralPurposeRegisters_GPRs(gpr_num, content);
			MyCache.set_MemoryAddressRegister_MAR(mar);
			MyCache.set_MemoryBufferRegister_MBR(content);
		}
	}
}

/*Store Register to memory. Takes a 16 bitset and extracts necessary bits to calculate the
effective address. Bus class is used to temporarily hold address and data.*/
void OS::STR(bitset<16> setIn)
{
	bitset<2> reg; //holds bits that identify the register
	reg[1] = setIn[7];
	reg[0] = setIn[6];
	unsigned long gpr_num = reg.to_ulong();
	bitset<16> effectiveAddress_EA; //indexed addressing requires 16, i believe it is okay to simply buffer the unused bits with 0s
	bitset<16> content; //holds values that are being transferred
	if (setIn[9] == 0)
	{
		if (setIn[8] == 0)
		{
			for (int i = 5; i >= 0; i--)
			{
				effectiveAddress_EA[i] = setIn[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = MyCache.get_GeneralPurposeRegisters_GPRs(gpr_num);
			MyMemory.setMemoryElement(effective_address, content);
		}
		else if (setIn[8] == 1)
		{
			bitset<16> index = MyCache.get_IndexRegister_X0();
			bitset<16> address;
			for (int i = 5; i >= 0; i--)
			{
				address[i] = setIn[i];
			}
			address = addBitSets(address, index);
			for (int i = 15; i >= 0; i--)
			{
				effectiveAddress_EA[i] = address[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = MyCache.get_GeneralPurposeRegisters_GPRs(gpr_num);
			MyMemory.setMemoryElement(effective_address, content);
		}
	}
	else if (setIn[9] == 1)
	{
		if (setIn[8] == 0)
		{
			for (int i = 5; i >= 0; i--)
			{
				effectiveAddress_EA[i] = setIn[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = MyCache.get_GeneralPurposeRegisters_GPRs(gpr_num);
			MyMemory.setMemoryElement(effective_address, content);
		}
		else if (setIn[8] == 1)
		{
			bitset<16> index = MyCache.get_IndexRegister_X0();
			bitset<16> address;
			for (int i = 5; i >= 0; i--)
			{
				address[i] = setIn[i];
			}
			address = addBitSets(address, index);
			for (int i = 15; i >= 0; i--)
			{
				effectiveAddress_EA[i] = address[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = MyCache.get_GeneralPurposeRegisters_GPRs(gpr_num);
			MyMemory.setMemoryElement(effective_address, content);
		}
	}
}

/*Load Index Register from memory. Takes a 16 bitset and extracts necessary bits to calculate the
effective address. Bus class is used to temporarily hold address and data.*/
void OS::LDX(bitset<16> temp)
{
	bitset<16> mar;
	bitset<16> effectiveAddress_EA; //indexed addressing requires 16, i believe it is okay to simply bufffer the unused bits with 0s
	bitset<16> content; //holds values that are being transferred
	if (temp[9] == 0)
	{
		if (temp[8] == 0)
		{
			for (int i = 5; i >= 0; i--)
			{
				effectiveAddress_EA[i] = temp[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			mar = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = SystemBus.loadData(effective_address);
			MyCache.set_IndexRegister_X0(content);
			MyCache.set_MemoryAddressRegister_MAR(mar);
			MyCache.set_MemoryBufferRegister_MBR(content);
		}
	}
	else if (temp[8] == 1)
	{
		bitset<16> index = MyCache.get_IndexRegister_X0();
		bitset<16> address;
		for (int i = 5; i >= 0; i--)
		{
			address[i] = temp[i];
		}
		address = addBitSets(address, index);
		for (int i = 15; i >= 0; i--)
		{
			effectiveAddress_EA[i] = address[i];
		}
		unsigned long effective_address = effectiveAddress_EA.to_ulong();
		mar = effectiveAddress_EA.to_ulong();
		SystemBus.loadAddress(effective_address);
		content = SystemBus.loadData(effective_address);
		MyCache.set_IndexRegister_X0(content);
		MyCache.set_MemoryAddressRegister_MAR(mar);
		MyCache.set_MemoryBufferRegister_MBR(content);
	}
	else if (temp[9] == 1)
	{
		if (temp[8] == 0)
		{
			for (int i = 5; i >= 0; i--)
			{
				effectiveAddress_EA[i] = temp[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			mar = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = SystemBus.loadData(effective_address);
			MyCache.set_IndexRegister_X0(content);
			MyCache.set_MemoryAddressRegister_MAR(mar);
			MyCache.set_MemoryBufferRegister_MBR(content);
		}
		else if (temp[8] == 1)
		{
			bitset<16> index = MyCache.get_IndexRegister_X0();
			bitset<16> address;
			for (int i = 5; i >= 0; i--)
			{
				address[i] = temp[i];
			}
			address = addBitSets(address, index);
			for (int i = 15; i >= 0; i--)
			{
				effectiveAddress_EA[i] = address[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			mar = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = SystemBus.loadData(effective_address);
			MyCache.set_IndexRegister_X0(content);
			MyCache.set_MemoryAddressRegister_MAR(mar);
			MyCache.set_MemoryBufferRegister_MBR(content);
		}
	}
}

/*Store Index Register to memory. Takes a 16 bitset and extracts necessary bits to calculate the
effective address. Bus class is used to temporarily hold address and data.*/
void OS::STX(bitset<16> setIn)
{
	bitset<16> effectiveAddress_EA; //indexed addressing requires 16, i believe it is okay to simply bufffer the unused bits with 0s
	bitset<16> content; //holds values that are being transferred
	if (setIn[9] == 0)
	{
		if (setIn[8] == 0)
		{
			for (int i = 5; i >= 0; i--)
			{
				effectiveAddress_EA[i] = setIn[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = MyCache.get_IndexRegister_X0();
			MyMemory.setMemoryElement(effective_address, content);
		}
		else if (setIn[8] == 1)
		{
			bitset<16> index = MyCache.get_IndexRegister_X0();
			bitset<16> address;
			for (int i = 5; i >= 0; i--)
			{
				address[i] = setIn[i];
			}
			address = addBitSets(address, index);
			for (int i = 15; i >= 0; i--)
			{
				effectiveAddress_EA[i] = address[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = MyCache.get_IndexRegister_X0();
			MyMemory.setMemoryElement(effective_address, content);
		}
	}
	else if (setIn[9] == 1)
	{
		if (setIn[8] == 0)
		{
			for (int i = 5; i >= 0; i--)
			{
				effectiveAddress_EA[i] = setIn[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = MyCache.get_IndexRegister_X0();
			MyMemory.setMemoryElement(effective_address, content);
		}
		else if (setIn[8] == 1)
		{
			bitset<16> index = MyCache.get_IndexRegister_X0();
			bitset<16> address;
			for (int i = 5; i >= 0; i--)
			{
				address[i] = setIn[i];
			}
			address = addBitSets(address, index);
			for (int i = 15; i >= 0; i--)
			{
				effectiveAddress_EA[i] = address[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content = MyCache.get_IndexRegister_X0();
			MyMemory.setMemoryElement(effective_address, content);
		}
	}
}

//Compares the values that are held in the indicated memory address and register and sets ZF, CF and SF
//flags to their appropriate values
void OS::CMP(bitset<16> setIn)
{
	bitset<2> reg; //holds bits that identify the register
	bitset<16> mar;
	reg[1] = setIn[7];
	reg[0] = setIn[6];
	unsigned long gpr_num = reg.to_ulong();
	bitset<16> effectiveAddress_EA; //indexed addressing requires 16, i believe it is okay to simply bufffer the unused bits with 0s
	bitset<16> content_mem; //holds mem value
	bitset<16> content_reg; //holds reg value
	unsigned long mem_cont; //converted bitset memory value for comparison
	unsigned long reg_cont; //converted bitset register value for comparison
	if (setIn[9] == 0)
	{
		if (setIn[8] == 0)
		{
			for (int i = 5; i >= 0; i--)
			{
				effectiveAddress_EA[i] = setIn[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			mar = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content_mem = SystemBus.loadData(effective_address);
			content_reg = MyCache.get_GeneralPurposeRegisters_GPRs(gpr_num);
			mem_cont = content_mem.to_ulong();
			reg_cont = content_reg.to_ulong();
			if (mem_cont == reg_cont)
			{
				MyCache.set_ZF(1);
				MyCache.set_CF(0);
				MyCache.set_SF(0);
				cout << "Equal" << endl;
			}
			else if (reg_cont < mem_cont)
			{
				MyCache.set_ZF(0);
				MyCache.set_CF(1);
				MyCache.set_SF(1);
				cout << "Reg is smaller" << endl;
			}
			else if (reg_cont > mem_cont)
			{
				MyCache.set_ZF(0);
				MyCache.set_CF(0);
				MyCache.set_SF(0);
				cout << "Reg is greaAter" << endl;
			}
			MyCache.set_MemoryAddressRegister_MAR(mar);
			MyCache.set_MemoryBufferRegister_MBR(content_mem); 
		}
		else if (setIn[8] == 1)
		{
			bitset<16> index = MyCache.get_IndexRegister_X0();
			bitset<16> address;
			for (int i = 5; i >= 0; i--)
			{
				address[i] = setIn[i];
			}
			address = addBitSets(address, index);
			for (int i = 15; i >= 0; i--)
			{
				effectiveAddress_EA[i] = address[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			mar = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content_mem = SystemBus.loadData(effective_address);
			content_reg = MyCache.get_GeneralPurposeRegisters_GPRs(gpr_num);
			mem_cont = content_mem.to_ulong();
			reg_cont = content_reg.to_ulong();
			if (mem_cont == reg_cont)
			{
				MyCache.set_ZF(1);
				MyCache.set_CF(0);
				MyCache.set_SF(0);
				cout << "Equal" << endl;
			}
			else if (reg_cont < mem_cont)
			{
				MyCache.set_ZF(0);
				MyCache.set_CF(1);
				MyCache.set_SF(1);
				cout << "Reg is smaller" << endl;
			}
			else if (reg_cont > mem_cont)
			{
				MyCache.set_ZF(0);
				MyCache.set_CF(0);
				MyCache.set_SF(0);
				cout << "Reg is greater" << endl;
			}
			MyCache.set_MemoryAddressRegister_MAR(mar);
			MyCache.set_MemoryBufferRegister_MBR(content_mem);
		}
	}
	else if (setIn[9] == 1)
	{
		if (setIn[8] == 0)
		{
			for (int i = 5; i >= 0; i--)
			{
				effectiveAddress_EA[i] = setIn[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			mar = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content_mem = SystemBus.loadData(effective_address);
			content_reg = MyCache.get_GeneralPurposeRegisters_GPRs(gpr_num);
			mem_cont = content_mem.to_ulong();
			reg_cont = content_reg.to_ulong();
			if (mem_cont == reg_cont)
			{
				MyCache.set_ZF(1);
				MyCache.set_CF(0);
				MyCache.set_SF(0);
				cout << "Equal" << endl;
			}
			else if (reg_cont < mem_cont)
			{
				MyCache.set_ZF(0);
				MyCache.set_CF(1);
				MyCache.set_SF(1);
				cout << "Reg is smaller" << endl;
			}
			else if (reg_cont > mem_cont)
			{
				MyCache.set_ZF(0);
				MyCache.set_CF(0);
				MyCache.set_SF(0);
				cout << "Reg is greater" << endl;
			}
			MyCache.set_MemoryAddressRegister_MAR(mar);
			MyCache.set_MemoryBufferRegister_MBR(content_mem);
		}
		else if (setIn[8] == 1)
		{
			bitset<16> index = MyCache.get_IndexRegister_X0();
			bitset<16> address;
			for (int i = 5; i >= 0; i--)
			{
				address[i] = setIn[i];
			}
			address = addBitSets(address, index);
			for (int i = 15; i >= 0; i--)
			{
				effectiveAddress_EA[i] = address[i];
			}
			unsigned long effective_address = effectiveAddress_EA.to_ulong();
			mar = effectiveAddress_EA.to_ulong();
			SystemBus.loadAddress(effective_address);
			content_mem = SystemBus.loadData(effective_address);
			content_reg = MyCache.get_GeneralPurposeRegisters_GPRs(gpr_num);
			mem_cont = content_mem.to_ulong();
			reg_cont = content_reg.to_ulong();
			if (mem_cont == reg_cont)
			{
				MyCache.set_ZF(1);
				MyCache.set_CF(0);
				MyCache.set_SF(0);
				cout << "Equal" << endl;
			}
			else if (reg_cont < mem_cont)
			{
				MyCache.set_ZF(0);
				MyCache.set_CF(1);
				MyCache.set_SF(1);
				cout << "Reg is smaller" << endl;
			}
			else if (reg_cont > mem_cont)
			{
				MyCache.set_ZF(0);
				MyCache.set_CF(0);
				MyCache.set_SF(0);
				cout << "Reg is greater" << endl;
			}
			MyCache.set_MemoryAddressRegister_MAR(mar);
			MyCache.set_MemoryBufferRegister_MBR(content_mem);
		}
	}
}