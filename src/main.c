#include <stdio.h>
#include "../include/job.h"
#include "../include/scheduler.h"
#include "../include/producer_consumer.h"
#include "../include/ipc.h"
#include "../include/banker.h"
#include "../include/process.h"
#include "../include/resource.h"

void run_scheduling(void)
{
    int n, quantum;

    printf("\nEnter number of jobs (1-99): ");

    if (scanf("%d", &n) != 1 || n <= 0 || n > 99)
    {
        printf("Invalid number of jobs!\n");
        return;
    }

    Job jobs[n];

    if (!create_jobs(jobs, n))
    {
        printf("Job creation failed!\n");
        return;
    }

    display_jobs(jobs, n);

    printf("\nEnter Time Quantum: ");

    if (scanf("%d", &quantum) != 1 || quantum <= 0)
    {
        printf("Invalid time quantum!\n");
        return;
    }

    SchedulingResult fcfs_result;
    SchedulingResult rr_result;
    SchedulingResult priority_result;

    fcfs_result = fcfs_schedule(jobs, n);
    rr_result = round_robin_schedule(jobs, n, quantum);
    priority_result = priority_schedule(jobs, n);

    compare_scheduling(fcfs_result, rr_result, priority_result);
}

void run_all_demos(void)
{
    printf("\n========== JOB SCHEDULING ==========\n");
    run_scheduling();

    printf("\n========== PRODUCER CONSUMER ==========\n");
    run_producer_consumer();

    printf("\n========== SHARED MEMORY IPC ==========\n");
    run_shared_memory_demo();

    printf("\n========== BANKER'S ALGORITHM ==========\n");
    run_bankers_demo();

    printf("\n========== PROCESS MANAGEMENT ==========\n");
    run_process_demo();

    printf("\n========== RESOURCE MANAGEMENT ==========\n");
    run_resource_demo();
}

int main(void)
{
    int choice;

    while (1)
    {
        printf("\n====================================\n");
        printf("       CAMPUS COMPUTE SYSTEM\n");
        printf("====================================\n");

        printf("1. Job Management and CPU Scheduling\n");
        printf("2. Producer-Consumer Synchronization\n");
        printf("3. Shared Memory IPC\n");
        printf("4. Banker's Algorithm\n");
        printf("5. Process Management\n");
        printf("6. Resource Management\n");
        printf("7. Run All Demonstrations\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Please enter a number.\n");
            return 1;
        }

        switch (choice)
        {
            case 1:
                run_scheduling();
                break;

            case 2:
                run_producer_consumer();
                break;

            case 3:
                run_shared_memory_demo();
                break;

            case 4:
                run_bankers_demo();
                break;

            case 5:
                run_process_demo();
                break;

            case 6:
                run_resource_demo();
                break;

            case 7:
                run_all_demos();
                break;

            case 0:
                printf("\nExiting Campus Compute System. Goodbye!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please select between 0 and 7.\n");
        }

        printf("\nPress Enter to continue...");
        getchar();
        getchar();
    }

    return 0;
}
