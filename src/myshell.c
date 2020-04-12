#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "../include/LineParser.h"
#include "../include/myshell.h"
//#include "../include/errorMessages.h"

#define MAX_INPUT_SIZE 2048

// Ansi color codes
#define BOLD_BLUE "\x1B[1;34m"
#define BOLD_RED "\x1B[1;31m"
#define RESET "\x1B[0m"

int debug = 0;
char *programName = "";

int main(int argc, char **argv)
{
    programName = argv[0] + 2; // argv[0] + 2 = program name without "./"

    if (argc > 1)
        isDebug(argv);

    char buffer[MAX_INPUT_SIZE] = "";
    while (1)
    {
        printDirectory();
        if (readLine(buffer, MAX_INPUT_SIZE, stdin) != NULL)
        {
            cmdLine *parsedLine = parseCmdLines(buffer);
            char *command = parsedLine->arguments[0];
            if (!isQuit(command)) // if user entered a command
            {
                if (strcmp(command, "cd") == 0) // if the command is "cd"
                    chCwd(parsedLine);
                else
                    execute(parsedLine);
            }
            else
                exit(EXIT_SUCCESS);

            freeCmdLines(parsedLine);
        }
    }
    return EXIT_SUCCESS;
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

int executeSingleCommand(cmdLine *pCmdLine)
{
    char *command = pCmdLine->arguments[0];
    execvp(command, pCmdLine->arguments);
    return 0; // execvp failed if code reaches this line
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

int isQuit(char *command)
{
    if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0)
        return 1;
    return 0;
}

void isDebug(char **argv)
{
    if (strcmp(argv[1], "-d") == 0)
    {
        debug = 1;
        printf("Debug mode enabled\n");
    }
}

int execute(cmdLine *line)
{
    pid_t pid = fork();
    switch (pid)
    {
    case 0:
    {
        // runs on child proccess:
        int status = executeSingleCommand(line);
        if (status != 1)
        {
            printErrMsg(line->arguments[0]);
            _exit(EXIT_FAILURE);
        }
        break;
    }
    case -1:
        // fork failed
        printErrMsg("fork");
        return 0;
    default:
        // runs on parent proccess:
        if (line->blocking == 1) // if ampersand isn't added, wait for child to finish
            waitForChild(pid);
        if (debug)
        {
            fprintf(stderr, "Forked, parent proccess id: %d\n", getpid());
            fprintf(stderr, "Child proccess id: %d\n", pid);
            fprintf(stderr, "Executing command: %s\n", line->arguments[0]);
        }
    }
    return 1;
}

int chCwd(cmdLine *line)
{
    if (line->argCount > 1) // Ok
    {
        int chdirResult = chdir(line->arguments[1]);
        if (chdirResult != 0)
            printErrMsg("cd");
        return -1;
    }
    return 0;
}

int waitForChild(pid_t pid)
{
    int waitpidVal = waitpid(pid, NULL, 0);
    if (waitpidVal != pid)
    {
        printErrMsg("waitpid");
        return -1;
    }
    return 0;
}

void printErrMsg(char *command)
{
    char firstChar = command[0];
    switch (firstChar)
    {
    case 'c':
        fprintf(stderr, "%s: cd: " BOLD_RED "%s\n", programName, strerror(errno));
        break;
    case 'w':
        fprintf(stderr, "%s: waitpid: " BOLD_RED "%s\n", programName, strerror(errno));
        break;
    case 'f':
        fprintf(stderr, "%s: fork: " BOLD_RED "%s\n", programName, strerror(errno));
        break;
    default:
        fprintf(stderr, "%s: %s: " BOLD_RED "command not found\n", programName, command);
        break;
    }
}