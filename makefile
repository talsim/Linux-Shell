# All Targets
BIN=./bin/
SOURCE=./src/
INCLUDE=./include/

all: myshell

# Tool invocations
myshell: myshell.o LineParser.o LinkedList.o Utils.o
	gcc -g -Wall -o myshell $(BIN)/myshell.o $(BIN)/LineParser.o $(BIN)/LinkedList.o $(BIN)/Utils.o

# Depends on the source and header files
LineParser.o: $(SOURCE)/LineParser.c $(INCLUDE)/LineParser.h
	gcc -g -Wall -c $(SOURCE)/LineParser.c -o $(BIN)/LineParser.o

myshell.o: $(SOURCE)/myshell.c
	mkdir -p bin
	gcc -g -Wall -c $(SOURCE)/myshell.c -o $(BIN)/myshell.o

LinkedList.o: $(SOURCE)/LinkedList.c $(INCLUDE)/LinkedList.h
	gcc -g -Wall -c $(SOURCE)/LinkedList.c -o $(BIN)/LinkedList.o

Utils.o: $(SOURCE)/Utils.c $(INCLUDE)/Utils.h
	gcc -g -Wall -c $(SOURCE)/Utils.c -o $(BIN)/Utils.o

#tell make that "clean" is not a file name!
.PHONY: clean run

#Clean the build directory	
clean: 
	rm -vf myshell $(BIN)/*
run:
	./myshell