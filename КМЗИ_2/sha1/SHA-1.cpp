// SHA-1.cpp: определяет точку входа для консольного приложения.
//
#include "sha1.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iomanip>



int main(int argc, char **argv)
{

if(argc !=2 )
{
	cout << "error!!"<<endl;
	cout <<"usage: ./program_name inputfile.txt"<<endl;
	return 123;
}

ifstream ifst;

const char* filename = argv[1];

ifst.open(filename);

if(!ifst)
{
	cout << "error! file not found!"<<endl;
	return 312;
}

int size = 0;

ifst.seekg(0,std::ios::end);
size = ifst.tellg();
ifst.seekg(0,std::ios::beg);


char* str;

str = new char[size+1];

int i= 0 ;

ifst.getline(str,size+1);

ifst.close();


cout << str <<endl;


SHA1((const byte *) str, strlen(str));

return 0;
}





