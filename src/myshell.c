#include <stdio.h>
#include <unistd.h>
#include "../include/LineParser.h"
#include "../include/myshell.h"

int main()
{
    printDirectory();
    return 1;
}

void printDirectory()
{
    char cwd[100];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("> Current working direcotry: %s\n", cwd);
}
