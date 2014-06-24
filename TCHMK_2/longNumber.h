#pragma once

class longNumber
{
private:
	int size; // размер числа
	unsigned char* elements; // разряды числа
	int znak; // знак числа. 0 - положительное, 1 - отрицательное

public:
	// конструкторы
	longNumber();
	longNumber(const char* String);
	longNumber(const longNumber& RightHandValue);
	longNumber(int RightHandValue);

	~longNumber(); // деструктор
	
	char* VivodStroki(); // возвращает строку - запись числа

	// файловые операции
	bool WriteFile(const char* FileName);
	bool SaveFile(const char* FileName);
	bool WriteBinFile(const char* FileName);
	bool SaveBinFile(const char* FileName);

	// перегружаемые операторы
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
	void SetSize(int newSize); // выделяет память под newSize элементов
	unsigned char & operator[](int i);
	unsigned char operator[](int i) const;
	void DelZer(); // удаление ведущих нулей
	int Sravnenie(const longNumber& B);
	void Sdvig(int s);

	longNumber Sum_Sub(const longNumber& left, const longNumber& right) const;
	longNumber Mult(const longNumber A, const longNumber B) const;
	longNumber Delenie(const longNumber& A, const longNumber& B, longNumber &ostatok) const;

};

longNumber Stepen(const longNumber& A, const longNumber& B, longNumber& modul);