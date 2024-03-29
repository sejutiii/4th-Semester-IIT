#include<bits/stdc++.h>
using namespace std;

int main()
{
    int numProcesses;
    vector<int> burstTime, priority, arrivalTime;
    freopen("input.txt","r",stdin);

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
            // precondition: assumes that the processes are sorted based on arrival time
            startTime[i]= max(arrivalTime[i], finishTime[i-1]);
            finishTime[i]= startTime[i]+ burstTime[i];
        }
    }

// Gantt chart 

    cout << "Gantt chart:" << endl << endl;
    cout << "|" ;
    for(int i=0; i<numProcesses; i++)
    {
      if(i==0)
      {
        cout << startTime[i] << "|---p" << i+1 << "---|" << finishTime[i] ;
      }
      else if(startTime[i]==finishTime[i-1])
        {
        cout << "|---p" << i+1 << "---|" << finishTime[i] ;
        }
        else
        {
            cout << "|---#---|" << startTime[i];
            cout << "|---p" << i+1 << "---|" << finishTime[i] ;
        }
    }
    cout << "|" << endl << endl;

    // Turnaround time and waiting time 
    
    int turnaround[numProcesses], waiting_time[numProcesses];
    for(int i=0; i<numProcesses; i++)
    {
        turnaround[i]= finishTime[i]- arrivalTime[i];
        waiting_time[i]= turnaround[i]- burstTime[i];
    }

    int total=0;
    cout << "Turnaround time of each process: " << endl;
    for(int i=0; i<numProcesses; i++)
    {
        cout << "P" << i+1 << ": " << turnaround[i] << endl;
        total += turnaround[i];
    }

    cout << "Average turnaround time: " << total/numProcesses << endl;

    total=0;
    cout << "Waiting time of each process: " << endl;
    for(int i=0; i<numProcesses; i++)
    {
        cout << "P" << i+1 << ": " << waiting_time[i] << endl;
        total += waiting_time[i];
    }

    cout << "Average waiting time: " << total/numProcesses << endl;
}