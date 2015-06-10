#ifndef SHA1H
#define SHA1H




#include <cstring>                                                                                      
#include <iostream>                                                                                    
#include <sstream>                                                                                      
#include <fstream>                                                                                      


typedef unsigned int unit32;
typedef unsigned char byte;

using namespace std;




int SHA1(const byte *input_string,unsigned length);







#endif