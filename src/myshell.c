#include <stdio.h>
#include <unistd.h>
#include "../include/LineParser.h"
#include "../include/myshell.h"

#define MAX_BUFFER_SIZE 2048

int main()
{
    printDirectory();

    char buffer[MAX_BUFFER_SIZE] = "";
    while (1)
    {
        if (fgets(buffer, MAX_BUFFER_SIZE, stdin) != NULL)
        {
            printf("user input: %s", buffer);
        }
    }
    return 1;
}

void printDirectory()
{
    char cwd[100] = "";
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("> Current working direcotry: %s\n", cwd);
}
