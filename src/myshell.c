#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/LineParser.h"
#include "../include/myshell.h"

#define MAX_INPUT_SIZE 2048

int main()
{
    printDirectory();

    char buffer[MAX_INPUT_SIZE] = "";
    while (1)
    {
        if(readLine(buffer, MAX_INPUT_SIZE, stdin) != NULL)
        {
            cmdLine *parsedLine = parseCmdLines(buffer);
            execute(parsedLine);
        }
    }
    return 1;
}

int execute(cmdLine *pCmdLine)
{
    char command[MAX_INPUT_SIZE] = "/bin/";
    strcat(command, pCmdLine->arguments[0]);
    execv(command, pCmdLine->arguments);
    return 1;
}

void printDirectory()
{
    char cwd[100] = "";
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("> Current working direcotry: %s\n", cwd);
}

char* readLine(char *str, int n, FILE *stream)
{
	char *ans = fgets(str, n, stream);
	if (ans == NULL)
		return NULL;
	int newlineIndex = strcspn(str, "\n");
	str[newlineIndex] = 0;
	return str;
}
