# CPU Scheduling Simulation

## Overview
This project simulates various CPU scheduling algorithms to understand and analyze their behavior. It allows users to input process details and choose from different algorithms to calculate scheduling parameters such as completion time, turnaround time, and waiting time.

## Features
- Supports the following scheduling algorithms:
  1. **First Come First Serve (FCFS)**
  2. **Shortest Job First (SJF - Non-Preemptive)**
  3. **Shortest Remaining Time (SRT - Preemptive)**
  4. **Round Robin (RR)**
  5. **Priority-Based Scheduling**
  6. **Multi-Level Queue (MLQ) Scheduling**
  7. **Multi-Level Feedback Queue (MLFQ) Scheduling**
- Computes essential metrics:
  - **Completion Time**
  - **Turnaround Time**
  - **Waiting Time**
- Allows interactive input for process details and algorithm selection.

## Installation and Usage

### Prerequisites
- A C++ compiler (e.g., GCC)
- Basic knowledge of running C++ programs from the terminal/command line

### Compilation
1. Download or clone the repository.
2. Navigate to the directory containing `cpu_scheduling.cpp`.
3. Compile the program using the following command:
   ```bash
   g++ -o cpu_scheduling cpu_scheduling.cpp
   ```

### Running the Application
1. Execute the compiled program:
   ```bash
   ./cpu_scheduling
   ```
2. Follow the interactive prompts:
   - Enter the number of processes.
   - Provide details for each process (Process ID, Arrival Time, Burst Time).
   - Select a scheduling algorithm from the menu.
   - For Round Robin, specify the time quantum.
   - For Priority-Based or Multi-Level Queue Scheduling, specify priorities.
3. View the calculated scheduling results, including:
   - Completion Time
   - Turnaround Time
   - Waiting Time

### Input Format
- **Process ID:** A unique identifier for each process.
- **Arrival Time:** Time when the process enters the ready queue.
- **Burst Time:** Time required by the process for execution.

### Example Interaction
```
Welcome to our CPU order processing application
Enter the number of processes:
3
Process ID: 1
Process Arrival Time: 0
Process Burst Time: 5
Process ID: 2
Process Arrival Time: 1
Process Burst Time: 3
Process ID: 3
Process Arrival Time: 2
Process Burst Time: 8

Choose the algorithm: 
1. FCFS
2. SJF
3. SRT
4. Round Robin
5. Priority-Based
6. MLQ
7. MLFQ
8. Exit
```

## Scheduling Algorithms Explained

1. **First Come First Serve (FCFS):**
   - Processes are executed in the order they arrive.

2. **Shortest Job First (SJF):**
   - Selects the process with the smallest burst time.
   - Supports both preemptive and non-preemptive variants.

3. **Shortest Remaining Time (SRT):**
   - Preemptive variant of SJF.
   - A process with a shorter remaining burst time can interrupt the current process.

4. **Round Robin (RR):**
   - Each process is assigned a fixed time slice (quantum) for execution.
   - Ensures fairness and avoids starvation.

5. **Priority-Based Scheduling:**
   - Processes are executed based on priority (lower number indicates higher priority).
   - Tiebreaker: Arrival time.

6. **Multi-Level Queue (MLQ):**
   - Processes are assigned to different queues based on priority.
   - Queue 1 uses Round Robin; Queue 2 uses FCFS.

7. **Multi-Level Feedback Queue (MLFQ):**
   - Dynamic queues with varying time quanta.
   - Allows processes to move between queues based on execution history.

## Contributing
Feel free to fork the repository, make enhancements, and submit pull requests.

## Acknowledgments
- Inspired by operating system scheduling concepts.
- Educational purpose: Demonstrating various CPU scheduling algorithms.

**Author:** **Samir**

**College:** **NIT Silchar** 🎓
