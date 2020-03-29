# All Targets
BIN=./bin/
SOURCE=./src/
INCLUDE=./include/

all: myshell

# Tool invocations
myshell: myshell.o LineParser.o 
	gcc -g -Wall -o myshell $(BIN)/myshell.o $(BIN)/LineParser.o 

# Depends on the source and header files
LineParser.o: $(SOURCE)/LineParser.c $(INCLUDE)/LineParser.h
	gcc -g -Wall -ansi -c $(SOURCE)/LineParser.c -o $(BIN)/LineParser.o

myshell.o: $(SOURCE)/myshell.c
	mkdir -p bin
	gcc -g -Wall -ansi -c $(SOURCE)/myshell.c -o $(BIN)/myshell.o

#tell make that "clean" is not a file name!
.PHONY: clean run

#Clean the build directory	
clean: 
	rm -vf myshell $(BIN)/*
run:
	./myshell