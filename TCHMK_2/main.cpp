// ТЧМК.cpp: определяет точку входа для консольного приложения.
//
#include <string.h>
#include <iostream>
#include "longNumber.h"
using std::cout;

using namespace std;
void printUsage()
{
	cout << "Usage: " << endl;
	cout << "TCHMK_1 <A filelame> <operation> <B filelame> <resultult filename> [-b] [<modul filename>]" << endl << endl;
	cout << "Parameters:" << endl;
	cout << "  operations:" << endl;
	cout << "    \"+\" - addition" << endl;
	cout << "    \"-\" - subtraction" << endl;
	cout << "    \"*\" - Mult" << endl;
	cout << "    \"/\" - Delenie" << endl;
	cout << "    \"%\" - taking the ostatok" << endl;
	cout << "    \"^\" - involution (Stepen)" << endl;
	cout << "  -b for operations with binary files" << endl;
}

bool process(longNumber A, longNumber B, longNumber modul, char operation, longNumber& result)
{
	if (modul < (int)0)
	{
		cout << "Negative modul!" << endl;
		return false;
	}

	if (operation == '^')
	{
		result = Stepen(A, B, modul);
		return true;
	}

	if (modul > (int)0)
	{
		A = A % modul;
		B = B % modul;
	}

	switch (operation)
	{
	case '+':
		result = A + B;
		break;

	case '-':
		result = A - B;
		break;

	case '*':
		result = A * B;
		break;

	case '/':
		try
		{
			result = A / B;
		}
		catch (int err)
		{
			cout << "Delenie by zero" << endl;
			return false;
		}
		break;

	case '%':
		try
		{
			result = A % B;
		}
		catch (int err)
		{
			cout << "Delenie by zero" << endl;
			return false;
		}
		break;

	default:
		cout << "Wrong operation." << endl;
		printUsage();
		return false;
	}

	if (modul > (int)0)
	{
		result = result % modul;
		while (result < (int)0)
			result = result + modul;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		cout << "Too few arguments passed." << endl;        
		printUsage();
		return -1;
	}

	if (argc > 7)
	{
		cout << "Too many arguments passed." << endl;
		printUsage();
		return -1;
	}

	if (strlen(argv[2]) > 1)
	{
		cout << "Wrong operation." << endl;
		printUsage();
		return -1;
	}

	char* fileA = argv[1];
	char operation = argv[2][0];
	char* fileB = argv[3];
	char* fileresult = argv[4];
	bool binary = false;
	char* fileMod = NULL;

	if (argc == 6)
	{
		if (!strcmp(argv[5], "-b"))
			binary = true;
		else
			fileMod = argv[5];
	}

	if (argc == 7)
	{
		binary = true;
		fileMod = argv[6];
	}

	longNumber A, B, modul = (int)0;

	if (binary)
	{
		A.WriteBinFile(fileA);
		B.WriteBinFile(fileB);
		if (fileMod)
			modul.WriteBinFile(fileMod);
	}
	else
	{
		A.WriteFile(fileA);
		B.WriteFile(fileB);
		if (fileMod)
			modul.WriteFile(fileMod);
	}

	longNumber result;
	if (!process(A, B, modul, operation, result))
		return -1;

	if (binary)
		result.SaveBinFile(fileresult);
	else
		result.SaveFile(fileresult);

	return 0;
}
