/*Waits for the child proccess to finish*/
/*Returns 0 on success, -1 otherwise*/
int waitForChild(pid_t pid);

/*Prints error message of the given command*/
void printErrMsg(char *command);

/*Checks if the command is 'quit' or 'exit'*/
/*Returns 1 if the given command is an exit command, otherwise, returns 0*/
int isQuit(char* command);

/*Checks if -d flag is given*/
/*If so, DEBUG is set to true*/
void isDebug(char **argv);

/*fgets without reading newline character*/
char* readLine(char *str, int n, FILE *stream);

/*Prints current working directory in Linux printing style*/
void printDirectory();

/*Compares the two given commands*/
/*Returns 1 if both are equal, 0 otherwise*/
int isCommand(char *command, char *compareTo);