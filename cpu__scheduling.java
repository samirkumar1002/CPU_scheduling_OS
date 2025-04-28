import java.util.*;

class Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int priority;

    Process(int pid, int arrivalTime, int burstTime) {
        this.pid = pid;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
    }
}

public class CPUScheduler {

    static void priorityBased(Process[] proc, int n) {
        Scanner sc = new Scanner(System.in);
        for (int i = 0; i < n; i++) {
            System.out.print("Enter the priority for Process " + proc[i].pid + ": ");
            proc[i].priority = sc.nextInt();
        }

        Arrays.sort(proc, (a, b) -> {
            if (a.priority == b.priority)
                return Integer.compare(a.arrivalTime, b.arrivalTime);
            return Integer.compare(a.priority, b.priority);
        });

        int currentTime = 0;
        for (int i = 0; i < n; i++) {
            if (currentTime < proc[i].arrivalTime) {
                currentTime = proc[i].arrivalTime;
            }
            proc[i].completionTime = currentTime + proc[i].burstTime;
            proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
            proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
            currentTime = proc[i].completionTime;
        }

        System.out.println("\nPriority-Based Scheduling Results:");
        System.out.println("PID\tPriority\tArrival\tBurst\tCompletion\tTurnaround\tWaiting");
        for (Process p : proc) {
            System.out.println(p.pid + "\t" + p.priority + "\t\t" + p.arrivalTime + "\t" + p.burstTime + "\t" + p.completionTime + "\t\t" + p.turnaroundTime + "\t\t" + p.waitingTime);
        }
    }

    static void FCFS(Process[] proc, int n) {
        Arrays.sort(proc, Comparator.comparingInt(a -> a.arrivalTime));

        int currentTime = 0;
        for (int i = 0; i < n; i++) {
            if (currentTime < proc[i].arrivalTime) {
                currentTime = proc[i].arrivalTime;
            }
            proc[i].completionTime = currentTime + proc[i].burstTime;
            proc[i].turnaroundTime = proc[i].completionTime - proc[i].arrivalTime;
            proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
            currentTime = proc[i].completionTime;
        }

        System.out.println("\nFCFS Scheduling Results:");
        System.out.println("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting");
        for (Process p : proc) {
            System.out.println(p.pid + "\t" + p.arrivalTime + "\t" + p.burstTime + "\t" + p.completionTime + "\t\t" + p.turnaroundTime + "\t\t" + p.waitingTime);
        }
    }

    static void SJFPreemptive(Process[] proc, int n) {
        int completed = 0, currentTime = 0;
        boolean[] isCompleted = new boolean[n];
        int[] burstRemaining = new int[n];
        for (int i = 0; i < n; i++) burstRemaining[i] = proc[i].burstTime;

        while (completed < n) {
            int minBurst = Integer.MAX_VALUE, idx = -1;

            for (int i = 0; i < n; i++) {
                if (proc[i].arrivalTime <= currentTime && !isCompleted[i] && burstRemaining[i] < minBurst) {
                    minBurst = burstRemaining[i];
                    idx = i;
                }
            }

            if (idx != -1) {
                burstRemaining[idx]--;
                currentTime++;
                if (burstRemaining[idx] == 0) {
                    completed++;
                    isCompleted[idx] = true;
                    proc[idx].completionTime = currentTime;
                    proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
                    proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
                }
            } else {
                currentTime++;
            }
        }

        System.out.println("\nSJF Preemptive Scheduling Results:");
        System.out.println("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting");
        for (Process p : proc) {
            System.out.println(p.pid + "\t" + p.arrivalTime + "\t" + p.burstTime + "\t" + p.completionTime + "\t\t" + p.turnaroundTime + "\t\t" + p.waitingTime);
        }
    }

    static void SJFNonPreemptive(Process[] proc, int n) {
        boolean[] isCompleted = new boolean[n];
        int completed = 0, currentTime = 0;

        while (completed < n) {
            int minBurst = Integer.MAX_VALUE, idx = -1;

            for (int i = 0; i < n; i++) {
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
                currentTime++;
            }
        }

        System.out.println("\nSJF Non-Preemptive Scheduling Results:");
        System.out.println("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting");
        for (Process p : proc) {
            System.out.println(p.pid + "\t" + p.arrivalTime + "\t" + p.burstTime + "\t" + p.completionTime + "\t\t" + p.turnaroundTime + "\t\t" + p.waitingTime);
        }
    }

    static void roundRobin(Process[] proc, int n, int quantum) {
        int[] burstRemaining = new int[n];
        for (int i = 0; i < n; i++) burstRemaining[i] = proc[i].burstTime;

        int currentTime = 0;
        Queue<Integer> queue = new LinkedList<>();
        for (int i = 0; i < n; i++) queue.add(i);

        while (!queue.isEmpty()) {
            int idx = queue.poll();

            if (proc[idx].arrivalTime <= currentTime) {
                if (burstRemaining[idx] > quantum) {
                    currentTime += quantum;
                    burstRemaining[idx] -= quantum;
                    queue.add(idx);
                } else {
                    currentTime += burstRemaining[idx];
                    burstRemaining[idx] = 0;
                    proc[idx].completionTime = currentTime;
                    proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
                    proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
                }
            } else {
                currentTime++;
                queue.add(idx);
            }
        }

        System.out.println("\nRound Robin Scheduling Results (Quantum = " + quantum + "):");
        System.out.println("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting");
        for (Process p : proc) {
            System.out.println(p.pid + "\t" + p.arrivalTime + "\t" + p.burstTime + "\t" + p.completionTime + "\t\t" + p.turnaroundTime + "\t\t" + p.waitingTime);
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Welcome to our CPU order processing application");
        System.out.print("Enter the number of processes: ");
        int n = sc.nextInt();
        Process[] proc = new Process[n];

        for (int i = 0; i < n; i++) {
            System.out.print("Process id: ");
            int pid = sc.nextInt();
            System.out.print("Process arrival time: ");
            int at = sc.nextInt();
            System.out.print("Process burst time: ");
            int bt = sc.nextInt();
            proc[i] = new Process(pid, at, bt);
        }

        while (true) {
            System.out.println("\nChoose the algorithm:\n 1.FCFS\n 2.SJF Preemptive\n 3.SJF Non-Preemptive\n 4.Round Robin\n 5.Priority Based\n 6.Exit");
            int choice = sc.nextInt();
            switch (choice) {
                case 1:
                    FCFS(proc, n);
                    break;
                case 2:
                    SJFPreemptive(proc, n);
                    break;
                case 3:
                    SJFNonPreemptive(proc, n);
                    break;
                case 4:
                    System.out.print("Enter the value of Quantum: ");
                    int quantum = sc.nextInt();
                    roundRobin(proc, n, quantum);
                    break;
                case 5:
                    priorityBased(proc, n);
                    break;
                case 6:
                    System.out.println("Exiting...");
                    sc.close();
                    return;
                default:
                    System.out.println("Invalid choice");
            }
        }
    }
}
