#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

#include "resource.h"
void run_resource_demo(void)
{
    struct rlimit limit;

    printf("\n========== RESOURCE MANAGEMENT DEMO ==========\n");

    // Get current file descriptor limit
    if(getrlimit(RLIMIT_NOFILE, &limit) == -1)
    {
        perror("getrlimit failed");
        return;
    }

    printf("\nCurrent Resource Limits:\n");
    printf("Soft Limit: %llu\n",
           (unsigned long long)limit.rlim_cur);

    printf("Hard Limit: %llu\n",
           (unsigned long long)limit.rlim_max);

    // Set a lower soft limit without exceeding the hard limit
    rlim_t new_limit = limit.rlim_cur;

    if(new_limit > 64)
    {
        new_limit = 64;
    }

    limit.rlim_cur = new_limit;

    if(setrlimit(RLIMIT_NOFILE, &limit) == -1)
    {
        perror("setrlimit failed");
        return;
    }

    printf("\nResource limit updated successfully!\n");

    // Verify updated resource limit
    if(getrlimit(RLIMIT_NOFILE, &limit) == -1)
    {
        perror("getrlimit verification failed");
        return;
    }

    printf("\nUpdated Resource Limits:\n");
    printf("Soft Limit: %llu\n",
           (unsigned long long)limit.rlim_cur);

    printf("Hard Limit: %llu\n",
           (unsigned long long)limit.rlim_max);
}
