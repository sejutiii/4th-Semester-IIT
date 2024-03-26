#include<bits/stdc++.h>
using namespace std;

int main()
{
    int numProcesses;
    vector<int> burstTime, priority, arrivalTime, remaining;
    freopen("input2.txt","r",stdin);

    cin >> numProcesses;
    
    for(int i=0; i<numProcesses; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        burstTime.push_back(a);
        remaining.push_back(a);
        priority.push_back(b);
        arrivalTime.push_back(c);
    }

    int quantum;
   // cout << "Enter the time quantum: ";
    cin >> quantum;

    vector<pair<int, int>> gantt;

    int finishTime[numProcesses];
    int startTime= arrivalTime[0];

    int time=0;

    bool flag= true;
    while (flag)
    {
        for(int i=0; i<numProcesses; i++)
        {
            pair <int, int> temp;
            if(arrivalTime[i] > time){
                bool check= true;
                for(int j=0; j<i; j++)
                {
                    if(remaining[j] != 0)
                    {
                        check= false;
                        break;
                    }
                }
                if(!check) break;
                int val;
                val = min (quantum, arrivalTime[i]-time);
                temp.first= -1;
                temp.second= val;
                gantt.push_back(temp);
                time += val;
                continue;
            }

            if (remaining[i]==0) continue;
            else if(remaining[i] >= quantum)
            {
                temp.first= i;
                temp.second= quantum;
                gantt.push_back(temp);
                remaining[i] -= quantum;
                time += quantum;
                if(remaining[i]==0)
                {
                finishTime[i]= time;
                }
            }
            else
            {
                temp.first= i;
                temp.second= remaining[i];
                gantt.push_back(temp);
                time += remaining[i];
                finishTime[i]= time;
                remaining[i]=0;
            }
        }

        int i;
        for(i=0; i<numProcesses; i++)
        {
            if(remaining[i] != 0) break;
        }
        if(i == numProcesses) flag= false;
    }

    cout << "Gantt chart: " << endl;
    cout << "|" << startTime;
    time=0;
    for(auto p: gantt)
    {
        cout << "|---";
        if(p.first == -1) cout << "#";
        else cout << "P" << p.first+1;
        time += p.second;
        cout << "---|"<<time;
    }
    cout<< "|" << endl << endl;

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