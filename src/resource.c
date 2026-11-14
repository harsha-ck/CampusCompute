#include <stdio.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "resource.h"

void run_resource_demo(void)
{
    struct rlimit original_limit;
    struct rlimit limit;

    int fd[64];
    int count = 0;
    int i;

    printf("\n========== RESOURCE MANAGEMENT DEMO ==========\n");

    // Get original resource limit
    if(getrlimit(RLIMIT_NOFILE, &original_limit) == -1)
    {
        perror("getrlimit failed");
        return;
    }

    printf("\nOriginal Resource Limits:\n");
    printf("Soft Limit: %llu\n",
           (unsigned long long)original_limit.rlim_cur);
    printf("Hard Limit: %llu\n",
           (unsigned long long)original_limit.rlim_max);

    // Set a lower soft limit
    limit = original_limit;

    if(limit.rlim_cur > 64)
    {
        limit.rlim_cur = 64;
    }

    if(setrlimit(RLIMIT_NOFILE, &limit) == -1)
    {
        perror("setrlimit failed");
        return;
    }

    printf("\nResource limit updated successfully!\n");

    // Verify updated limit
    if(getrlimit(RLIMIT_NOFILE, &limit) == -1)
    {
        perror("getrlimit verification failed");
        setrlimit(RLIMIT_NOFILE, &original_limit);
        return;
    }

    printf("\nUpdated Resource Limits:\n");
    printf("Soft Limit: %llu\n",
           (unsigned long long)limit.rlim_cur);
    printf("Hard Limit: %llu\n",
           (unsigned long long)limit.rlim_max);

    // Demonstrate the actual effect of the limit
    printf("\nTesting file descriptor limit...\n");

    while(count < 64)
    {
        fd[count] = open("/dev/null", O_RDONLY);

        if(fd[count] == -1)
        {
            if(errno == EMFILE)
            {
                printf("\nResource limit reached!\n");
                printf("Too many open files (EMFILE).\n");
            }
            else
            {
                perror("open failed");
            }

            break;
        }

        count++;
    }

    printf("Successfully opened file descriptors: %d\n", count);

    // Close all opened file descriptors
    for(i = 0; i < count; i++)
    {
        close(fd[i]);
    }

    printf("All opened file descriptors closed successfully.\n");

    // Restore original resource limit
    if(setrlimit(RLIMIT_NOFILE, &original_limit) == -1)
    {
        perror("Failed to restore original resource limit");
        return;
    }

    printf("Original resource limit restored successfully.\n");
}
