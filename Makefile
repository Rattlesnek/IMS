CPP=g++
CFLAGS=-std=c++11 -Wall -Wextra -Wno-deprecated

all: lib main

.PHONY: lib
lib:
	$(MAKE) -C ./lib/config4cpp

main: clean main.cpp 
	$(CPP) $(CFLAGS) main.cpp -o main -L"./lib/config4cpp/lib/" -lconfig4cpp -I"./lib/config4cpp/include"

clean:
	rm -f main
