/*Prints current working directory*/
void printDirectory();

/*fgets without reading newline character*/
char* readLine(char *str, int n, FILE *stream);

/*Executes the given command*/
/*Returns 1 if everything is OK, else, returns 0*/
int execute(cmdLine* pCmdLine);

/*Checks if the command is 'quit' or 'exit'*/
/*Returns 1 if the given command is an exit command, otherwise, returns 0*/
int isQuit(char* command);

/*Checks if -d flag is given*/
/*If so, DEBUG is set to true*/
void isDebug(char **argv);

/*Forks and executes the command on the child proccess*/
/*Returns 1 if it was successful, else, returns 0*/
int forkAndExec(cmdLine *line);