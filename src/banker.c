#include <stdio.h>
#include <stdbool.h>
#include "banker.h"
void run_bankers_demo(void)
{
    int n = 5;
    int m = 3;

    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int maximum[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int available[MAX_RESOURCES] = {3, 3, 2};
    int need[MAX_PROCESSES][MAX_RESOURCES];

    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};

    int safe_sequence[MAX_PROCESSES];

    int count = 0;

    // Calculate Need matrix
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    // Copy Available into Work
    for(int j = 0; j < m; j++)
    {
        work[j] = available[j];
    }

    printf("\n========== BANKER'S ALGORITHM ==========\n");

    // Safety Algorithm
    while(count < n)
    {
        bool found = false;

        for(int i = 0; i < n; i++)
        {
            if(!finish[i])
            {
                int j;

                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                        break;
                }

                if(j == m)
                {
                    for(int k = 0; k < m; k++)
                    {
                        work[k] += allocation[i][k];
                    }

                    safe_sequence[count++] = i;

                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found)
            break;
    }

    // Display result
    if(count == n)
    {
        printf("\nSystem is in SAFE state.\n");

        printf("Safe Sequence: ");

        for(int i = 0; i < n; i++)
        {
            printf("P%d", safe_sequence[i]);

            if(i != n - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is in UNSAFE state.\n");
        printf("No safe sequence exists.\n");
    }
    // Second test: deliberately create an unsafe state
    printf("\n--- UNSAFE STATE TEST ---\n");

    int unsafe_available[MAX_RESOURCES] = {0, 0, 0};

    // Reset the safety algorithm variables
    count = 0;

    for(int i = 0; i < n; i++)
    {
        finish[i] = false;
    }

    for(int j = 0; j < m; j++)
    {
        work[j] = unsafe_available[j];
    }

    // Run safety algorithm again
    while(count < n)
    {
        bool found = false;

        for(int i = 0; i < n; i++)
        {
            if(!finish[i])
            {
                int j;

                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                        break;
                }

                if(j == m)
                {
                    for(int k = 0; k < m; k++)
                    {
                        work[k] += allocation[i][k];
                    }

                    safe_sequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found)
            break;
    }

    if(count == n)
    {
        printf("System is in SAFE state.\n");
    }
    else
    {
        printf("System is in UNSAFE state.\n");
        printf("No safe sequence exists.\n");
    }
}
