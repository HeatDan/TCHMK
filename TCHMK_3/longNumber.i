%module longNumber
%{
/* Includes the header in the wrapper code */
#include "longNumber.h"
%}

/* Parse the header file to generate wrappers */
%include "longNumber.h"