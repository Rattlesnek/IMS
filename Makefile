CPP=g++
CFLAGS=-std=c++11 -Wall -Wextra -Wno-deprecated

all: lib main

.PHONY: lib
lib:
	$(MAKE) -C ./lib/config4cpp

main: clean *.cpp
	$(CPP) $(CFLAGS) *.cpp -o main -I"./lib/config4cpp/include" -L"./lib/config4cpp/lib/" -lconfig4cpp  -I"/usr/local/include" -L"/usr/local/lib64" -lsimlib -lm

clean:
	rm -f main
