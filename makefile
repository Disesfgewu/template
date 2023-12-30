.PHONY: directories clean stat

all: directories bin/ut_all 

bin/ut_all:./main.cpp
	g++ -std=c++14 ./main.cpp -o bin/ut_all 

directories:
	mkdir -p bin

clean:
	rm -f bin/*
