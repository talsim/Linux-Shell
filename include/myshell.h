/*Prints current working directory in Linux printing style*/
void printDirectory();

/*fgets without reading newline character*/
char* readLine(char *str, int n, FILE *stream);

/*Executes the given command*/
/*Returns 0 if failed*/
int executeSingleCommand(cmdLine* pCmdLine);

/*Checks if the command is 'quit' or 'exit'*/
/*Returns 1 if the given command is an exit command, otherwise, returns 0*/
int isQuit(char* command);

/*Checks if -d flag is given*/
/*If so, DEBUG is set to true*/
void isDebug(char **argv);

/*Forks and executes the command on the child proccess*/
/*Returns 1 if it was successful, else, returns 0*/
int execute(cmdLine *line);

/*Changes the current working directoy*/
/*On success, returns zero. On error, -1 is returned.*/
int chCwd(cmdLine *line);

/*Waits for the child proccess to finish*/
/*Returns 0 on success, -1 otherwise*/
int waitForChild(pid_t pid);