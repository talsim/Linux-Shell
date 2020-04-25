/*Changes the current working directoy*/
/*On success, returns zero. On error, -1 is returned.*/
int changeCwd(cmdLine *line);

/*Invokes the command in the history at the given index*/
/*Returns 0 on success, -1 on failure*/
int invokeCommandByIndex(List *list, int index);