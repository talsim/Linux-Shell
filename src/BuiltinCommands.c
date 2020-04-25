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

int invokeCommandByIndex(List *history, int index)
{
    char *data = get(history, index);
    if (data)
    {
        cmdLine *line = parseCmdLines(data);
        saveCommand(history, line->arguments);
        printf("%s\n", data); // print command to console before running it
        int execResult = execute(line, history);
        if (execResult == 0)
            return 0;
    }
    return -1;
}