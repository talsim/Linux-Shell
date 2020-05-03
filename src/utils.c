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

/*Concatenates command and arguments in the given argv*/
/*Returns a pointer to the concatenated string on the heap, NULL otherwise*/
static char *combineCommandAndArgs(char* const argv[MAX_ARGUMENTS]);

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

static char *combineCommandAndArgs(char *const argv[MAX_ARGUMENTS])
{
    char *ans = (char *)malloc(strlen(argv[0]) + 1); // allocate argv[0] bytes on heap memory
    if (ans)
    {
        strcpy(ans, argv[0]);
        char* const* args = argv + 1;
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

int saveCommand(List *history, char *const argv[MAX_ARGUMENTS])
{
    const char *command = argv[0];
    if (command[0] == '!')
        return 0; // just return and let invokeCommandByIndex call you
    char *data = combineCommandAndArgs(argv);
    if (data)
    {
        if (is_empty(history))
        {
            add_last(history, data);
        }
        else
        {
            if (!isCommand(argv[0], get_last(history)))
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

void executeBuiltin(cmdLine *parsedLine, List *history)
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
            if (invokeCommandByIndex(history, index) == -1)
                printErrMsg(command, "event not found");
        }
        else
            printErrMsg(command, "event not found");
    }
}

int executeSingleCommand(cmdLine *pCmdLine)
{
    char *command = pCmdLine->arguments[0];
    execvp(command, pCmdLine->arguments);
    return 0; // execvp failed if code reaches this line
}

int isBuiltin(char *command)
{
    if (isCommand(command, "cd") ||
        isCommand(command, "history") ||
        command[0] == '!')
        return 1;
    return 0;
}