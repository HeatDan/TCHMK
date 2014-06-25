#include "longNumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>
using std::ifstream;
using std::ofstream;

#define DIV_BY_ZERO 1

longNumber::longNumber()
{// конструктор по умолчанию обнуляет число
	this->size = 1;
	this->znak = 0;
	this->elements = new unsigned char[1];
	this->elements[0] = 0;
}

longNumber::longNumber(const char* string)
{// преобразовнаие строки string в число
// считаем, что строка - запись в 10-чном виде какого-либо числа
// поэтому надо перейти от основания 10 к основанию 256
// для этого необходимо каждую цифру в числе умножть на 10 ^ i,
// где i - номер разряда этой цифры
	
	int strLen = strlen(string);
	int strSign = 0;
	if (string[0] == '-')
	{
		strSign = 1;
		strLen--;
	}

	longNumber result; // число, в котором "будем собирать результат перевода"

	longNumber Stepen10 = 1; // 10 ^ i
	// цикл для i от конца строки (самого младшего разряда)
	// до самого старшего разряда (учитывая знак)
	for (int i = strLen + strSign - 1; i >= strSign; i--)
	{
		int rI = string[i] - '0'; // очередной разряд числа
		result = result + Stepen10 * rI;
		Stepen10 = Stepen10 * 10;
	}
	result.znak = strSign;

	this->size = 0;
	*this = result; // записываем в this полученное число
}

longNumber::longNumber(const longNumber &right)
{// конструктор копирования
	this->size = right.size;
	this->elements = new unsigned char[this->size];
	this->znak = right.znak;
	memcpy(elements, right.elements, this->size * sizeof(unsigned char));
	return;
}

longNumber::longNumber(int value)
{// конструктор из целого числа
	this->elements = new unsigned char[11]();
	this->size = 0;
	this->znak = 0;
	if (value < 0)
	{
		this->znak = 1;
		value = -value;
	}
	do
	{
		this->size++;
		this->elements[this->size - 1] = value % 256;
		value = value / 256;
	} while (value > 0);

	this->DelZer();
}

longNumber::~longNumber()
{// дуструктор
	delete[] elements;
}

char* longNumber::VivodStroki()
{// вывод числа
// необходимо в строку записать остатки от деления числа на 10, 
// пока число не станет равным нулю.
	
	longNumber temp = *this; // число, которое будем делить на 10
	temp.znak = 0;
	
	std::vector<char> tmpStr; // в этот вектор будем записывать полученную строку


	while (temp != (int)0)
	{
		longNumber ostatok;
		temp = Delenie(temp, 10, ostatok); // делим число на 10 и находим остаток
		char ost = ostatok[0] + '0'; // остаток от деления на 10 находится в 0-вой позиции в ostatok
		tmpStr.push_back(ost);
	}

	// если число было отрицательным, запишем знак
	if (this->znak)
		tmpStr.push_back('-');

	// теперь в tmpStr находится строка, представляющая число
	// но записанная задом-наперёд.
	// исправим это

	int strSize = tmpStr.size();
	char* string = new char[strSize + 1]();

	for (int i = 0; i < tmpStr.size(); i++)
	{
		string[strSize - i - 1] = tmpStr[i];
	}

	return string;
}


bool longNumber::ReadFile(const char* filename)
{
	ifstream Text_file(filename);
	if (Text_file.fail())
		return false;

	// узнаем размер файла
	Text_file.seekg(0, std::ios::end);
	int SizeOfFile = Text_file.tellg();
	Text_file.seekg(0, std::ios::beg);

	char* string = new char[SizeOfFile + 1]();
	Text_file >> string;
	Text_file.close();

	*this = longNumber(string);
	delete[] string;
	return true;
}

bool longNumber::SaveFile(const char* filename)
{
	ofstream Result_file(filename);
	if (Result_file.fail())
		return false;

	char* string = this->VivodStroki();
	Result_file << string;
	delete[] string;
	Result_file.close();

	return true;
}

bool longNumber::SaveBinFile(const char* filename)
{// т. к. основание 256 - считаем бинарный файл просто массивом коэффициентов

	ofstream outBinFile(filename, std::ios::binary);
	if (outBinFile.fail())
		return false;

	// просто записываем коэффициенты в бинарный файл
	outBinFile.write((char*) this->elements, this->size); 

	outBinFile.close();
	return true;
}

bool longNumber::ReadBinFile(const char* filename)
{
	ifstream inBinFile(filename, std::ios::binary);
	if (inBinFile.fail())
		return false;

	inBinFile.seekg(0, std::ios::end);
	int SizeOfFile = inBinFile.tellg();
	inBinFile.seekg(0, std::ios::beg);

	delete[] this->elements;
	this->elements = new unsigned char[SizeOfFile];
	this->size = SizeOfFile;
	this->znak = 0;

	// считываем содержимое файла
	inBinFile.read((char*)this->elements, SizeOfFile);
	inBinFile.close();

	return true;
}


void longNumber::SetSize(int newSize)
{	// изменяет размер числа, при этом обнуляя его. 
	if (this->size)
		delete[] this->elements;
	this->size = newSize;
	this->znak = 0;
	this->elements = new unsigned char[this->size]();
}

void longNumber::DelZer()
{// убирает из числа 0 в старших разрядах
	while ((size - 1) && elements && elements[size - 1] == 0)
		this->size--;

	if (this->size == 1 && elements[0] == 0)
		this->znak = 0;
}

int longNumber::Sravnenie(const longNumber& B)
{
	// функция возвращает
	// 0 - если числа равны,
	// >0 - если this больше
	// <0 - если this меньше
	int thisSign = 1;
	if (this->znak == 1)
		thisSign = -1;

	if (this->znak != B.znak)
		return thisSign;

	if (this->size > B.size)
		return thisSign;

	if (this->size < B.size)
		return -thisSign;

	int i = this->size - 1;

	while (this->elements[i] == B[i] && i > 0)
	{
		i--;
	}
	return ( (int) this->elements[i] - (int) B[i]) * thisSign;
}

void longNumber::Sdvig(int s)
{// сдвигает число на s разрядов влево
	// то есть, по сути, это умножение на 10^s

	unsigned char* newElements = new unsigned char[this->size + s]();
	for (int i = 0; i < this->size; i++)
	{
		newElements[i + s] = this->elements[i];
	}

	delete[] this->elements;
	this->elements = newElements;
	this->size += s;
	this->DelZer();
}


longNumber longNumber::Sum_Sub(const longNumber& left, const longNumber& right) const
{// сложение и вычитание "столбиком"
	longNumber A = left, B = right; // в А будет большее по модулю число, в B - меньшее.
	A.znak = 0;
	B.znak = 0;
	if (A > B)
	{
		A.znak = left.znak;
		B.znak = right.znak;
	}
	else
	{
		A = right;
		B = left;
	}

	if (A.znak == B.znak)
	{// если числа одного знака, то просто складываем их и выставляем нужный знак

		longNumber result;
		result.SetSize(A.size + 1);

		int carry = 0;

		for (int i = 0; i < A.size; i++)
		{
			int tmp = A[i] + carry;
			if (i < B.size)
				tmp += B[i];

			result[i] = tmp % 256;
			carry = tmp / 256;
		}

		result[A.size] = carry;
		result.znak = A.znak;
		result.DelZer();
		return result;
	}
	else
	{// отнимаем одно от другого и выставляем нужный знак
		longNumber result;
		result.SetSize(A.size);

		int carry = 0;
		for (int i = 0; i < A.size; i++)
		{
			int tmp = A[i] - carry;
			if (i < B.size)
				tmp -= B[i];

			carry = 0;
			if (tmp < 0)
			{
				carry = 1;
				tmp += 256;
			}
			result[i] = tmp;
		}

		result.znak = A.znak;
		result.DelZer();
		return result;
	}
}

longNumber longNumber::Mult(const longNumber A, const longNumber B) const
{// простое умножение "столбиком"
	longNumber result;
	result.SetSize(A.size + B.size);
	int carry = 0;
	for (int i = 0; i < B.size; i++)
	{
		carry = 0;
		for (int j = 0; j < A.size; j++)
		{
			int tmp = (int) B[i] * (int) A[j] + (int) carry + (int) result[i + j];
			carry = tmp / 256;
			result[i + j] = tmp % 256;
		}
		result[i + A.size] = carry;
	}

	result.znak = (A.znak != B.znak);
	result.DelZer();
	return result;
}

longNumber longNumber::Delenie(const longNumber& A, const longNumber& B, longNumber &ostatok) const
{// возвращает целую часть от деления, в ostatok - остаток
	ostatok = A;
	ostatok.znak = 0;

	longNumber divider = B;
	divider.znak = 0;

	if (divider == longNumber((int)0))
	{
		throw DIV_BY_ZERO;
	}

	if (ostatok < divider)
	{
		ostatok = A;
		return longNumber((int)0);
	}

	longNumber result;
	result.SetSize(A.size - B.size + 1);

	for (int i = A.size - B.size + 1; i; i--)
	{
		int MaxGran = 256;
		int MinGran = 0;
		int Gran = MaxGran;

		// цикл - подбор бинарным поиском числа Gran
		while (MaxGran - MinGran > 1)
		{
			Gran = (MaxGran + MinGran) / 2;

			// получаем tmp = Gran * divider * 256^i;
			longNumber tmp = divider * Gran;
			tmp.Sdvig(i - 1);	// сдвигаем число на (i - 1) разрядов влево
									// то есть, по сути, это умножение на 256^(i - 1)
			
			if (tmp > ostatok)
				MaxGran = Gran;
			else
				MinGran = Gran;
		}
		longNumber tmp = divider * MinGran;
		tmp.Sdvig(i - 1); // умножение на 256 ^ (i - 1)
		ostatok = ostatok - tmp;
		result[i - 1] = MinGran;
	}

	result.znak = (A.znak != B.znak);
	ostatok.znak = (A.znak != B.znak);
	ostatok.DelZer();
	result.DelZer();

	return result;
}


longNumber Stepen(const longNumber& A, const longNumber& B, longNumber& modul)
{// возведение A в степень B по модулю modul
	if (modul <= (int)0)
		return A ^ B;

	longNumber base = A % modul;
	longNumber result = 1;

	for (longNumber i = B; i > (int)0; i = i - 1)
		result = (result * base) % modul;

	return result;
}

unsigned char & longNumber::operator[](int i)
{
	if (i < 0)
		return this->elements[this->size + i];
	return this->elements[i];
}

unsigned char longNumber::operator[](int i) const
{
	if (i < 0)
		return this->elements[this->size + i];
	return this->elements[i];
}


longNumber& longNumber::operator=(const longNumber& rhv)
{
	if (this->size)
		delete[] this->elements;

	this->size = rhv.size;
	this->elements = new unsigned char[size];
	this->znak = rhv.znak;
	memcpy(elements, rhv.elements, size);
	return *this;
}

longNumber longNumber::operator-() const
{// унарный минус
	longNumber result = *this;
	result.znak = !result.znak;
	return result;
}

longNumber longNumber::operator^(const longNumber& right) const
{// возведение *this в степень right
	longNumber result = 1;
	longNumber base = *this;
	for (longNumber i = right; i > (int)0; i = i - 1)
		result = result * base;
	return result;
}

longNumber longNumber::operator+(const longNumber& right) const
{
	return Sum_Sub(*this, right);
}

longNumber longNumber::operator-(const longNumber& right) const
{
	return *this + (-right);
}

longNumber longNumber::operator*(const longNumber& right) const
{
	return Mult(*this, right);
}

longNumber longNumber::operator/(const longNumber& right) const
{
	longNumber rem;
	return Delenie(*this, right, rem);
}

longNumber longNumber::operator%(const longNumber& right) const
{
	longNumber rem;
	Delenie(*this, right, rem);
	return rem;
}

bool longNumber::operator>(const longNumber& B)
{
	return this->Sravnenie(B) > 0;
}

bool longNumber::operator>=(const longNumber& B)
{
	return this->Sravnenie(B) >= 0;
}

bool longNumber::operator<(const longNumber& B)
{
	return this->Sravnenie(B) < 0;
}

bool longNumber::operator<=(const longNumber& B)
{
	return this->Sravnenie(B) <= 0;
}

bool longNumber::operator==(const longNumber& B)
{
	return this->Sravnenie(B) == 0;
}

bool longNumber::operator!=(const longNumber& B)
{
	return this->Sravnenie(B) != 0;
}

longNumber longNumber::operator+(const int& right) const
{
	return Sum_Sub(*this, (longNumber) right);
}

longNumber longNumber::operator-(const int& right) const
{
	return *this + (longNumber) (-right);
}

longNumber longNumber::operator*(const int& right) const
{
	return Mult(*this, (longNumber)  right);
}

longNumber longNumber::operator/(const int& right) const
{
	longNumber rem;
	return Delenie(*this, (longNumber)  right, rem);
}

longNumber longNumber::operator%(const int& right) const
{
	longNumber rem;
	Delenie(*this, (longNumber)  right, rem);
	return rem;
}

bool longNumber::operator>(const int& B)
{
	return this->Sravnenie( (longNumber) B) > 0;
}

bool longNumber::operator>=(const int& B)
{
	return this->Sravnenie( (longNumber) B) >= 0;
}

bool longNumber::operator<(const int& B)
{
	return this->Sravnenie( (longNumber) B) < 0;
}

bool longNumber::operator<=(const int& B)
{
	return this->Sravnenie( (longNumber) B) <= 0;
}

bool longNumber::operator==(const int& B)
{
	return this->Sravnenie( (longNumber) B) == 0;
}

bool longNumber::operator!=(const int& B)
{
	return this->Sravnenie( (longNumber) B) != 0;
}

char* longNumber::__repr__()
{
	return VivodStroki();
}

char* longNumber::__str__()
{
	return VivodStroki();
}