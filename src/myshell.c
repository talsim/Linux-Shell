#include <stdio.h>
#include <string.h>
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
        if(readLine(buffer, MAX_BUFFER_SIZE, stdin) != NULL)
        {
            printf("user input: %s\n", buffer);
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

char* readLine(char *str, int n, FILE *stream)
{
	char *ans = fgets(str, n, stream);
	if (ans == NULL)
		return NULL;
	int newlineIndex = strcspn(str, "\n");
	str[newlineIndex] = '\0';
	return str;
}
