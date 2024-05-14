#include <bits/stdc++.h>
using namespace std;

#define numProcess 5
#define numResources 3
  
int current[numProcess][numResources] = { { 0, 1, 0 }, 
                     { 2, 0, 0 }, 
                     { 3, 0, 2 }, 
                     { 2, 1, 1 }, 
                     { 0, 0, 2 } }; 

int maxDemand[numProcess][numResources] = { { 7, 5, 3 }, 
                   { 3, 2, 2 }, 
                   { 9, 0, 2 }, 
                   { 2, 2, 2 }, 
                   { 4, 3, 3 } }; 

int available[numResources] = { 3, 3, 2 }; 

int main()
{
bool finish[numProcess];

for(int i=0; i<numProcess; i++)
{
    finish[i]= false;
}

int need[numProcess][numResources];
  for (int i = 0; i < numProcess; i++) {
    for (int j = 0; j < numResources; j++)
      need[i][j] = maxDemand[i][j] - current[i][j];
  }

int sequnce[numProcess], seq_index=0;

for(int m=0; m<numProcess; m++)
{
    for(int i=0; i<numProcess; i++)
    {
        if(finish[i]== false)
        {
            bool flag = true; // true -> can allocate resource to this process
            for(int j=0; j<numResources; j++)
            {
                if(need[i][j] > available[j])
                {
                    flag= false;
                    break;
                }
            }

            if(flag)
            {
                sequnce[seq_index]= i;
                seq_index++;
                for(int k=0; k<numResources; k++)
                {
                    available[k] += current[i][k];
                    finish[i]= true;
                }
            }
        }
    }
}
 
bool isSafe= true;
  
for(int i=0; i<numProcess; i++)
{
    if(finish[i]==false)
    {
        isSafe= false;
        cout << "The given sequence is not safe";
        break;
    }
}

if(isSafe= true)
{
    cout << "This is a safe Sequence: " << endl;
    for (int i = 0; i < numProcess-1; i++)
        cout << "P" << sequnce[i] << " -> ";
    cout << "P" << sequnce[numProcess - 1] <<endl;
  }

return (0);

}

