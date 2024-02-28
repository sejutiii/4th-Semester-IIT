#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h> 

int main() 
{
//char *args[] = {"ls", "-aF", "/", 0}; 
char *args[] = {"pwd", 0}; 
char *env[] = { 0 }; 
printf("About to run /bin/pwd\n");
execve("/bin/pwd", args, env);
perror("execve"); 
exit(1);
}
