#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "job.h"

typedef struct
{
    float avg_tat;
    float avg_wt;
} SchedulingResult;

SchedulingResult fcfs_schedule(Job jobs[], int n);
SchedulingResult round_robin_schedule(Job jobs[], int n, int quantum);
SchedulingResult priority_schedule(Job jobs[], int n);

void compare_scheduling(SchedulingResult fcfs,
                        SchedulingResult rr,
                        SchedulingResult priority);

#endif
