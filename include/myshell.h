/*Executes the given command*/
/*Returns 0 if failed*/
int executeSingleCommand(cmdLine *pCmdLine);

/*Forks and executes the command on the child proccess*/
/*Returns 0 if it was successful, else, returns -1*/
int execute(cmdLine *line);

/*Changes the current working directoy*/
/*On success, returns zero. On error, -1 is returned.*/
int changeCwd(cmdLine *line);

/*Waits for the child proccess to finish*/
/*Returns 0 on success, -1 otherwise*/
int waitForChild(pid_t pid);

/*Saves the command and the arguments the user inputed*/
/*Returns 0 on success, -1 on failure*/
int saveCommand(List *list, const char **argv);

/*Invokes the command in the history at the given index*/
/*Returns 0 on success, -1 on failure*/
int invokeCommandByIndex(List *list, int index);