#pragma once

class longNumber
{
private:
	int size; // ������ �����
	unsigned char* elements; // ������� �����
	int znak; // ���� �����. 0 - �������������, 1 - �������������

public:
	// ������������
	longNumber();
	longNumber(const char* String);
	longNumber(const longNumber& RightHandValue);
	longNumber(int RightHandValue);

	~longNumber(); // ����������
	
	char* VivodStroki(); // ���������� ������ - ������ �����

	// �������� ��������
	bool WriteFile(const char* FileName);
	bool SaveFile(const char* FileName);
	bool WriteBinFile(const char* FileName);
	bool SaveBinFile(const char* FileName);

	// ������������� ���������
	longNumber& operator=(const longNumber& right);
	longNumber operator+(const longNumber& right) const;
	longNumber operator-() const;
	longNumber operator-(const longNumber& right) const;
	longNumber operator*(const longNumber& right) const;
	longNumber operator/(const longNumber& right) const;
	longNumber operator%(const longNumber& right) const;
	longNumber operator^(const longNumber& right) const;

	bool operator>(const longNumber& B);
	bool operator>=(const longNumber& B);
	bool operator<(const longNumber& B);
	bool operator<=(const longNumber& B);
	bool operator==(const longNumber& B);
	bool operator!=(const longNumber& B);

private:
	void SetSize(int newSize); // �������� ������ ��� newSize ���������
	unsigned char & operator[](int i);
	unsigned char operator[](int i) const;
	void DelZer(); // �������� ������� �����
	int Sravnenie(const longNumber& B);
	void Sdvig(int s);

	longNumber Sum_Sub(const longNumber& left, const longNumber& right) const;
	longNumber Mult(const longNumber A, const longNumber B) const;
	longNumber Delenie(const longNumber& A, const longNumber& B, longNumber &ostatok) const;

};

longNumber Stepen(const longNumber& A, const longNumber& B, longNumber& modul);