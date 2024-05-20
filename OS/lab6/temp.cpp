#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int startTime;
    int finishTime;
    int waitingTime;
    int turnaroundTime;
};

struct ComparePriority {
    bool operator()(const Process& p1, const Process& p2) {
        if (p1.priority == p2.priority) {
            return p1.arrivalTime > p2.arrivalTime;
        }
        return p1.priority > p2.priority;
    }
};

void priorityScheduling(vector<Process>& processes) {
    int numprocess = processes.size();

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    priority_queue<Process, vector<Process>, ComparePriority> pq;

    int currentTime = 0;
    int completed = 0;
    int i = 0;

    while (completed != numprocess) {
        while (i < numprocess && processes[i].arrivalTime <= currentTime) {
            pq.push(processes[i]);
            i++;
        }

        if (!pq.empty()) {
            Process current = pq.top();
            pq.pop();

            if (current.startTime == -1) {
                current.startTime = currentTime;
            }

            current.remainingTime--;
            currentTime++;

            if (current.remainingTime == 0) {
                current.finishTime = currentTime;
                current.turnaroundTime = current.finishTime - current.arrivalTime;
                current.waitingTime = current.turnaroundTime - current.burstTime;
                cout << "Process " << current.id << " completed at time " << currentTime << endl;
                completed++;
            } else {
                pq.push(current);
            }
        } else {
            currentTime++;
        }
    }

    cout << "Gantt chart:" << endl << endl;
    cout << "|";
    for (int i = 0; i < numprocess; i++) {
        if (i == 0) {
            cout << processes[i].arrivalTime << "|---p" << processes[i].id << "---|" << processes[i].finishTime;
        } else if (processes[i].finishTime - processes[i - 1].finishTime == processes[i].burstTime) {
            cout << "|---p" << processes[i].id << "---|" << processes[i].finishTime;
        } else {
            cout << "|---#---|" << processes[i].startTime;
            cout << "|---p" << processes[i].id << "---|" << processes[i].finishTime;
        }
    }
    cout << "|" << endl << endl;

    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;

    cout << "Process\tTurnaround Waiting\n";
    for (const auto& p : processes) {
        cout << p.id << "\t  " << p.turnaroundTime << "\t     "
             << p.waitingTime << '\n';
        totalTurnaroundTime += p.turnaroundTime;
        totalWaitingTime += p.waitingTime;
    }

    cout << "Average Turnaround Time: " << totalTurnaroundTime / numprocess << '\n';
    cout << "Average Waiting Time: " << totalWaitingTime / numprocess << '\n';
}

int main() {
    vector<Process> processes;

    int numProcesses;
    freopen("input.txt", "r", stdin);
    cin >> numProcesses;

    for (int i = 0; i < numProcesses; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        Process p;
        p.id = i;
        p.burstTime = a;
        p.remainingTime = a;
        p.priority = b;
        p.arrivalTime = c;
        p.startTime = -1;
        p.finishTime = -1;
        p.waitingTime = 0;
        p.turnaroundTime = 0;

        processes.push_back(p);
    }

    priorityScheduling(processes);

    return 0;
}
