/*Prints error message of the given command, using errno.*/
/*Else, prints errorMsg*/
void printErrMsg(char *command, char *errorMsg);

/*Checks if the command is 'quit' or 'exit'*/
/*Returns 1 if the given command is an exit command, otherwise, returns 0*/
int isQuit(char *command);

/*fgets without reading newline character*/
char *readLine(char *str, int n, FILE *stream);

/*Prints current working directory in Linux printing style*/
void printDirectory();

/*Compares the two given commands*/
/*Returns 1 if both are equal, 0 otherwise*/
int isCommand(const char *command, char *compareTo);

/*Concatenates command and arguments in the given argv*/
/*Returns a pointer to the concatenated string on the heap, NULL otherwise*/
char *combineCommandAndArgs(const char **argv);

/*Checks if str is an integer*/
/*Returns 1 if true, 0 elsewise*/
int isInteger(char *str);

/*Waits for the child proccess to finish*/
/*Returns 0 on success, -1 otherwise*/
int waitForChild(pid_t pid);

/*Saves the command and the arguments the user inputed*/
/*Returns 0 on success, -1 on failure*/
int saveCommand(List *list, const char **argv);

/**/
int executeFromBin(cmdLine *line);

/**/
void executeBuiltin(cmdLine *parsedLine, List *history);

/*Executes the given command*/
/*Returns 0 if failed*/
int executeSingleCommand(cmdLine *pCmdLine);

/**/
int isBuiltin(char *command);