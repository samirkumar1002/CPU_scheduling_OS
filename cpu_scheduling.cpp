#include <bits/stdc++.h>
using namespace std ;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int priority; // Add this field for priority
};

void Priority_based(Process proc[], int n_process) {
    // Take priorities as input
    for (int i = 0; i < n_process; i++) {
        cout << "Enter the priority for Process " << proc[i].pid << ": ";
        cin >> proc[i].priority;
    }

    // Sort processes based on priority (higher priority = smaller number)
    // If priorities are equal, sort by arrival time
    sort(proc, proc + n_process, [](Process a, Process b) {
        if (a.priority == b.priority) 
            return a.arrivalTime < b.arrivalTime;
        return a.priority < b.priority;
    });

    // Initialize times
    int currentTime = 0;
    for (int i = 0; i < n_process; i++) {
        if (currentTime < proc[i].arrivalTime) {
            currentTime = proc[i].arrivalTime; // CPU idle until the process arrives
        }
        proc[i].completionTime = currentTime + proc[i].burstTime;
        proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
        currentTime = proc[i].completionTime;
    }

    // Print results
    cout << "\nPriority-Based Scheduling Results:\n";
    cout << "PID\tPriority\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n_process; i++) {
        cout << proc[i].pid << "\t" << proc[i].priority << "\t\t"
             << proc[i].arrivalTime << "\t" << proc[i].burstTime << "\t"
             << proc[i].completionTime << "\t\t" << proc[i].turnaroundTime << "\t\t"
             << proc[i].waitingTime << endl;
    }
}

void FCFS(Process proc[], int n_process) {
    // Sort processes based on arrival time
    sort(proc, proc + n_process, [](Process a, Process b) {
        return a.arrivalTime < b.arrivalTime;
    });

    // Initialize times
    int currentTime = 0;
    for (int i = 0; i < n_process; i++) {
        if (currentTime < proc[i].arrivalTime) {
            currentTime = proc[i].arrivalTime; // CPU idle until the process arrives
        }
        proc[i].completionTime = currentTime + proc[i].burstTime;
        proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
        proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
        currentTime = proc[i].completionTime;
    }

    // Print results
    cout << "\nFCFS Scheduling Results:\n";
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n_process; i++) {
        cout << proc[i].pid << "\t" << proc[i].arrivalTime << "\t" << proc[i].burstTime << "\t"
             << proc[i].completionTime << "\t\t" << proc[i].turnaroundTime << "\t\t"
             << proc[i].waitingTime << endl;
    }
}

void SJF_Preemptive(Process proc[], int n_process) {
    int completed = 0, currentTime = 0;
    vector<bool> isCompleted(n_process, false);
    int burstRemaining[n_process];
    for (int i = 0; i < n_process; i++) burstRemaining[i] = proc[i].burstTime;

    while (completed < n_process) {
        int minBurst = INT_MAX, idx = -1;

        // Find the process with the smallest remaining burst time
        for (int i = 0; i < n_process; i++) {
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i] && burstRemaining[i] < minBurst) {
                minBurst = burstRemaining[i];
                idx = i;
            }
        }

        if (idx != -1) {
            burstRemaining[idx]--;
            currentTime++;

            if (burstRemaining[idx] == 0) { // Process completed
                completed++;
                isCompleted[idx] = true;
                proc[idx].completionTime = currentTime;
                proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
                proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
            }
        } else {
            currentTime++; // Idle time if no process is ready
        }
    }

    // Print results
    cout << "\nSJF Preemptive Scheduling Results:\n";
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n_process; i++) {
        cout << proc[i].pid << "\t" << proc[i].arrivalTime << "\t" << proc[i].burstTime << "\t"
             << proc[i].completionTime << "\t\t" << proc[i].turnaroundTime << "\t\t"
             << proc[i].waitingTime << endl;
    }
}

void SJF_NonPreemptive(Process proc[], int n_process) {
    vector<bool> isCompleted(n_process, false);
    int completed = 0, currentTime = 0;

    while (completed < n_process) {
        int minBurst = INT_MAX, idx = -1;

        // Find the process with the smallest burst time
        for (int i = 0; i < n_process; i++) {
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i] && proc[i].burstTime < minBurst) {
                minBurst = proc[i].burstTime;
                idx = i;
            }
        }

        if (idx != -1) {
            currentTime += proc[idx].burstTime;
            proc[idx].completionTime = currentTime;
            proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
            proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
            isCompleted[idx] = true;
            completed++;
        } else {
            currentTime++; // Idle time if no process is ready
        }
    }

    // Print results
    cout << "\nSJF Non-Preemptive Scheduling Results:\n";
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n_process; i++) {
        cout << proc[i].pid << "\t" << proc[i].arrivalTime << "\t" << proc[i].burstTime << "\t"
             << proc[i].completionTime << "\t\t" << proc[i].turnaroundTime << "\t\t"
             << proc[i].waitingTime << endl;
    }
}

void Round_Robin(Process proc[], int n_process, int quantum) {
    int burstRemaining[n_process];
    for (int i = 0; i < n_process; i++) burstRemaining[i] = proc[i].burstTime;

    int currentTime = 0;
    queue<int> q;
    for (int i = 0; i < n_process; i++) q.push(i);

    while (!q.empty()) {
        int idx = q.front();
        q.pop();

        if (proc[idx].arrivalTime <= currentTime) {
            if (burstRemaining[idx] > quantum) {
                currentTime += quantum;
                burstRemaining[idx] -= quantum;
                q.push(idx); // Process goes to the back of the queue
            } else {
                currentTime += burstRemaining[idx];
                burstRemaining[idx] = 0;
                proc[idx].completionTime = currentTime;
                proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
                proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
            }
        } else {
            currentTime++; // CPU is idle
            q.push(idx);
        }
    }

    // Print results
    cout << "\nRound Robin Scheduling Results (Quantum = " << quantum << "):\n";
    cout << "PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n_process; i++) {
        cout << proc[i].pid << "\t" << proc[i].arrivalTime << "\t" << proc[i].burstTime << "\t"
             << proc[i].completionTime << "\t\t" << proc[i].turnaroundTime << "\t\t"
             << proc[i].waitingTime << endl;
    }
}

void MLQ(Process proc[], int n_process) {
    vector<Process> queue1; // Higher-priority queue (Round Robin)
    vector<Process> queue2; // Lower-priority queue (FCFS)

    // Input the priority of each process to determine which queue it belongs to
    for (int i = 0; i < n_process; i++) {
        int priorityLevel;
        cout << "Enter priority level (1 = High, 2 = Low) for Process " << proc[i].pid << ": ";
        cin >> priorityLevel;
        if (priorityLevel == 1)
            queue1.push_back(proc[i]);
        else
            queue2.push_back(proc[i]);
    }

    // Round Robin for Queue 1
    int quantum = 2; // Example quantum value for Round Robin
    cout << "\nScheduling Queue 1 (Round Robin with quantum = " << quantum << "):\n";
    Round_Robin(queue1.data(), queue1.size(), quantum);

    // FCFS for Queue 2
    cout << "\nScheduling Queue 2 (FCFS):\n";
    FCFS(queue2.data(), queue2.size());

    // Combine and print results
    cout << "\nMulti-Level Queue Scheduling Results:\n";
    cout << "PID\tQueue\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";

    for (const auto &p : queue1) {
        cout << p.pid << "\t1\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << endl;
    }

    for (const auto &p : queue2) {
        cout << p.pid << "\t2\t" << p.arrivalTime << "\t" << p.burstTime << "\t"
             << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << endl;
    }
}

void MLFQ(Process proc[], int n_process) {
    vector<Process> queue1; // Highest priority (RR with Quantum = 2)
    vector<Process> queue2; // Medium priority (RR with Quantum = 4)
    vector<Process> queue3; // Lowest priority (FCFS)

    int burstRemaining[n_process];
    for (int i = 0; i < n_process; i++) {
        burstRemaining[i] = proc[i].burstTime;
        queue1.push_back(proc[i]); // All processes start in Queue 1
    }

    int currentTime = 0;

    // Function for Round Robin Scheduling
    auto roundRobin = [&](vector<Process>& queue, int quantum) {
        vector<Process> nextQueue;
        for (auto& p : queue) {
            int idx = p.pid - 1; // Get index based on PID
            if (burstRemaining[idx] > quantum) {
                currentTime += quantum;
                burstRemaining[idx] -= quantum;
                p.arrivalTime = currentTime; // Update arrival time for next queue
                nextQueue.push_back(p);     // Process moves to the next queue
            } else {
                currentTime += burstRemaining[idx];
                burstRemaining[idx] = 0;
                p.completionTime = currentTime;
                p.turnaroundTime = p.completionTime - p.arrivalTime;
                p.waitingTime = p.turnaroundTime - p.burstTime;
            }
        }
        queue = nextQueue; // Update the current queue with processes that remain
    };

    // Step 1: Process Queue 1 with RR (Quantum = 2)
    cout << "\nScheduling Queue 1 (Round Robin with Quantum = 2):\n";
    while (!queue1.empty()) {
        roundRobin(queue1, 2);
        queue2.insert(queue2.end(), queue1.begin(), queue1.end());
        queue1.clear();
    }

    // Step 2: Process Queue 2 with RR (Quantum = 4)
    cout << "\nScheduling Queue 2 (Round Robin with Quantum = 4):\n";
    while (!queue2.empty()) {
        roundRobin(queue2, 4);
        queue3.insert(queue3.end(), queue2.begin(), queue2.end());
        queue2.clear();
    }

    // Step 3: Process Queue 3 with FCFS
    cout << "\nScheduling Queue 3 (FCFS):\n";
    if (!queue3.empty()) {
        sort(queue3.begin(), queue3.end(), [](Process a, Process b) {
            return a.arrivalTime < b.arrivalTime;
        });

        for (auto& p : queue3) {
            int idx = p.pid - 1;
            currentTime = max(currentTime, p.arrivalTime) + burstRemaining[idx];
            burstRemaining[idx] = 0;
            p.completionTime = currentTime;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
        }
    }

    // Combine and print results
    cout << "\nMulti-Level Feedback Queue Scheduling Results:\n";
    cout << "PID\tQueue\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";

    for (int i = 0; i < n_process; i++) {
        int queueLevel = (burstRemaining[i] == 0 && proc[i].completionTime <= 2) ? 1 :
                         (burstRemaining[i] == 0 && proc[i].completionTime <= 4) ? 2 : 3;

        cout << proc[i].pid << "\t" << queueLevel << "\t" << proc[i].arrivalTime << "\t"
             << proc[i].burstTime << "\t" << proc[i].completionTime << "\t\t"
             << proc[i].turnaroundTime << "\t\t" << proc[i].waitingTime << endl;
    }
}



int main(){
    cout << "Welcome to our CPU order processing application " << endl ;
    cout << "Enter the number of processes :\n" ;
    int n_process ;
    cin >> n_process ;
    Process proc[n_process];

    for(int i=0;i<n_process;i++){
        cout << "Process id :";
        cin >> proc[i].pid ;
        cout << "Process arrival time :";
        cin >> proc[i].arrivalTime ;
        cout << "Process burst time :";
        cin >> proc[i].burstTime ;
    }

    while(true){
    cout << "Choose the algorithm : \n 1.FCFS\n 2.SJF\n 3.SRT\n 4.Round Robin\n 5.Priority Based\n 6.MLQ\n 7.MLFQ\n8.Exit" ;
    int choose ;
    cin >> choose ;
    switch (choose)
    {
    case 1:
        FCFS(proc,n_process);
        break;
    case 2:
        SJF_Preemptive(proc,n_process);
        break;
    case 3:
        SJF_NonPreemptive(proc,n_process);
        break;
    case 4:
        cout << "Enter the value of Quantum :" ;
        int quantum ;
        cin >> quantum ;
        Round_Robin(proc,n_process,quantum);
        break;
    case 5:
        Priority_based(proc,n_process);
        break;
    case 6:
        MLQ(proc,n_process) ;
        break;
    
    case 7:
        MLFQ(proc,n_process) ;
        break;
    
    default:
        cout<< "Invalid choice" << endl ;
        break;
    }
    if(choose==8) break ;
    }
    cout << "exitcode" ;
    int x ;
    cin >> x ;

    return 0;
}