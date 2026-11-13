#include <stdio.h>
#include "../include/job.h"

void create_jobs(Job jobs[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("\nEnter details for Job %d\n", i + 1);

        jobs[i].id = i + 1;

        printf("Arrival Time: ");
        scanf("%d", &jobs[i].arrival_time);

        printf("Burst Time: ");
        scanf("%d", &jobs[i].burst_time);

        printf("Priority: ");
        scanf("%d", &jobs[i].priority);

        jobs[i].remaining_time = jobs[i].burst_time;
        jobs[i].completion_time = 0;
        jobs[i].turnaround_time = 0;
        jobs[i].waiting_time = 0;
        jobs[i].status = 0;
    }
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

