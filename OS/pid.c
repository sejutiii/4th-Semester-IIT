#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
printf("My process pid is %d\n", getpid());
printf("My parent's process pid is %d\n", getppid());
exit(0);
}
