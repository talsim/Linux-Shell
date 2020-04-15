/*Executes the given command*/
/*Returns 0 if failed*/
int executeSingleCommand(cmdLine* pCmdLine);

/*Forks and executes the command on the child proccess*/
/*Returns 1 if it was successful, else, returns 0*/
int execute(cmdLine *line);

/*Changes the current working directoy*/
/*On success, returns zero. On error, -1 is returned.*/
int changeCwd(cmdLine *line);