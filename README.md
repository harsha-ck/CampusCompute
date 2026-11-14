# CampusCompute – Intelligent Job Scheduling and Resource Management

## 1. Project Overview

CampusCompute is a C-based Operating Systems mini-project that demonstrates CPU scheduling, process synchronization, inter-process communication, deadlock avoidance, process management, and resource management using POSIX system calls.

The project combines multiple Operating Systems concepts into one interactive command-line application.

## 2. Features Implemented

### FR1 – Job Management
- Create jobs with unique job IDs.
- Accept arrival time, burst time, and priority.
- Initialize job execution and scheduling information.
- Display job details.

### FR2 – CPU Scheduling Algorithms
Implements three CPU scheduling algorithms:

- **First Come First Serve (FCFS)**
- **Round Robin (RR)** – accepts a user-defined time quantum.
- **Non-Preemptive Priority Scheduling** – smaller priority number represents higher priority.

Displays scheduling information, including:
- Gantt chart
- Completion Time (CT)
- Turnaround Time (TAT)
- Waiting Time (WT)
- Average Turnaround Time
- Average Waiting Time

A comparison of the three algorithms is also displayed.

### FR3 – Producer–Consumer Synchronization
- Uses POSIX threads.
- Implements a bounded circular buffer.
- Uses a mutex for mutual exclusion.
- Uses condition variables to synchronize producer and consumer threads.
- Logs produced and consumed items in `logs/producer_consumer.log`.

### FR4 – Inter-Process Communication
- Uses POSIX shared memory.
- Uses a named POSIX semaphore for synchronization.
- Demonstrates communication between parent and child processes.
- Cleans up shared memory and semaphore resources after execution.

### FR5 – Banker's Algorithm
- Calculates the Need matrix.
- Checks whether the system is in a safe state.
- Displays a safe sequence when one exists.
- Demonstrates an unsafe system state.

### FR6 – Process Management
- Creates child processes using `fork()`.
- Uses `waitpid()` to wait for child-process termination.
- Demonstrates normal child-process execution.
- Demonstrates a simulated child-process failure and detects its exit status.

### FR7 – Resource Management
- Uses `getrlimit()` to retrieve resource limits.
- Uses `setrlimit()` to modify the file-descriptor soft limit.
- Verifies the updated limit.
- Restores the original resource limit.

### FR8 – Command-Line Interface
- Provides an interactive terminal interface.
- Accepts job information and the Round Robin time quantum.
- Runs the integrated demonstrations and displays their results.

## 3. Technologies Used

- Programming Language: C
- Operating System: Linux (Ubuntu)
- Compiler: GCC
- Build System: GNU Make
- POSIX Threads (`pthread`)
- POSIX Shared Memory
- POSIX Semaphores
- Linux process and resource-management system calls

## 4. Project Structure

```text
CampusCompute/
│
├── include/
│   ├── banker.h
│   ├── ipc.h
│   ├── job.h
│   ├── process.h
│   ├── producer_consumer.h
│   ├── resource.h
│   └── scheduler.h
│
├── src/
│   ├── banker.c
│   ├── ipc.c
│   ├── job.c
│   ├── main.c
│   ├── process.c
│   ├── producer_consumer.c
│   ├── resource.c
│   └── scheduler.c
│
├── logs/
│   └── producer_consumer.log
│
├── Makefile
└── README.md
```

## 5. Requirements

The following tools are required:

- GCC compiler
- GNU Make
- Linux environment (Ubuntu recommended)
- POSIX threads and POSIX IPC support

## 6. Build Instructions

Clone the repository:

```bash
git clone https://github.com/harsha-ck/CampusCompute.git
```

Navigate into the project directory:

```bash
cd CampusCompute
```

Compile the project:

```bash
make
```

Clean generated executable files:

```bash
make clean
```

## 7. Running the Project

Run the application using:

```bash
make run
```

The program asks for:
1. Number of jobs.
2. Arrival time, burst time, and priority for each job.
3. Round Robin time quantum.

It then executes the scheduling algorithms and the remaining demonstrations.

## 8. Example Input

```text
Enter number of jobs: 3

Job 1:
Arrival Time: 0
Burst Time: 5
Priority: 3

Job 2:
Arrival Time: 0
Burst Time: 4
Priority: 2

Job 3:
Arrival Time: 0
Burst Time: 3
Priority: 1

Enter Time Quantum: 2
```

The application displays scheduling results, producer–consumer activity, shared-memory communication, Banker’s Algorithm results, process-management results, and resource-limit information.

## 9. Team Contributions

| Team Member | Responsibilities |
|---|---|
| Harsha C K | FR1 – Job Management, FR2 – CPU Scheduling, FR3 – Producer–Consumer Synchronization, FR4 – Shared Memory and Semaphore |
| Jayanth | FR5 – Banker's Algorithm, FR6 – Process Management, FR7 – Resource Management |
| Both Members | Integration, compilation, testing, debugging, and documentation |

## 10. Conclusion

CampusCompute demonstrates important Operating Systems concepts through practical C implementations on Linux. It integrates CPU scheduling, synchronization, inter-process communication, deadlock avoidance, process management, and resource management into a single command-line application.
