/*Prints error message of the given command*/
void printErrMsg(char *command);

/*Checks if the command is 'quit' or 'exit'*/
/*Returns 1 if the given command is an exit command, otherwise, returns 0*/
int isQuit(char *command);

/*Checks if -d flag is given*/
/*If so, DEBUG is set to true*/
void isDebug(char **argv);

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