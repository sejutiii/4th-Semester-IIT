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

// sorting based on the shortest job

    vector<int> index_sorted(numProcesses);
    for (int i = 0; i < numProcesses; i++) {
        index_sorted[i] = i;
    }

    // Sorting based on burst time and arrival time
    int temp = 0;
    for (int i = 0; i < numProcesses; i++) {
    //cout << "temp: " << temp << " i=" << i+1 << "   "<< endl;
        for (int j = i + 1; j < numProcesses; j++) {

            if ((arrivalTime[index_sorted[i]] >= arrivalTime[index_sorted[j]] || arrivalTime[index_sorted[j]] < temp) &&
                burstTime[index_sorted[i]] > burstTime[index_sorted[j]]) {
                swap(index_sorted[i], index_sorted[j]);
            }
        }
        temp = max(temp, arrivalTime[index_sorted[i]])+ burstTime[index_sorted[i]];
    }

    int finishTime[numProcesses];
    int startTime[numProcesses];
    
    for(int i=0; i<numProcesses; i++)
    {
        if(i==0)
        {
            startTime[i]= arrivalTime[index_sorted[i]];
            finishTime[i]= arrivalTime[index_sorted[i]]+ burstTime[index_sorted[i]];
        }
        else
        {
            // precondition: assumes that the processes are sorted based on arrival time
            startTime[i]= max(arrivalTime[index_sorted[i]], finishTime[i-1]);
            finishTime[i]= startTime[i]+ burstTime[index_sorted[i]];
        }
    }

// Gantt chart 

    cout << "Gantt chart:" << endl << endl;
    cout << "|" ;
    for(int i=0; i<numProcesses; i++)
    {
      if(i==0)
      {
        cout << startTime[i] << "|---p" << index_sorted[i]+1 << "---|" << finishTime[i] ;
      }
      else if(startTime[i]==finishTime[i-1])
        {
        cout << "|---p" << index_sorted[i]+1 << "---|" << finishTime[i] ;
        }
        else
        {
            cout << "|---#---|" << startTime[i];
            cout << "|---p" << index_sorted[i]+1 << "---|" << finishTime[i] ;
        }
    }
    cout << "|" << endl << endl;

    // Turnaround time and waiting time 
    
    int turnaround[numProcesses], waiting_time[numProcesses];
    for(int i=0; i<numProcesses; i++)
    {
        turnaround[i]= finishTime[i]- arrivalTime[index_sorted[i]];
        waiting_time[i]= turnaround[i]- burstTime[index_sorted[i]];
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