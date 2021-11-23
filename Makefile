PP = g++
EXEC = ./customer_queue
TMPOUT=main.testresult
CFLAGS := -g -Wall -O3 -std=c++11

build: src/main.cpp include/client.hpp include/store.hpp src/client.cpp src/store.cpp
	${PP} -c src/main.cpp src/client.cpp src/store.cpp
	${PP} -o main main.o client.o store.o

run: clean build
	./main < test/default.txt 

debug:
	${PP} main.cpp -o test

clean:
	rm -rf *o main

tests: build
	@bash run_tests.sh ./main $(TMPOUT)