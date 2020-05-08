#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include "../include/LineParser.h"
#include "../include/LinkedList.h"
#include "../include/utils.h"
#include "../include/myshell.h"

#define MAX_INPUT_SIZE 2048

char *programName = "";

int main(int argc, char **argv)
{
    programName = argv[0] + 2; // argv[0] + 2 = program name without "./"
    
    List *history = create_list();

    char buffer[MAX_INPUT_SIZE] = "";
    while (1)
    {
        printDirectory();
        readLine(buffer, MAX_INPUT_SIZE, stdin);
        if (!isempty(buffer))
        {
            cmdLine *parsedLine = parseCmdLines(buffer);
            char *command = parsedLine->arguments[0];
            if (!isQuit(command)) // if user entered a command
            {
                saveCommand(history, parsedLine->arguments);
                execute(parsedLine, history);
            }
            else
            {
                free_list(history);
                freeCmdLines(parsedLine);
                break;
            }
            freeCmdLines(parsedLine);
        }
    }
    return EXIT_SUCCESS;
}

int execute(cmdLine *line, List *history)
{
    if (isBuiltin(line->arguments[0]))
    {
        executeBuiltin(line, history);
    }
    else
    {
        executeFromBin(line);
    }
    return 0;
}