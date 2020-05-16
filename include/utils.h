/*Prints error message of the given command, using errno.*/
/*Else, prints errorMsg*/
void printErrMsg(char *command, char *errorMsg);

/*Checks if the command is 'quit' or 'exit'*/
/*Returns 1 if the given command is an exit command, otherwise, returns 0*/
int isQuit(char *command);

/*Checks if command is builtin*/
/*Returns 1 if builtin, 0 otherwise*/
int isBuiltin(char *command);

/*fgets without reading newline character*/
char *readLine(char *str, int n, FILE *stream);

/*Prints current working directory in Linux printing style*/
void printDirectory();

/*Compares the two given commands*/
/*Returns 1 if both are equal, 0 otherwise*/
int isCommand(const char *command, char *compareTo);

/*Checks if str is an integer*/
/*Returns 1 if true, 0 elsewise*/
int isInteger(char *str);

/*Waits for the child proccess to finish*/
/*Returns 0 on success, -1 otherwise*/
int waitForChild(pid_t pid);

/*Saves the command and the arguments the user inputed*/
/*Returns 0 on success, -1 on failure*/
int saveCommand(List *history, char buffer[2048], char *const argv[MAX_ARGUMENTS]);

/*Executes line on child proccess*/
/*Returns 0 on success, -1 on failure*/
int executeFromBin(cmdLine *line);

/*Executes builtin command on parent process*/
void executeBuiltin(cmdLine *parsedLine, char buffer[2048], List *history);

/*Executes the given command*/
/*Returns 0 if failed*/
int executeSingleCommand(cmdLine *pCmdLine);

/*Forks and executes the command on the child proccess*/
/*Returns 0 if it was successful, else, returns -1*/
int execute(cmdLine *line, char buffer[2048], List *history);

/*Checks if the given string is empty*/
/*Returns 1 if true, 0 elsewise*/
int isempty(const char *s);