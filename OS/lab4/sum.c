#include<stdio.h>
#include<unistd.h>

int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int sum=0;

    int pid= fork();
    if(pid==0)
    {
        for(int i=1; i<=n; i+=2)
        {
            sum += i;
        }
        printf("Sum Odd= %d\n", sum);
    }
    else
    {
        for(int i=2; i<=n; i+=2)
        {
            sum += i;
        }
        printf("Sum Even= %d\n", sum);
    }
    return 0;
}