################################################################
#	Project:	Chat server using IPK24-CHAT protocol
#	File: 		Makefile
#	Author: 	Adam Ližičiar xlizic00@stud.fit.vutbr.cz
################################################################

COMPILER = g++
COMPILER_FLAGS = -std=c++20 -Wall -Wextra -Werror
PROGRAM_NAME = ipk24chat-server

.PHONY: make run test clean pack

make: src/main.cpp
	$(COMPILER) $(COMPILER_FLAGS) src/main.cpp -o $(PROGRAM_NAME)

run: make
	./$(PROGRAM_NAME)

test: make
	g++ test/test.cpp -o test/test -lgtest -lgtest_main
	./test/test

clean:
	rm -f test/test
	rm -f *.exe *.out *.core *.zip
	rm -f $(PROGRAM_NAME)

pack:
	zip -r xlizic00.zip filter-out .vscode,$(wildcard *)
