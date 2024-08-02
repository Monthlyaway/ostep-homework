#include <stdio.h>
#include <features.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
// #include <linux/time.h>

#define NUM_ITERATIONS 100000

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;
    struct timespec start, end;

    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    { // Child process
        for (int i = 0; i < NUM_ITERATIONS; i++)
        {
            char buf;
            read(pipe1[0], &buf, 0);
            write(pipe2[1], "x", 0);
        }
        exit(0);
    }
    else
    { // Parent process
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < NUM_ITERATIONS; i++)
        {
            char buf;
            write(pipe1[1], "x", 0);
            read(pipe2[0], &buf, 0);
        }

        clock_gettime(CLOCK_MONOTONIC, &end);
        wait(NULL);

        // Calculate elapsed time in nanoseconds
        long elapsed_ns = (end.tv_sec - start.tv_sec) * 1e9L + (end.tv_nsec - start.tv_nsec);
        double average_time_per_switch = (double)elapsed_ns / NUM_ITERATIONS;

        printf("Average time per context switch: %.2f ns\n", average_time_per_switch);
    }

    return 0;
}
