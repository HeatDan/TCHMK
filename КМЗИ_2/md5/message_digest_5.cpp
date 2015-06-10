#include "md5.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ios>
using namespace std;


int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		cout << "Error!\n Usage: ./program_name inputfile"<<endl;
		return 321;
	}


	MD5 md5; //создаем объект класса MD5
	const char* filePath; //filePath будем присваивать путь к файлу, дайджест которого необходимо получить.
	ifstream infile; // тут будет храниться указатель на открытый файл
	
	filePath = argv[1];// присваиваем переменной путь к файлу
	infile.open(filePath);// открываем файл на чтение
	
	if(infile)// если файл открыт 
	{
		cout << "MD5 digest: ";
		md5.update(infile);// обновляем контекст в зависимости от входного файла
		cout << md5.toString() << endl; // тут вычисляется сам дайджест, приводится к string и выводится в консоль.
	}
	else
	{
		cout << "input file not found" << endl; // если не удалось открыть файл, выводим сообщение об этом.
		return 123;
	}
	
	return 0;
}
