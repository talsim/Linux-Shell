#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include "../include/utils.h"
#include "../include/LinkedList.h"

extern int debug;
extern char *programName;

// Ansi color codes
#define BOLD_BLUE "\x1B[1;34m"
#define BOLD_RED "\x1B[1;31m"
#define RESET "\x1B[0m"

void printErrMsg(char *command, char *errorMsg)
{
    if (errorMsg == NULL)
        fprintf(stderr, "%s: %s: " BOLD_RED "%s\n" RESET, programName, command, strerror(errno));
    else // print errorMsg
        fprintf(stderr, "%s: %s: " BOLD_RED "%s\n", programName, command, errorMsg);
}

void isDebug(char **argv)
{
    if (isCommand(argv[1], "-d"))
    {
        debug = 1;
        printf("Debug mode enabled\n");
    }
}

int isQuit(char *command)
{
    if (isCommand(command, "quit") || isCommand(command, "exit"))
        return 1;
    return 0;
}

int isCommand(const char *command, char *compareTo)
{
    return strcmp(command, compareTo) == 0;
}

char *readLine(char *str, int n, FILE *stream)
{
    char *ans = fgets(str, n, stream);
    if (ans == NULL)
        return NULL;
    int newlineIndex = strcspn(str, "\n");
    str[newlineIndex] = 0;
    return str;
}

void printDirectory()
{
    char cwd[100] = "";
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        char *pCwd = cwd + 1;
        printf(BOLD_BLUE "%s" RESET "# ", pCwd); // Linux printing style
    }
}

char *combineCommandAndArgs(const char **argv)
{
    char *ans = (char *)malloc(strlen(argv[0]) + 1); // allocate argv[0] bytes on heap memory
    if (ans)
    {
        strcpy(ans, argv[0]);
        const char **args = argv + 1;
        int maxArgsLength = 255; // in LineParser -> max length of argv = 256

        for (int i = 0; i < maxArgsLength; i++)
        {
            if (args[i] == NULL)
                break;
            strcat(ans, " ");
            strcat(ans, args[i]);
        }
        return ans;
    }
    return NULL;
}

int isInteger(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}