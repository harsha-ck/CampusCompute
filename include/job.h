#ifndef JOB_H
#define JOB_H

typedef struct
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;

    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;

    int status;

} Job;

void create_jobs(Job jobs[], int n);
void display_jobs(Job jobs[], int n);

#endif

