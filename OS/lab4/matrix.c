#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    int matA[3][2]= { 4, 1,
    2, 2,
    3, 4};
    int matB[2][3]= 
    {
        1, 2, 3,
        3, 2, 1};

    int row_A= 3, col_A=2, col_B=3;

    for(int i=0; i<row_A; i++)
    {
        printf("\n");
    
        for(int k=0; k<col_B; k++)
        {
            int pid= fork();
            if(pid==0)
            {
                int sum =0;
                for(int j=0; j<col_A; j++)
                {
                    sum += matA[i][j]* matB[j][k];
                }
                printf("%d\t", sum);
                exit(0);
            }
            else
            {
                wait(NULL);
            }
        }
    }
    printf("\n");
    return 0;

}