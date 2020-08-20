#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include "../include/LinkedList.h"
#include "../include/LineParser.h"
#include "../include/utils.h"
#include "../include/BuiltinCommands.h"

extern char *programName;

// Ansi color codes
#define BOLD_BLUE "\x1B[1;34m"
#define BOLD_RED "\x1B[1;31m"
#define RESET "\x1B[0m"

#define MAX_INPUT_SIZE 2048

void printErrMsg(char *command, char *errorMsg)
{
    if (errorMsg == NULL)
        fprintf(stderr, "%s: %s: " BOLD_RED "%s\n" RESET, programName, command, strerror(errno));
    else // print errorMsg
        fprintf(stderr, "%s: %s: " BOLD_RED "%s\n", programName, command, errorMsg);
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

int isEnvVarsCommand(char *command)
{
    return strcmp(command, "set") == 0 ||
    strcmp(command, "env") == 0 ||
    strcmp(command, "delete") == 0;
}

char *getFormattedCwd()
{
    char cwd[100] = "";
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        size_t formattedCwdSize = sizeof(cwd) + 50;
        char *formattedCwd = malloc(formattedCwdSize);
        snprintf(formattedCwd, formattedCwdSize, BOLD_BLUE "%s" RESET "# ", cwd); // Linux shell printing style
        return formattedCwd;
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

int waitForChild(pid_t pid)
{
    int waitpidResult = waitpid(pid, NULL, 0);
    if (waitpidResult != pid)
    {
        printErrMsg("waitpid", NULL);
        return -1;
    }
    return 0;
}

int saveCommand(List *history, char buffer[MAX_INPUT_SIZE], char *const argv[MAX_ARGUMENTS])
{
    const char *command = argv[0];
    if (command[0] == '!')
        return 0;                                    // just return and let invokeCommandByIndex call you
    char *data = (char *)malloc(strlen(buffer) + 1); // combineCommandAndArgs(argv);
    if (data)
    {
        strcpy(data, buffer);

        if (is_empty(history))
        {
            add_last(history, data);
        }
        else
        {
            if (!isCommand(command, get_last(history)))
                add_last(history, data);
            else
                free(data);
        }
        return 0;
    }
    return -1;
}

int executeFromBin(cmdLine *line)
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
            printErrMsg(line->arguments[0], NULL);
            _exit(EXIT_FAILURE);
        }
        break;
    }
    case -1:
        // fork failed
        printErrMsg("fork", NULL);
        return -1;
    default:
        // runs on parent proccess:
        if (line->blocking == 1) // if ampersand isn't added, wait for child to finish
            waitForChild(pid);
    }
    return 0;
}

void executeBuiltin(cmdLine *parsedLine, char buffer[MAX_INPUT_SIZE], List *history, List *envVars)
{
    char *command = parsedLine->arguments[0];
    if (isCommand(command, "cd"))
        changeCwd(parsedLine);

    else if (isCommand(command, "history"))
        printHistory(history);

    else if (command[0] == '!')
    {
        char *input = command + 1;
        if (isInteger(input))
        {
            int index = atoi(input);
            int result = invokeCommandByIndex(history, envVars, buffer, index);
            if (result == -1)
                printErrMsg(command, "event not found");
        }
        else
            printErrMsg(command, "event not found");
    }
    else if (isCommand(command, "set") || isCommand(command, "env") || isCommand(command, "delete")) // if command is related to env variables
    {
        executeEnvCommands(command, parsedLine, envVars);
    }
}

int executeEnvCommands(char *command, cmdLine *parsedLine, List *envVars)
{
    if (isCommand(command, "set"))
    {
        executeSet(parsedLine, envVars);
    } 
    else if (isCommand(command, "env"))
    {
        executeEnv(parsedLine, envVars);
    }
    else if (isCommand(command, "delete"))
    {
        executeDelete(parsedLine, envVars);
    }
    return 1;
}

int executeSingleCommand(cmdLine *pCmdLine)
{
    char *command = pCmdLine->arguments[0];
    execvp(command, pCmdLine->arguments);
    return 0; // execvp failed if code reaches this line
}

int execute(cmdLine *line, char buffer[MAX_INPUT_SIZE], List *history, List *envVars)
{
    if (isBuiltin(line->arguments[0]))
    {
        executeBuiltin(line, buffer, history, envVars);
    }
    else
    {
        executeFromBin(line); // e.g "echo Hello", "cat foo"
    }
    return 0;
}

int isBuiltin(char *command)
{
    if (isCommand(command, "cd") ||
        isCommand(command, "history") ||
        command[0] == '!' ||
        isEnvVarsCommand(command))
        return 1;   
    return 0;
}

int isempty(const char *s)
{
    while (*s)
    {
        if (!isspace(*s))
            return 0;
        s++;
    }
    return 1;
}