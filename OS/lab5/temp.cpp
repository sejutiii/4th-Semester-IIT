#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int numProcesses;
    vector<int> burstTime, priority, arrivalTime;
    freopen("input.txt","r",stdin);
    cin >> numProcesses;

    for (int i = 0; i < numProcesses; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        burstTime.push_back(a);
        priority.push_back(b);
        arrivalTime.push_back(c);
    }

    // Initialize index_sorted array
    vector<int> index_sorted(numProcesses);
    for (int i = 0; i < numProcesses; i++) {
        index_sorted[i] = i;
    }

    int temp = 0;
    for (int i = 0; i < numProcesses; i++) {
        for (int j = i + 1; j < numProcesses; j++) {

            if ((arrivalTime[index_sorted[i]] >= arrivalTime[index_sorted[j]] || arrivalTime[index_sorted[j]] < temp) &&
                priority[index_sorted[i]] < priority[index_sorted[j]]) {
                cout << index_sorted[i]+1 << " " << index_sorted[j]+1 << endl;
                swap(index_sorted[i], index_sorted[j]);
    
            }
        }
        temp = max(temp, arrivalTime[index_sorted[i]])+ burstTime[index_sorted[i]];
    }

    for(int i=1; i<numProcesses; i++)
    {
        if(priority[index_sorted[i]]== priority[index_sorted[i-1]] && index_sorted[i-1] > index_sorted[i])
        {
            swap(index_sorted[i], index_sorted[i-1]);
        }
    }

    // Print sorted indexes
    for (int i = 0; i < numProcesses; i++) {
        cout << index_sorted[i] + 1 << "\t";
    }

    return 0;
}
