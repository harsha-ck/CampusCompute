#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <sys/wait.h>

#include "../include/ipc.h"
#define SHM_NAME "/campuscompute_shm"
#define SEM_NAME "/campuscompute_sem"
#define SHM_SIZE  sizeof(SharedData)

typedef struct
{
    int job_id;
    int burst_time;
    char status[50];

} SharedData;
void run_shared_memory_demo(void)
{
    int shm_fd;
    SharedData *data;

    printf("\n========== SHARED MEMORY DEMO ==========\n");

    // Create shared memory
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

    if(shm_fd == -1)
    {
        perror("shm_open failed");
        return;
    }

    // Set shared memory size
    if(ftruncate(shm_fd, SHM_SIZE) == -1)
    {
        perror("ftruncate failed");
        close(shm_fd);
        shm_unlink(SHM_NAME);
        return;
    }

    printf("Shared memory created successfully!\n");
// Map shared memory into the process address space
data = mmap(NULL, SHM_SIZE,
            PROT_READ | PROT_WRITE,
            MAP_SHARED, shm_fd, 0);
if(data == MAP_FAILED)
{
    perror("mmap failed");
    close(shm_fd);
    shm_unlink(SHM_NAME);
    return;
}

printf("Shared memory mapped successfully!\n");
// Create named semaphore
sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 0);

if(sem == SEM_FAILED)
{
    perror("sem_open failed");

    munmap(data, SHM_SIZE);
    close(shm_fd);
    shm_unlink(SHM_NAME);

    return;
}

printf("Named semaphore created successfully!\n");
// Create a child process
pid_t pid = fork();

if(pid < 0)
{
    perror("fork failed");

    sem_close(sem);
    sem_unlink(SEM_NAME);
    munmap(data, SHM_SIZE);
    close(shm_fd);
    shm_unlink(SHM_NAME);

    return;
}
if(pid == 0)
{
    // Child waits until parent writes the data
    printf("\nChild process waiting for data...\n");

    sem_wait(sem);

    printf("\nChild process received shared data:\n");
    printf("Job ID: %d\n", data->job_id);
    printf("Burst Time: %d\n", data->burst_time);
    printf("Status: %s\n", data->status);

    sem_close(sem);

    _exit(0);
}
else
{
    // Parent writes data into shared memory
    data->job_id = 101;
    data->burst_time = 5;

    strcpy(data->status, "Running");

    printf("\nParent process wrote data:\n");
    printf("Job ID: %d\n", data->job_id);
    printf("Burst Time: %d\n", data->burst_time);
    printf("Status: %s\n", data->status);

    // Signal the child that data is ready
    sem_post(sem);

    // Wait for child process to finish
    waitpid(pid, NULL, 0);

    printf("\nChild process completed successfully!\n");

    // Cleanup
    sem_close(sem);
    sem_unlink(SEM_NAME);

    munmap(data, SHM_SIZE);
    close(shm_fd);
    shm_unlink(SHM_NAME);

    printf("Shared memory and semaphore cleaned up!\n");
}

