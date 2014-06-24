#include "longNumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>
using std::ifstream;
using std::ofstream;

#define Delenie_BY_ZERO 1

longNumber::longNumber()
{// ����������� �� ��������� �������� �����
	this->size = 1;
	this->znak = 0;
	this->elements = new unsigned char[1];
	this->elements[0] = 0;
}

longNumber::longNumber(const char* string)
{// �������������� ������ string � �����
	// �������, ��� ������ - ������ � 10-���� ���� ������-���� �����
	// ������� ���� ������� �� ��������� 10 � ��������� 256
	// ��� ����� ���������� ������ ����� � ����� ������� �� 10 ^ i,
	// ��� i - ����� ������� ���� �����

	int strLen = strlen(string);
	int strSign = 0;
	if (string[0] == '-')
	{
		strSign = 1;
		strLen--;
	}

	longNumber result; // �����, � ������� "����� �������� ��������� ��������"

	longNumber Stepen10 = 1; // 10 ^ i
	// ���� ��� i �� ����� ������ (������ �������� �������)
	// �� ������ �������� ������� (�������� ����)
	for (int i = strLen + strSign - 1; i >= strSign; i--)
	{
		int rI = string[i] - '0'; // ��������� ������ �����
		result = result + Stepen10 * rI;
		Stepen10 = Stepen10 * 10;
	}
	result.znak = strSign;

	this->size = 0;
	*this = result; // ���������� � this ���������� �����
}

longNumber::longNumber(const longNumber &right)
{// ����������� �����������
	this->size = right.size;
	this->elements = new unsigned char[this->size];
	this->znak = right.znak;
	memcpy(elements, right.elements, this->size * sizeof(unsigned char));
	return;
}

longNumber::longNumber(int value)
{// ����������� �� ������ �����
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
{// ����������
	delete[] elements;
}

char* longNumber::VivodStroki()
{// ����� �����
	// ���������� � ������ �������� ������� �� ������� ����� �� 10, 
	// ���� ����� �� ������ ������ ����.

	longNumber temp = *this; // �����, ������� ����� ������ �� 10
	temp.znak = 0;

	std::vector<char> tmpStr; // � ���� ������ ����� ���������� ���������� ������


	while (temp != (int)0)
	{
		longNumber ostatok;
		temp = Delenie(temp, 10, ostatok); // ����� ����� �� 10 � ������� �������
		char ost = ostatok[0] + '0'; // ������� �� ������� �� 10 ��������� � 0-��� ������� � ostatok
		tmpStr.push_back(ost);
	}

	// ���� ����� ���� �������������, ������� ����
	if (this->znak)
		tmpStr.push_back('-');

	// ������ � tmpStr ��������� ������, �������������� �����
	// �� ���������� �����-������.
	// �������� ���

	int strSize = tmpStr.size();
	char* string = new char[strSize + 1]();

	for (int i = 0; i < tmpStr.size(); i++)
	{
		string[strSize - i - 1] = tmpStr[i];
	}

	return string;
}


bool longNumber::WriteFile(const char* filename)                  //������ �� ����������
{
	ifstream Text_file(filename);
	if (Text_file.fail())
		return false;

	// ������ ������ �����
	Text_file.seekg(0, std::ios::end);
	int SizeOfFile = Text_file.tellg();
	Text_file.seekg(0, std::ios::beg);

	char* string = new char[SizeOfFile + 1]();
	Text_file >> string;
	Text_file.close();

	*this = longNumber(string);                                   //����������� ����� �� ������
	delete[] string;
	return true;
}

bool longNumber::SaveFile(const char* filename)                 //���������� � ���������
{
	ofstream resultult_file(filename);
	if (resultult_file.fail())
		return false;

	char* string = this->VivodStroki();
	resultult_file << string;
	delete[] string;
	resultult_file.close();

	return true;
}

bool longNumber::SaveBinFile(const char* filename)
{// �. �. ��������� 256 - ������� �������� ���� ������ �������� �������������

	ofstream outBinFile(filename, std::ios::binary);             //�������� ������ ������
	if (outBinFile.fail())
		return false;

	// ������ ���������� ������������ � �������� ����
	outBinFile.write((char*) this->elements, this->size);

	outBinFile.close();
	return true;
}

bool longNumber::WriteBinFile(const char* filename)     //������ � ���������
{
	ifstream inBinFile(filename, std::ios::binary);            //��������
	if (inBinFile.fail())                                      //�������� �� ��������
		return false;

	inBinFile.seekg(0, std::ios::end);                         //��������� �� �����
	int SizeOfFile = inBinFile.tellg();                        //������
	inBinFile.seekg(0, std::ios::beg);                         //������� �� ������ �����

	delete[] this->elements;
	this->elements = new unsigned char[SizeOfFile];            //��������� ������
	this->size = SizeOfFile;                                   //������
	this->znak = 0;                                            //����

	// ��������� ���������� �����
	inBinFile.read((char*)this->elements, SizeOfFile); 
	inBinFile.close();

	return true;
}


void longNumber::SetSize(int newSize)
{	// �������� ������ �����, ��� ���� ������� ���. 
	if (this->size)
		delete[] this->elements;
	this->size = newSize;
	this->znak = 0;
	this->elements = new unsigned char[this->size]();
}

void longNumber::DelZer()
{// ������� �� ����� 0 � ������� ��������
	while ((size - 1) && elements && elements[size - 1] == 0)
		this->size--;

	if (this->size == 1 && elements[0] == 0)
		this->znak = 0;
}

int longNumber::Sravnenie(const longNumber& B)
{
	// ������� ����������
	// 0 - ���� ����� �����,
	// >0 - ���� this ������
	// <0 - ���� this ������
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
	return ((int) this->elements[i] - (int)B[i]) * thisSign;
}

void longNumber::Sdvig(int s)
{// �������� ����� �� s �������� �����
	// �� ����, �� ����, ��� ��������� �� 256^s

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
{// �������� � ��������� "���������"
	longNumber A = left, B = right; // � � ����� ������� �� ������ �����, � B - �������.
	A.znak = 0;
	B.znak = 0;
	//���������� B.Size ? A.Size.
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
	{// ���� ����� ������ �����, �� ������ ���������� �� � ���������� ������ ����

		longNumber result;
		result.SetSize(A.size + 1);

		int carry = 0;
		

		for (int i = 0; i < A.size; i++)
		{
			int tmp = A[i] + carry;
			if (i < B.size)              
				tmp += B[i];  // A[i]+B[i]+carry

			result[i] = tmp % 256; //������� ��������� � ������ �� ������ 256
			carry = tmp / 256;
		}

		result[A.size] = carry;  //���� ��� ��������� �������� �������� ������� ������� ��� � ������� ������
		result.znak = A.znak;
		result.DelZer();
		return result;
	}
	else
	{// �������� ���� �� ������� � ���������� ������ ����
		longNumber result;
		result.SetSize(A.size);

		int carry = 0;
		for (int i = 0; i < A.size; i++)
		{
			int tmp = A[i] - carry;
			if (i < B.size)
				tmp -= B[i];  //A[i]-B[i]-carry

			carry = 0;
			if (tmp < 0)      // ���� ����� �������������, �� ����
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
{// ������� ��������� "���������"
	longNumber result;
	result.SetSize(A.size + B.size);   //�������������� ������ ������� �+�
	int carry = 0;
	for (int i = 0; i < B.size; i++)
	{
		carry = 0;
		for (int j = 0; j < A.size; j++)       //��������� ��������� ���������, ��������������� ��������� i-�� ����� A �� ����� B, 
			                                   
		{
			int tmp = (int)B[i] * (int)A[j] + (int)carry + (int)result[i + j]; //� �������� ���������� ����� ���������� ��� � result, ������� � i - �� �������.	                                                                 
			carry = tmp / 256;
			result[i + j] = tmp % 256;
		}
		result[i + A.size] = carry;                    //���� ������������ ����� result ������ 256 � ������� �������.
	}

	result.znak = (A.znak != B.znak);
	result.DelZer();
	return result;
}

longNumber longNumber::Delenie(const longNumber& A, const longNumber& B, longNumber &ostatok) const
{// ���������� ����� ����� �� �������, � ostatok - �������
	ostatok = A;
	ostatok.znak = 0;

	longNumber Delenieider = B;
	Delenieider.znak = 0;

	if (Delenieider == longNumber((int)0))
	{
		throw Delenie_BY_ZERO;                   //���� �������� =0 ������
	}

	if (ostatok < Delenieider)
	{
		ostatok = A;                        //���� ������� ������ ��������, �� ������� 0
		return longNumber((int)0);
	}

	longNumber result;
	result.SetSize(A.size - B.size + 1);      //������ ������� - �������� + 1

	for (int i = A.size - B.size + 1; i; i--)
	{
		int MaxGran = 256;
		int MinGran = 0;
		int Gran = MaxGran;

		// ���� - ������ �������� ������� ����� Gran
		while (MaxGran - MinGran > 1)
		{
			Gran = (MaxGran + MinGran) / 2;

			// �������� tmp = Gran * Delenieider * 256^i;
			longNumber tmp = Delenieider * Gran;
			tmp.Sdvig(i - 1);	// �������� ����� �� (i - 1) �������� �����
			// �� ����, �� ����, ��� ��������� �� 256^(i - 1)

			if (tmp > ostatok)
				MaxGran = Gran;
			else
				MinGran = Gran;
		}
		longNumber tmp = Delenieider * MinGran;
		tmp.Sdvig(i - 1); // ��������� �� 256 ^ (i - 1)
		ostatok = ostatok - tmp;
		result[i - 1] = MinGran;
	}

	result.znak = (A.znak != B.znak);      //����������� �����
	ostatok.znak = (A.znak != B.znak);
	ostatok.DelZer();
	result.DelZer();

	return result;
}


longNumber Stepen(const longNumber& A, const longNumber& B, longNumber& modul)
{// ���������� A � ������� B �� ������ modul
	if (modul <= (int)0)
		return A ^ B;

	longNumber base = A % modul;
	longNumber result = 1;

	for (longNumber i = B; i > (int)0; i = i - 1)         //��������� ���������� �� ���� � ����� �� �� ������
		result = (result * base) % modul;                

	return result;
}

unsigned char & longNumber::operator[](int i)         // this ����� ������      
{
	if (i < 0)
		return this->elements[this->size + i];
	return this->elements[i];
}

unsigned char longNumber::operator[](int i) const   //���������� �������� "���������� ������" this-const
{
	if (i < 0)
		return this->elements[this->size + i];
	return this->elements[i];
}


longNumber& longNumber::operator=(const longNumber& rhv)    //�������� ������������
{
	if (this->size)                            //����������� �����
		delete[] this->elements;

	this->size = rhv.size;
	this->elements = new unsigned char[size];
	this->znak = rhv.znak;
	memcpy(elements, rhv.elements, size);
	return *this;
}

longNumber longNumber::operator-() const       //������ ����
{// ������� �����
	longNumber result = *this;
	result.znak = !result.znak;
	return result;
}

longNumber longNumber::operator^(const longNumber& right) const             //���������� � �������
{// ���������� *this � ������� right
	longNumber result = 1;
	longNumber base = *this;
	for (longNumber i = right; i > (int)0; i = i - 1)
		result = result * base;
	return result;
}

longNumber longNumber::operator+(const longNumber& right) const             //�������� +
{
	return Sum_Sub(*this, right);
}

longNumber longNumber::operator-(const longNumber& right) const                //��� �� + ������ �� ������ -
{
	return *this + (-right);
}

longNumber longNumber::operator*(const longNumber& right) const              //�������� ���������
{
	return Mult(*this, right);
}

longNumber longNumber::operator/(const longNumber& right) const           //�������� �������, ���.�������� �������
{
	longNumber rem;
	return Delenie(*this, right, rem);                             //���������� ����� �����
}

longNumber longNumber::operator%(const longNumber& right) const            //���������� �������
{
	longNumber rem;
	Delenie(*this, right, rem);
	return rem;
}

bool longNumber::operator>(const longNumber& B)                            //���������
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