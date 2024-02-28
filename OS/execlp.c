#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h> 
int main() {
printf("About to run ls\n");
execlp("ls", "ls", "-aF", "/", (char*)0);
perror("execlp"); 
exit(1);
}
