#include <stdio.h>
#include "../include/job.h"
#include "../include/scheduler.h"
#include "../include/producer_consumer.h"
#include "../include/ipc.h"
#include "../include/banker.h"
#include "../include/process.h"
#include "../include/resource.h"
int main()
{
    int n;

    printf("====================================\n");
    printf("       CAMPUS COMPUTE SYSTEM\n");
    printf("====================================\n");

    printf("\nEnter number of jobs: ");

    if(scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of jobs!\n");
        return 1;
    }

    Job jobs[n];

    create_jobs(jobs, n);

    display_jobs(jobs, n);

    int quantum;

printf("\nEnter Time Quantum: ");
scanf("%d", &quantum);

if(quantum <= 0)
{
    printf("Invalid time quantum!\n");
    return 1;
}
SchedulingResult fcfs_result;
SchedulingResult rr_result;
SchedulingResult priority_result;

fcfs_result = fcfs_schedule(jobs, n);

rr_result = round_robin_schedule(jobs, n, quantum);

priority_result = priority_schedule(jobs, n);

compare_scheduling(fcfs_result, rr_result, priority_result);

run_producer_consumer();

run_shared_memory_demo();

// FR5 - Banker's Algorithm
run_bankers_demo();

// FR6 - Process Management
run_process_demo();

// FR7 - Resource Management
run_resource_demo();

return 0;
}
