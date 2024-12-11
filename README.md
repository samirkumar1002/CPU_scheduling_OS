<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CPU Scheduling Simulation</title>
</head>
<body>
    <header>
        <h1>CPU Scheduling Simulation</h1>
    </header>

    <section>
        <h2>Overview</h2>
        <p>
            This project simulates various CPU scheduling algorithms to understand and analyze their behavior. 
            It allows users to input process details and choose from different algorithms to calculate scheduling 
            parameters such as completion time, turnaround time, and waiting time.
        </p>
    </section>

    <section>
        <h2>Features</h2>
        <ul>
            <li>Supports the following scheduling algorithms:
                <ol>
                    <li>First Come First Serve (FCFS)</li>
                    <li>Shortest Job First (SJF - Non-Preemptive)</li>
                    <li>Shortest Remaining Time (SRT - Preemptive)</li>
                    <li>Round Robin (RR)</li>
                    <li>Priority-Based Scheduling</li>
                    <li>Multi-Level Queue (MLQ) Scheduling</li>
                    <li>Multi-Level Feedback Queue (MLFQ) Scheduling</li>
                </ol>
            </li>
            <li>Computes essential metrics:
                <ul>
                    <li>Completion Time</li>
                    <li>Turnaround Time</li>
                    <li>Waiting Time</li>
                </ul>
            </li>
            <li>Interactive input for process details and algorithm selection.</li>
        </ul>
    </section>

    <section>
        <h2>Installation and Usage</h2>

        <h3>Prerequisites</h3>
        <ul>
            <li>A C++ compiler (e.g., GCC)</li>
            <li>Basic knowledge of running C++ programs from the terminal/command line</li>
        </ul>

        <h3>Compilation</h3>
        <ol>
            <li>Download or clone the repository.</li>
            <li>Navigate to the directory containing <code>cpu_scheduling.cpp</code>.</li>
            <li>Compile the program using the following command:
                <pre><code>g++ -o cpu_scheduling cpu_scheduling.cpp</code></pre>
            </li>
        </ol>

        <h3>Running the Application</h3>
        <ol>
            <li>Execute the compiled program:
                <pre><code>./cpu_scheduling</code></pre>
            </li>
            <li>Follow the interactive prompts:
                <ul>
                    <li>Enter the number of processes.</li>
                    <li>Provide details for each process (Process ID, Arrival Time, Burst Time).</li>
                    <li>Select a scheduling algorithm from the menu.</li>
                    <li>For Round Robin, specify the time quantum.</li>
                    <li>For Priority-Based or Multi-Level Queue Scheduling, specify priorities.</li>
                </ul>
            </li>
            <li>View the calculated scheduling results, including:
                <ul>
                    <li>Completion Time</li>
                    <li>Turnaround Time</li>
                    <li>Waiting Time</li>
                </ul>
            </li>
        </ol>

        <h3>Input Format</h3>
        <ul>
            <li><strong>Process ID:</strong> A unique identifier for each process.</li>
            <li><strong>Arrival Time:</strong> Time when the process enters the ready queue.</li>
            <li><strong>Burst Time:</strong> Time required by the process for execution.</li>
        </ul>

        <h3>Example Interaction</h3>
        <pre>
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
        </pre>
    </section>

    <section>
        <h2>Scheduling Algorithms Explained</h2>
        <ol>
            <li><strong>First Come First Serve (FCFS):</strong> Processes are executed in the order they arrive.</li>
            <li><strong>Shortest Job First (SJF):</strong> Selects the process with the smallest burst time. Supports both preemptive and non-preemptive variants.</li>
            <li><strong>Shortest Remaining Time (SRT):</strong> Preemptive variant of SJF. A process with a shorter remaining burst time can interrupt the current process.</li>
            <li><strong>Round Robin (RR):</strong> Each process is assigned a fixed time slice (quantum) for execution. Ensures fairness and avoids starvation.</li>
            <li><strong>Priority-Based Scheduling:</strong> Processes are executed based on priority (lower number indicates higher priority). Tiebreaker: Arrival time.</li>
            <li><strong>Multi-Level Queue (MLQ):</strong> Processes are assigned to different queues based on priority. Queue 1 uses Round Robin; Queue 2 uses FCFS.</li>
            <li><strong>Multi-Level Feedback Queue (MLFQ):</strong> Dynamic queues with varying time quanta. Allows processes to move between queues based on execution history.</li>
        </ol>
    </section>

    <section>
        <h2>Contributing</h2>
        <p>
            Feel free to fork the repository, make enhancements, and submit pull requests.
        </p>
    </section>

    <section>
        <h2>License</h2>
        <p>
            This project is licensed under the MIT License. See <code>LICENSE</code> for details.
        </p>
    </section>

    <footer>
        <h2>Acknowledgments</h2>
        <p>
            Inspired by operating system scheduling concepts. Educational purpose: Demonstrating various CPU scheduling algorithms.
        </p>
    </footer>
</body>
</html>
