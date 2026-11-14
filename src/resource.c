#include <stdio.h>
#include <sys/resource.h>

#include "resource.h"

void run_resource_demo(void)
{
    struct rlimit original, updated, current;

    printf("\n========== RESOURCE MANAGEMENT DEMO ==========\n");

    // Save original resource limits
    if(getrlimit(RLIMIT_NOFILE, &original) == -1)
    {
        perror("getrlimit failed");
        return;
    }

    printf("\nOriginal Resource Limits:\n");
    printf("Soft Limit: %llu\n",
           (unsigned long long)original.rlim_cur);
    printf("Hard Limit: %llu\n",
           (unsigned long long)original.rlim_max);

    // Reduce the soft limit to 64, if possible
    updated = original;

    if(updated.rlim_cur > 64)
    {
        updated.rlim_cur = 64;
    }

    if(setrlimit(RLIMIT_NOFILE, &updated) == -1)
    {
        perror("setrlimit failed");
        return;
    }

    printf("\nResource limit updated successfully!\n");

    // Verify updated limit
    if(getrlimit(RLIMIT_NOFILE, &current) == -1)
    {
        perror("getrlimit verification failed");
        return;
    }

    printf("\nUpdated Resource Limits:\n");
    printf("Soft Limit: %llu\n",
           (unsigned long long)current.rlim_cur);
    printf("Hard Limit: %llu\n",
           (unsigned long long)current.rlim_max);

    // Restore original limits
    if(setrlimit(RLIMIT_NOFILE, &original) == -1)
    {
        perror("Failed to restore original resource limit");
        return;
    }

    printf("\nOriginal resource limits restored successfully!\n");
}
