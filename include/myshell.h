/*Prints current working directory*/
void printDirectory();

/*fgets without reading newline character*/
char* readLine(char *str, int n, FILE *stream);

/*Executes the given command*/
/*Returns 1 if everything is OK, else, returns 0*/
int execute(cmdLine* pCmdLine);