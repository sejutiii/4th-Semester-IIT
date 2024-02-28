#include<bits/stdc++.h>
using namespace std;

int main()
{
    int numProcesses;
    vector<int> burstTime, priority, arrivalTime;
    freopen("input2.txt","r",stdin);

    cin >> numProcesses;
    
    for(int i=0; i<numProcesses; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        burstTime.push_back(a);
        priority.push_back(b);
        arrivalTime.push_back(c);
    }

    // for(int i=0; i<numProcesses; i++)
    // {
    //     cout << burstTime[i] << " " << priority[i] << endl;
    // }

    int finishTime[numProcesses];
    int startTime[numProcesses];
    
    for(int i=0; i<numProcesses; i++)
    {
        if(i==0)
        {
            startTime[i]= arrivalTime[i];
            finishTime[i]= arrivalTime[i]+ burstTime[i];
        }
        else
        {
            startTime[i]= max(arrivalTime[i], finishTime[i-1]);
            finishTime[i]= startTime[i]+ burstTime[i];
        }
    }

    for(int i=0; i<numProcesses; i++)
    {
       cout << startTime[i] << " p" << i << " " << finishTime[i] << "\t";
    }
}