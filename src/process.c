#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "process.h"

void run_process_demo(void)
{
    pid_t pid;
    int status;

    printf("\n========== PROCESS MANAGEMENT DEMO ==========\n");

    // Run two test cases
    for(int test = 0; test < 2; test++)
    {
        printf("\n--- Test %d: %s ---\n",
               test + 1,
               test == 0 ? "Normal Execution" : "Simulated Failure");

        fflush(stdout);

        pid = fork();

        if(pid < 0)
        {
            perror("fork failed");
            return;
        }

        // Child process
        if(pid == 0)
        {
            printf("\nChild Process:\n");
            printf("Child PID: %d\n", getpid());
            printf("Parent PID: %d\n", getppid());

            if(test == 0)
            {
                printf("Child process executing successfully.\n");
                exit(EXIT_SUCCESS);
            }
            else
            {
                printf("Child process simulating a failure.\n");
                exit(EXIT_FAILURE);
            }
        }

        // Parent process
        else
        {
            printf("\nParent Process:\n");
            printf("Parent PID: %d\n", getpid());
            printf("Created Child PID: %d\n", pid);

            if(waitpid(pid, &status, 0) == -1)
            {
                perror("waitpid failed");
                return;
            }

            if(WIFEXITED(status))
            {
                int exit_status = WEXITSTATUS(status);

                printf("\nChild exited with status: %d\n", exit_status);

                if(exit_status == EXIT_SUCCESS)
                {
                    printf("Parent: Child completed successfully.\n");
                }
                else
                {
                    printf("Parent: Child failure detected!\n");
                }
            }
            else
            {
                printf("\nChild terminated abnormally.\n");
            }
        }
    }

    printf("\nProcess management demo completed.\n");
}
