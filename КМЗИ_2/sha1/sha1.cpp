#include "sha1.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>


unit32 M[100][80]={0};
int M_index=0;





//нелинейные операции
unit32 round_functions(unit32 B,unit32 C,unit32 D,int t)
{
         if(t<20)return (B&C)|((~B)&D);
         if(t<40)return B^C^D;
         if(t<60)return (B&C)|(B&D)|(C&D);
         else return B^C^D;
}

unit32 ROTL(unit32 x,int y)
{
                     
         x=(x<<y)|(x>>(32-y));
   
         return x;
} 

void padding(const byte *testStr,unsigned length)
{
    
    
    //cout << length << endl;
    int index;//index of testStr
    
    
    for(index=0;M_index*16+index<=length/4;index++)
    {
                                                   
            if(4*index<length)M[M_index][index]=testStr[4*index]<<24;
            
            if(4*index+1<length)M[M_index][index]=M[M_index][index]| testStr[4*index+1]<<16;
           
            if(4*index+2<length)M[M_index][index]=M[M_index][index]| testStr[4*index+2]<<8;
           
            if(4*index+3<length)M[M_index][index]=M[M_index][index]| testStr[4*index+3];
         
            if(index==16){index=0;M_index++;}
    }
    index--;
    
    M[M_index][index]=M[M_index][index]| ((0x80) << (3-length%4)*8);
    
    long long int bitlen= length*8;
  
    if(index%16>=14)
               M_index++;
   
 
   M[M_index][14]= bitlen>>32;
   M[M_index][15]= bitlen;
    
  
    
}
void transform()
{
     
   //Инициализируются пять 32-битовых переменных
    unit32 H0=0x67452301;
    unit32 H1=0xEFCDAB89;
    unit32 H2=0x98BADCFE;
    unit32 H3=0x10325476;
    unit32 H4=0xC3D2E1F0;
 //четыре константы
    unit32 K[4]={0x5A827999,0x6ED9EBA1,0x8F1BBCDC,0xCA62C1D6};
    unit32 A;
    unit32 B;
    unit32 C;
    unit32 D;
    unit32 E;
//16 слов по 32-бита дополняются до 80 32-битовых слов
    for(int i=0;i<=M_index;i++)
    {
            for(int t=16;t<80;t++)
               M[i][t]=ROTL(M[i][t-3]^M[i][t-8]^M[i][t-14]^M[i][t-16],1);
//Инициализация хеш-значений
            A=H0;
            B=H1;
            C=H2;
            D=H3;
            E=H4;

//Основной цикл
            
            for(int t=0;t<80;t++)
            {
               unit32 temp=(ROTL(A,5)+round_functions(B,C,D,t)+E+M[i][t]+K[t/20]);
               E=D;
               D=C;
               C=ROTL(B,30);
               B=A;
               A=temp;
            }
      //Добавляем хеш-значение этой части к результату
            H0+=A;
            H1+=B;
            H2+=C;
            H3+=D;
            H4+=E;
                
    }
    cout << hex << H0 <<" "<< H1<<" " << H2 << " "<< H3<<" " << H4 << endl;

}

void init()
{
     for(int i=0;i<100;i++)
        for(int j=0;j<80;j++)
          M[i][j]=0;
}

int SHA1( const byte *input_string, unsigned length)
{

   
   init();
   padding(input_string,length);
   transform();
    
return 0;
}


