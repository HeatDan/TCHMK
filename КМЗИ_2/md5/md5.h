#ifndef MD5_H
#define MD5_H
 
#include <string>
#include <fstream>
 

typedef unsigned char byte;
typedef unsigned int uint32;
 
using std::string;
using std::ifstream;
 

class MD5 {
public:
    MD5();// конструктор по умолчанию
    MD5(const void* input, size_t length); //конструктор от входного буфера
    MD5(const string& str); // конструктор от строки
    MD5(ifstream& in); // конструктор от входного файла
    void update(const void* input, size_t length); // обновление контекста от входного буфера
    void update(const string& str); // Обновление констекста от строки
    void update(ifstream& in); // обновление контекста от входного файла
    const byte* digest(); //функция возврата дайджеста MD5
    string toString();// приведение к типу string
    void reset(); // установка контекста по умолчанию
 
private:
    void update(const byte* input, size_t length);
    void final();
    void transform(const byte block[64]);
    void encode(const uint32* input, byte* output, size_t length);
    void decode(const byte* input, uint32* output, size_t length);
    string bytesToHexString(const byte* input, size_t length);
 
    /* class uncopyable */
    MD5(const MD5&);
    MD5& operator=(const MD5&);
 
private:
    uint32 _state[4];   /* регистры ABCD */
    uint32 _count[2];   /* количество бит по модулю 2^64 */
    byte _buffer[64];   /* входной буфер */
    byte _digest[16];   /* дайджест сообщения */
    bool _finished;     /* завершено ли вычисление? */
 
    static const byte PADDING[64];  /* основа для вычисления */
    static const char HEX[16];
    enum { BUFFER_SIZE = 1024 };
};
 
#endif