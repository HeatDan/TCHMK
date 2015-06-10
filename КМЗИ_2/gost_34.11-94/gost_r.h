#include <iostream>
#include <fstream>
#include <memory.h>

using namespace std;


class Gost_r
{
    typedef unsigned char byte;
    typedef byte B[32];
    typedef byte B32[4];

    byte *buffer, res[32];

    unsigned int length;

    int fi(int argument);

    void E_f(byte A[], byte K[], byte R[]);//Функция f в ГОСТ 28147-89
    void E(byte D[], byte K[], byte R[]);
    void A_Y(byte Y[], byte R[]);
    void P_Y(byte Y[], byte R[]);
    void psi_Y(byte arr[]);
    void psi_round(byte arr[], int p);
    void f(byte H[], byte M[], byte newH[]);
public:
    bool read_file(char *fileName);
    bool Show_hash();
    
    void gost_r();
};
