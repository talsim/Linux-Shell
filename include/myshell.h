/*Prints current working directory*/
void printDirectory();

/*fgets without reading newline character*/
char* readLine(char *str, int n, FILE *stream);

/*Executes the given command*/
/*Returns EXIT_SUCCESS if everything is OK, else, returns EXIT_FAILURE*/
int execute(cmdLine* pCmdLine);

/*Checks if the command is 'quit' or 'exit'*/
/*Returns 1 if the given command is an exit command, otherwise, returns 0*/
int isQuit(char* command);

/*Checks if -d flag is given*/
/*If so, DEBUG is set to true*/
void isDebug(char **argv);