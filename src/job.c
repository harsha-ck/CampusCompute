#include <stdio.h>
#include "../include/job.h"

int create_jobs(Job jobs[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("\nEnter details for Job %d\n", i + 1);

        jobs[i].id = i + 1;

        printf("Arrival Time: ");
        if(scanf("%d", &jobs[i].arrival_time) != 1 ||
           jobs[i].arrival_time < 0)
        {
            printf("Invalid arrival time! Enter a non-negative integer.\n");
            return 0;
        }

        printf("Burst Time: ");
        if(scanf("%d", &jobs[i].burst_time) != 1 ||
           jobs[i].burst_time <= 0)
        {
            printf("Invalid burst time! Enter a positive integer.\n");
            return 0;
        }

        printf("Priority: ");
        if(scanf("%d", &jobs[i].priority) != 1 ||
           jobs[i].priority < 0)
        {
            printf("Invalid priority! Enter a non-negative integer.\n");
            return 0;
        }

        jobs[i].remaining_time = jobs[i].burst_time;
        jobs[i].completion_time = 0;
        jobs[i].turnaround_time = 0;
        jobs[i].waiting_time = 0;
        jobs[i].status = 0;
    }

    return 1;
}

void display_jobs(Job jobs[], int n)
{
    printf("\n========== JOB DETAILS ==========\n");
    printf("ID\tAT\tBT\tPriority\n");

    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n",
               jobs[i].id,
               jobs[i].arrival_time,
               jobs[i].burst_time,
               jobs[i].priority);
    }
}
