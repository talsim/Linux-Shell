#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include "../include/LineParser.h"
#include "../include/LinkedList.h"
#include "../include/utils.h"

#define MAX_INPUT_SIZE 2048

char *programName = "";

int main(int argc, char **argv)
{
    programName = argv[0] + 2; // argv[0] + 2 = program name without "./"

    List *history = create_list();

    char *buf = NULL;
    while (1)
    {
        char *cwd = getFormattedCwd();
        buf = readline(cwd);

        free(cwd);

        if (!isempty(buf))
        {
            cmdLine *parsedLine = parseCmdLines(buf);
            char *command = parsedLine->arguments[0];
            if (!isQuit(command)) // if user entered a command
            {
                saveCommand(history, buf, parsedLine->arguments);
                execute(parsedLine, buf, history);
            }
            else
            {
                free_list(history);
                freeCmdLines(parsedLine);
                free(buf);
                break;
            }
            freeCmdLines(parsedLine);
            free(buf);
        }
    }
    return EXIT_SUCCESS;
}