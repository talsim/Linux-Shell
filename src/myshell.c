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
                saveCommand(history, buffer, parsedLine->arguments);
                execute(parsedLine, buffer, history);
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