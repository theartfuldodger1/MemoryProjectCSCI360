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
				menu1A();
			}
			break;
			case 2: //Add Instruction Line By Line
			{
				menu1B();//not functional yet
			}
			break;
			case 3: //Load Program to Main Memory
			{

			}
			break;
			case 4: //Display Empty Registers
			{

			}
			break;
			case 5: //Display Instruction Display with Default Values
			{

			}
			break;
			case 6: //Display Empty Memory
			{

			}
			break;
			case 7: //Help
			{

			}
			break;
			case 8: //Quit
			{
				//exit
			}
			break;
			}
	} while (param != 8);
	/*
	// UpperCase == Interrupts
	// LowerCase == SysCalls

	// A 					new process
	// D number				The hard disk #number has finished the work for one process.
	// d number file_name	The process that currently uses the CPU requests the hard disk #number. It wants to read or write file file_name.
	// m address			The process that currently uses the CPU requests a memory operation for the address address.
	// S r || i || m :: S = Snapshot of -> r = Running & ready queue || i = Using HDD & Wait queue || m = display frame table
	// t					The process that currently uses the CPU terminates. It leaves the system immediately. Make sure you release the memory used by this process.

	int param = 0;
	char input;
	//int queueLevel;

	do
	{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	failCheck(cin);

	cin >> input;
	//cout << "You entered: " << input << endl;

	if (input == 'A')// A :: new process
	param = 1;
	else if (input == 'D')// D number :: The hard disk #number has finished the work for one process.
	param = 2;
	else if (input == 'd')// d number file_name	:: The process that currently uses the CPU requests the hard disk #number. It wants to read or write file file_name.
	param = 3;
	else if (input == 'm')// m address :: The process that currently uses the CPU requests a memory operation for the address address.
	param = 4;
	else if (input == 'S')// S r || i || m :: S = Snapshot of -> r = Running & ready queue || i = Using HDD & Wait queue || m = display frame table
	param = 5;
	else if (input == 't')// t :: The process that currently uses the CPU terminates. It leaves the system immediately. Make sure you release the memory used by this process.
	param = 6;
	else if (input == 'Q')//The currently running process has spent a time quantum using the CPU. If the same process continues to use the CPU and one more Q command arrives, it means that the process has spent one more time quantum.
	param = 7;
	else if (input == '8')//Internal check of CPU process
	param = 8;
	else if (input == '9')//internal exit
	param = 9;
	else
	{
	cout << "Incorrect input:" << endl;
	param = 0;
	}

	if (param > 0 || param < 9)
	switch (param)
	{
	case 1: // Create a new Process
	{
	//DONE
	//insert into cpu queue level 1
	//create and insert FT_element
	CPU.createNewProcess(PIDCounter);
	memory_module.insertNewProcessFT_Element(PIDCounter);
	incrementPIDCounter();
	}
	break;
	case 2: // The HDD has finished the work for one process
	{
	//DONE
	int HDDNumIn;
	cin >> HDDNumIn;
	if ((HDDNumIn < 0) || (HDDNumIn >(HDDArray.getHDDQuantity() - 1)))
	{
	cout << "Incorrect input: Hard Drive number must be between 0 and "
	<< (HDDArray.getHDDQuantity() - 1) << endl;
	}
	else
	{
	if (!HDDArray.HDDQueueEmpty(HDDNumIn))
	{
	int pidIn;
	int queueNumIn;
	HDDArray.removeProcess(HDDNumIn, pidIn, queueNumIn);
	CPU.processToReady(pidIn, queueNumIn);
	}
	else
	cout << "HDD " << HDDNumIn << " Queue: Empty. No process to remove." << endl;
	}
	}
	break;
	case 3: // Process currently using the CPU requests the HDD#? to read file file_name. THREE params here
	{
	//DONE
	int HDDNumIn;
	string file_name;
	if (CPU.getCurrentPID() == -1)
	{
	cout << "CPU Queues are empty." << endl;
	cout << "No currently running process to move" << endl;
	cin >> HDDNumIn;
	cin >> file_name;
	}
	else
	{
	cin >> HDDNumIn;
	if ((HDDNumIn < 0) || (HDDNumIn >(HDDArray.getHDDQuantity() - 1)))
	{
	cout << "Incorrect input: Hard Drive number must be between 0 and "
	<< (HDDArray.getHDDQuantity() - 1) << endl;
	cin >> file_name;
	}
	else
	{
	cin >> file_name;

	int tempPID = CPU.getCurrentPID();
	int tempPIDQueue = CPU.getCurrentPIDQueue();
	HDDArray.processToHDD(HDDNumIn, tempPID, tempPIDQueue, file_name);
	CPU.moveCurrentFromCPU();
	}
	}
	}
	break;
	case 4: // m address :: The process that currently uses the CPU requests a memory operation for a specific address.
	{
	//DONE
	int pidIn;
	int pNumIn;
	pidIn = CPU.getCurrentPID();
	cin >> pNumIn;
	memory_module.insertNewFT_Element(pidIn, pNumIn);
	}
	break;
	case 5: // S r || i || m :: S = Snapshot of -> r = Running & ready queue || i = Using HDD & wait queue || m = display frame table
	{
	//DONE
	char snapshot = ' ';
	cin >> snapshot;
	if ((snapshot == 'r') || (snapshot == 'i') || (snapshot == 'm'))
	{
	if (snapshot == 'r')//DONE
	CPU.getCPUQ();
	else if (snapshot == 'i')
	HDDArray.getHDDQueue();
	else if (snapshot == 'm')//DONE
	memory_module.getFrameTableContents();
	else	//something went horribly wrong...
	cout << "Unknown input error" << endl;
	}
	else
	{
	cout << "Incorrect snapshot type input" << endl;
	param = 0;
	}
	}
	break;
	case 6: // t :: The process that currently uses the CPU terminates. It leaves the system immediately. Make sure you release the memory used by this process.
	{
	//DONE
	if (CPU.getCurrentPID() == -1)
	{
	cout << "CPU Queues are empty." << endl;
	cout << "No currently running process to move" << endl;
	}
	else
	{
	memory_module.removeFT_Element(CPU.getCurrentPID());
	CPU.terminateCPUProcess();
	}
	}
	break;
	case 7://The currently running process has spent a time quantum using the CPU. If the same process continues to use the CPU and one more Q command arrives, it means that the process has spent one more time quantum.
	{
	CPU.spentQuantum();//DONE
	}
	break;
	case 8://///FOR TESTING
	{
	cout << "case 8" << endl;
	cout << " Current running process: " << CPU.getCurrentPID();
	}
	break;
	}
	} while (param != 9);
	*/
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
	//cout.setf(ios::fixed, ios::floatfield);
	//cout.setf(ios::showpoint);
	//cout.precision(2);
	cout << right;
	cout << setw(45) << "Initialization Menu"
		<< "\n\t----------------------------------------------------"
		<< "\n\t1. Add Instruction File"
		<< "\n\t2. Add Instruction Line By Line"
		<< "\n\t3. Load Program to Main Memory"
		<< "\n\t4. Display Empty Registers"
		<< "\n\t5. Display Instruction Display with Default Values"
		<< "\n\t6. Display Empty Memory"
		<< "\n\t7. Help"
		<< "\n\t8. Quit"
		<< "\n\n\t==>> ";
}
//add instruction file from Menu1, choice 1
void OS::menu1A()
{
	/*
				 Add an Instruction File
	---------------------------------------------------
	Please ensure usage of proper case.

	=>>
	*/
	string fileIn;
	ifstream instructionFile;
	bool fileFail = 0;
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
		{
			cerr << "\n\tCould not open file\n\n";
		}
		else
			fileFail = 1;

	} while (!fileFail);
	processFile(instructionFile, MyMemory.getInstructionSet());
}
void OS::processFile(ifstream &inFile, list <bitset<16>> instructions)
{
	/*             R
	Opcode  I  IX AC  Address
	000001  0  0  11  101100
	15  10  9  8  76  5    0
	*/
	bitset<16> buildSet;
	bool firstPass = 1;
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
		opCode = opCode;
		//Acquire and encode opCode - END

		//Load/Store Instructions //Comparison Instruction -> LDR(1), STR(2), AMR(4), SMR(5), CMP(17) //Form --> opCode r, i, x, address
		if (opCode == 1 || opCode == 2 || opCode == 4 || opCode == 5 || opCode == 17 )
			codeRIXA(inFile, buildSet);
		//Load/Store Instructions //Transfer Instructions -> LDX(41), STX(42), JE(10), JNE(11), JG(12), JGE(14), JL(15), JLE(16), JUMP(13) //Form --> opCode i, x, address
		else if (opCode == 41 || opCode == 42 || opCode == 10 || opCode ==11 || opCode == 12 || opCode == 13 || opCode == 14 || opCode == 15 || opCode == 16)
			codeIXA(inFile, buildSet);
		//Basic Arithmetic and Logic Instructions -> AIR(6), SIR(7) //Form --> opCode, r, immed
		else if (opCode == 6 || opCode == 7)
			codeRimmed(inFile, buildSet);
		//-> DEC(8), INC(9) //Form --> opCode, r, immed
		else if (opCode == 8 || opCode == 9)
			codeR(inFile, buildSet);
		//Advanced Arithmetic and Logical Instructions -> MUL(20), DIV(21), TER(22), AND(23), ORR(24) //form --> opCode, rx, ry
		else if (opCode == 20 || opCode == 21 || opCode == 22 || opCode == 23 || opCode == 24)
		    codeRxRx(inFile, buildSet);
		 //-> NOT(25) //form --> opCode, rx
		else if (opCode == 25)
		    codeRx(inFile, buildSet);
		//-> ADD(26), SUB(27) //form --> opCode, rx, ry, i, ix
        else if (opCode == 26 || opCode == 26 )
            codeRRII(inFile, buildSet);

		instructions.push_back(buildSet);
	}

	//for testing BEGIN
	int temp = 0;
	list <bitset<16>>::iterator iter = instructions.begin();
	while (iter != instructions.end())
	{
		cout << "List position:: " << temp << ", Item:: " << *iter << endl;
		cout << "\tposition:: " << temp << ", size:: " << iter->size() << endl;
		iter++;
		temp++;
	}
	//for testing END
}
//Encodes 16 bit instruction for LDR, STR, AMR, SMR, CMP
void OS::codeRIXA(istream &inFile, bitset<16> &buildSet)
{
	/*             R
	Opcode  I  IX AC  Address
	000001  0  0  11  101100
	15  10  9  8  76  5    0
	*/
cout << "codeRIXA!" << endl;
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
	buildSet[9] = stoi(iCode);//twoBits[0];
	//Acquire and encode I - END

	//Acquire and encode X - BEGIN
	delim = ',';
	string xCode = fileIterator(inFile, delim);
	buildSet[8] = stoi(xCode);//twoBits[0];
	//Acquire and encode X - END

	//Acquire and encode address BEGIN
	encodeAddress(inFile, buildSet);
	//Acquire and encode address END
}
//Encodes 16 bit instruction for LDX, LDX, JE, JNE, JG, JGE, JL, JLE, JUMP //Form --> opCode i, x, address
void OS::codeIXA(istream &inFile, bitset<16> &buildSet)
{
	/*             R
	Opcode  I  IX AC  Address
	000001  0  0  11  101100
	15  10  9  8  76  5    0
	*/
	cout << "codeIXA!" << endl;\
	char delim = ',';

	//Acquire and encode I - BEGIN
	delim = ',';
	string iCode = fileIterator(inFile, delim);
	buildSet[9] = stoi(iCode);//twoBits[0];
	//Acquire and encode I - END

	//Acquire and encode X - BEGIN
	delim = ',';
	string xCode = fileIterator(inFile, delim);
	buildSet[8] = stoi(xCode);//twoBits[0];
	//Acquire and encode X - END

	//Acquire and encode address BEGIN
	encodeAddress(inFile, buildSet);
	//Acquire and encode address END
}
//encodes 6 bit address from user input or file
void OS::encodeAddress(istream &inFile, bitset<16> &buildSet)
{
	char delim = '\n';
	string addyCode = fileIterator(inFile, delim);
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
/**********************************************************************************************************************/
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

	return bitOpCode;
}

// add individual instructions from Menu1, choice 2
void OS::menu1B()
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
		<< "\n\tEnter Q if you are finished."
		<< "\n\n\t=>>" << endl;
	string instructionIn;
	cin >> instructionIn;

}
//simulation menu, follows addition of instructions (menu1A or 1B). Choice 1 returns the user to Menu 1 (Initialization Menu)
void OS::menu2()
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
	cout << right;
	cout << setw(45) << "Initialization Menu" << endl;
	unsigned short int param = 0;
	do
	{
		cout << "\n";
		initializationMenu();
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
			case 1:
			{

			}
			break;
			case 2:
			{
			}
			break;
			case 3:
			{

			}
			break;
			case 4:
			{

			}
			break;
			case 5:
			{

			}
			break;
			case 6:
			{

			}
			break;
			case 7:
			{

			}
			break;
			case 8:
			{

			}
			break;
			}
	} while (param != 8);
}
//follows loading of program into main memory - choice 3 from menu2/simulation menu
//if user selects choice 1, return to Menu 1, initializatinMenu()
void OS::menu2A()
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
	cout << right;
	cout << setw(45) << "Initialization Menu" << endl;
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
