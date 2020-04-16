#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include "../include/utils.h"

extern int debug;
extern char* programName;

// Ansi color codes
#define BOLD_BLUE "\x1B[1;34m"
#define BOLD_RED "\x1B[1;31m"
#define RESET "\x1B[0m"

void printErrMsg(char *command)
{
    fprintf(stderr, "%s: %s: " BOLD_RED "%s\n" RESET, programName, command, strerror(errno));
}

int waitForChild(pid_t pid)
{
    int waitpidResult = waitpid(pid, NULL, 0);
    if (waitpidResult != pid)
    {
        fprintf(stderr, "%s: waitpid: %s\n", programName, strerror(errno));
        return -1;
    }
    return 0;
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

int isCommand(char *command, char *compareTo)
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
        printf(BOLD_BLUE "%s" RESET "# ", pCwd); // Linux shell printing style
    }
}