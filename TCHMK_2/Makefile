all: main.cpp longNumber.cpp
	g++ -c -fPIC longNumber.cpp
	g++ -shared -o liblongNumber.so longNumber.o
	LD_LIBRARY_PATH=./ g++ main.cpp -llongNumber -I. -Wl,-rpath,. -L. -o TCHMK_1
	
windows: main.cpp longNumber.cpp
	g++ -c longNumber.cpp
	g++ -shared -o longNumber.dll longNumber.o
	g++ main.cpp longNumber.dll -I. -Wl,-rpath,. -L. -o TCHMK_1.exe