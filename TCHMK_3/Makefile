all: 
	swig -c++ -python longNumber.i
	g++ -fPIC -c longNumber.cpp
	g++ -fPIC -c longNumber_wrap.cxx -I/usr/include/python2.7
	g++ -shared longNumber.o longNumber_wrap.o -o _longNumber.so
	rm longNumber.o longNumber_wrap.cxx longNumber_wrap.o
	
windows32:
	swig -c++ -python longNumber.i
	g++ -c longNumber.cpp
	g++ -c longNumber_wrap.cxx -IC:\Python27\include
	g++ longNumber.o longNumber_wrap.o -Ic:\python27\include -Lc:\python27\libs -lpython27 -shared -o _longNumber.pyd
	del longNumber.o longNumber_wrap.cxx longNumber_wrap.o
	
windows64:
	swig -c++ -python longNumber.i
	C:\TDM-GCC-64\bin\g++ -c longNumber.cpp
	C:\TDM-GCC-64\bin\g++ -c longNumber_wrap.cxx -IC:\Python27\include
	C:\TDM-GCC-64\bin\g++ longNumber.o longNumber_wrap.o -Ic:\python27\include -Lc:\python27\libs -lpython27 -shared -o _longNumber.pyd
	del longNumber.o longNumber_wrap.cxx longNumber_wrap.o