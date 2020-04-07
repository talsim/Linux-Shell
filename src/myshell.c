#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include "../include/LineParser.h"
#include "../include/myshell.h"

#define MAX_INPUT_SIZE 2048

int debug = 0;

int main(int argc, char **argv)
{

    if (argc > 1)
        isDebug(argv);

    printDirectory();

    char buffer[MAX_INPUT_SIZE] = "";
    while (1)
    {
        if (readLine(buffer, MAX_INPUT_SIZE, stdin) != NULL)
        {
            cmdLine *parsedLine = parseCmdLines(buffer);
            if (!isQuit(parsedLine->arguments[0])) // if user entered a command
            {
                forkAndExec(parsedLine);
            }
            else
            {
                printf("Quiting...\n");
                exit(EXIT_SUCCESS);
            }
            freeCmdLines(parsedLine);
        }
    }
    return EXIT_SUCCESS;
}

int execute(cmdLine *pCmdLine)
{
    char *command = pCmdLine->arguments[0];
    if (execvp(command, pCmdLine->arguments))
        return 1;
    return 0;
}

void printDirectory()
{
    char cwd[100] = "";
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("> Current working direcotry: %s\n", cwd);
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

int forkAndExec(cmdLine *line)
{
    pid_t pid = fork();
    switch (pid)
    {
    case 0:
        // runs on child proccess:
        if (execute(line))
        {
            perror("Error");
            _exit(EXIT_FAILURE);
        }
        _exit(EXIT_SUCCESS);
        break;
    case -1:
        // fork failed
        fprintf(stderr, "fork() failed");
        return 0;
    // runs on parent proccess:
    default:
        if (debug)
        {
            fprintf(stderr, "Forked, parent proccess id: %d\n", getpid());
            fprintf(stderr, "Executing command: %s\n", line->arguments[0]);
        }
        return 1;
    }
}
