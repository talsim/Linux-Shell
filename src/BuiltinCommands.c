#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include "../include/LineParser.h"
#include "../include/LinkedListEnv.h"
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

int invokeCommandByIndex(List *history, List *envVars, char buffer[2048], int index)
{
    char *data = get(history, index);
    if (data)
    {
        cmdLine *line = parseCmdLines(data);
        saveCommand(history, data, line->arguments);
        printf("%s\n", data); // print command to console before running it
        int execResult = execute(line, buffer, history, envVars);
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

void executeSet(cmdLine *line, List_env *envVars)
{
    char *name = line->arguments[1];
    char *value = line->arguments[2];
    if (!contains_env(envVars, name)) // if name doesn't exist
    {
        add_last_env(envVars, name, value);
    }
    else
    {
        // override the existing value

    }
}

void executeEnv(cmdLine *line, List_env *envVars)
{
    for (int i = 0; i < envVars->size; i++)
    {
        printf("%d %s:%s\n", i, get_env(envVars, i))
    }
}

void executeDelete(cmdLine *line, List_env *envVars)
{

}