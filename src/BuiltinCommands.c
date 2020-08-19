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

int changeCwd(cmdLine *line)
{
    if (line->argCount > 1)
    {
        int chdirResult = chdir(line->arguments[1]);
        if (chdirResult != 0)
        {
            printErrMsg("cd", NULL);
            return -1;
        }
    }
    return 0;
}

int invokeCommandByIndex(List *history, char buffer[2048], int index)
{
    char *data = get(history, index);
    if (data)
    {
        cmdLine *line = parseCmdLines(data);
        saveCommand(history, data, line->arguments);
        printf("%s\n", data); // print command to console before running it
        int execResult = execute(line, buffer, history);
        freeCmdLines(line);
        if (execResult == 0)
            return 0;
    }
    return -1;
}

void printHistory(List *history)
{
    for (int i = 0; i < history->size; i++)
        printf("%d %s\n", i, get(history, i));
}

int executeSet(cmdLine *line, List *envVars)
{
    if () // if name already exists
}

int executeEnv(cmdLine *line, List *envVars)
{

}

int executeDelete(cmdLine *line, List *envVars)
{
    
}