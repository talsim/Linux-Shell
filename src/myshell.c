#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include "../include/LineParser.h"
#include "../include/myshell.h"
#include "../include/LinkedList.h"
#include "../include/utils.h"

#define MAX_INPUT_SIZE 2048

/*Waits for the child proccess to finish*/
/*Returns 0 on success, -1 otherwise*/
static int waitForChild(pid_t pid);

static int saveCommand(List *list, char **argv);

int debug = 0;
char *programName = "";

int main(int argc, char **argv)
{
    programName = argv[2]; // argv[2] = program name without "./"

    if (argc > 1)
        isDebug(argv);

    List *history = create_list();
    char buffer[MAX_INPUT_SIZE] = "";
    while (1)
    {
        printDirectory();
        readLine(buffer, MAX_INPUT_SIZE, stdin);
        if (!isCommand(buffer, ""))
        {
            cmdLine *parsedLine = parseCmdLines(buffer);
            char *command = parsedLine->arguments[0];
            if (!isQuit(command)) // if user entered a command
            {
                saveCommand(history, parsedLine->arguments);
                if (isCommand(command, "cd")) // if the command is "cd"
                    changeCwd(parsedLine);

                else if (isCommand(command, "history"))
                {
                    printf("history:\n");
                    print_list(history);
                }
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

int executeSingleCommand(cmdLine *pCmdLine)
{
    char *command = pCmdLine->arguments[0];
    execvp(command, pCmdLine->arguments);
    return 0; // execvp failed if code reaches this line
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

int changeCwd(cmdLine *line)
{
    if (line->argCount > 1)
    {
        int chdirResult = chdir(line->arguments[1]);
        if (chdirResult != 0)
        {
            printErrMsg("cd");
            return -1;
        }
    }
    return 0;
}

static int waitForChild(pid_t pid)
{
    int waitpidResult = waitpid(pid, NULL, 0);
    if (waitpidResult != pid)
    {
        fprintf(stderr, "%s: waitpid: %s\n", programName, strerror(errno));
        return -1;
    }
    return 0;
}

static int saveCommand(List *list, char **argv)
{
    char *data = combineCommandAndArgs(argv);
    add_last(list, data);
    return 0;
}