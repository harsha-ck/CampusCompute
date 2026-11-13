
#include <stdio.h>
#include "../include/scheduler.h"

SchedulingResult fcfs_schedule(Job jobs[], int n)
{SchedulingResult result;
    Job sorted[n];

    // Copy original jobs
    for(int i = 0; i < n; i++)
    {
        sorted[i] = jobs[i];
    }

    // Sort jobs according to arrival time
    // If arrival times are equal, smaller job ID comes first
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(sorted[j].arrival_time > sorted[j + 1].arrival_time)
            {
                Job temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    float total_tat = 0;
    float total_wt = 0;

    printf("\n========== FCFS SCHEDULING ==========\n");

    printf("\nGantt Chart:\n");

    for(int i = 0; i < n; i++)
    {
        // Handle CPU idle time
        if(current_time < sorted[i].arrival_time)
        {
            printf("| IDLE ");
            current_time = sorted[i].arrival_time;
        }

        printf("| J%d ", sorted[i].id);

        current_time += sorted[i].burst_time;

        sorted[i].completion_time = current_time;

        sorted[i].turnaround_time =
            sorted[i].completion_time - sorted[i].arrival_time;

        sorted[i].waiting_time =
            sorted[i].turnaround_time - sorted[i].burst_time;

        total_tat += sorted[i].turnaround_time;
        total_wt += sorted[i].waiting_time;
    }

    printf("|\n");

    printf("\nJob\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("J%d\t%d\t%d\t%d\t%d\t%d\n",
               sorted[i].id,
               sorted[i].arrival_time,
               sorted[i].burst_time,
               sorted[i].completion_time,
               sorted[i].turnaround_time,
               sorted[i].waiting_time);
    }

 result.avg_tat = total_tat / n;
result.avg_wt = total_wt / n;

printf("\nAverage Turnaround Time: %.2f",
       result.avg_tat);

printf("\nAverage Waiting Time: %.2f\n",
       result.avg_wt);

return result;
}


SchedulingResult round_robin_schedule(Job jobs[], int n, int quantum)
{SchedulingResult result;
    Job sorted[n];

    int queue[100];
    int front = 0, rear = 0;
    int count = 0;

    int current_time = 0;
    int completed = 0;

    float total_tat = 0;
    float total_wt = 0;

    // Copy jobs
    for(int i = 0; i < n; i++)
    {
        sorted[i] = jobs[i];
        sorted[i].remaining_time = sorted[i].burst_time;
    }

    // Sort according to arrival time
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(sorted[j].arrival_time > sorted[j + 1].arrival_time)
            {
                Job temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    printf("\n========== ROUND ROBIN SCHEDULING ==========\n");
    printf("Time Quantum: %d\n", quantum);

    printf("\nGantt Chart:\n");

    // Add initially available jobs
    while(count < n && sorted[count].arrival_time <= current_time)
    {
        queue[rear] = count;
        rear = (rear + 1) % 100;
        count++;
    }

    while(completed < n)
    {
        // If queue is empty, move to next arrival
        if(front == rear)
        {
            printf("| IDLE ");
            current_time = sorted[count].arrival_time;

            while(count < n && sorted[count].arrival_time <= current_time)
            {
                queue[rear] = count;
                rear = (rear + 1) % 100;
                count++;
            }
        }

        int index = queue[front];
        front = (front + 1) % 100;

        int execute_time;

        if(sorted[index].remaining_time > quantum)
            execute_time = quantum;
        else
            execute_time = sorted[index].remaining_time;

        printf("| J%d ", sorted[index].id);

        current_time += execute_time;
        sorted[index].remaining_time -= execute_time;

        // Add newly arrived jobs
        while(count < n && sorted[count].arrival_time <= current_time)
        {
            queue[rear] = count;
            rear = (rear + 1) % 100;
            count++;
        }

        // Reinsert unfinished job
        if(sorted[index].remaining_time > 0)
        {
            queue[rear] = index;
            rear = (rear + 1) % 100;
        }
        else
        {
            sorted[index].completion_time = current_time;

            sorted[index].turnaround_time =
                sorted[index].completion_time - sorted[index].arrival_time;

            sorted[index].waiting_time =
                sorted[index].turnaround_time - sorted[index].burst_time;

            total_tat += sorted[index].turnaround_time;
            total_wt += sorted[index].waiting_time;

            completed++;
        }
    }

    printf("|\n");

    printf("\nJob\tAT\tBT\tCT\tTAT\tWT\n");

    // Display results in original job order
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(sorted[j].id == i)
            {
                printf("J%d\t%d\t%d\t%d\t%d\t%d\n",
                       sorted[j].id,
                       sorted[j].arrival_time,
                       sorted[j].burst_time,
                       sorted[j].completion_time,
                       sorted[j].turnaround_time,
                       sorted[j].waiting_time);
                break;
            }
        }
    }

  result.avg_tat = total_tat / n;
result.avg_wt = total_wt / n;

printf("\nAverage Turnaround Time: %.2f", result.avg_tat);
printf("\nAverage Waiting Time: %.2f\n", result.avg_wt);

return result;
}
SchedulingResult priority_schedule(Job jobs[], int n)
{SchedulingResult result;
    Job sorted[n];
    int completed = 0;
    int current_time = 0;

    float total_tat = 0;
    float total_wt = 0;

    int visited[n];

    for(int i = 0; i < n; i++)
    {
        sorted[i] = jobs[i];
        visited[i] = 0;
    }

    printf("\n========== PRIORITY SCHEDULING ==========\n");
    printf("Smaller priority number = Higher priority\n");

    printf("\nGantt Chart:\n");

    while(completed < n)
    {
        int index = -1;

        // Find the highest-priority job that has arrived
        for(int i = 0; i < n; i++)
        {
            if(visited[i] == 0 &&
               sorted[i].arrival_time <= current_time)
            {
                if(index == -1 ||
                   sorted[i].priority < sorted[index].priority ||
                   (sorted[i].priority == sorted[index].priority &&
                    sorted[i].id < sorted[index].id))
                {
                    index = i;
                }
            }
        }

        // No job has arrived yet
        if(index == -1)
        {
            printf("| IDLE ");
            current_time++;
            continue;
        }

        // Execute the selected job completely
        printf("| J%d ", sorted[index].id);

        current_time += sorted[index].burst_time;

        sorted[index].completion_time = current_time;

        sorted[index].turnaround_time =
            sorted[index].completion_time - sorted[index].arrival_time;

        sorted[index].waiting_time =
            sorted[index].turnaround_time - sorted[index].burst_time;

        total_tat += sorted[index].turnaround_time;
        total_wt += sorted[index].waiting_time;

        visited[index] = 1;
        completed++;
    }

    printf("|\n");

    printf("\nJob\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++)
    {
        printf("J%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               sorted[i].id,
               sorted[i].arrival_time,
               sorted[i].burst_time,
               sorted[i].priority,
               sorted[i].completion_time,
               sorted[i].turnaround_time,
               sorted[i].waiting_time);
    }

    result.avg_tat = total_tat / n;
result.avg_wt = total_wt / n;

printf("\nAverage Turnaround Time: %.2f", result.avg_tat);
printf("\nAverage Waiting Time: %.2f\n", result.avg_wt);

return result;
}
void compare_scheduling(SchedulingResult fcfs,
                        SchedulingResult rr,
                        SchedulingResult priority)
{
    printf("\n========== SCHEDULING COMPARISON ==========\n");

    printf("\nAlgorithm\tAverage TAT\tAverage WT\n");

    printf("FCFS\t\t%.2f\t\t%.2f\n",
           fcfs.avg_tat, fcfs.avg_wt);

    printf("Round Robin\t%.2f\t\t%.2f\n",
           rr.avg_tat, rr.avg_wt);

    printf("Priority\t%.2f\t\t%.2f\n",
           priority.avg_tat, priority.avg_wt);
}
