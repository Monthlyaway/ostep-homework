#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1, pid2;
    int status;

    // First fork
    pid1 = fork();
    if (pid1 == 0)
    {
        // Child process 1
        printf("Child 1: PID = %d, Parent PID = %d\n", getpid(), getppid());
        sleep(2); // Simulate work by sleeping
        exit(0);  // Child 1 exits
    }
    else if (pid1 > 0)
    {
        // Parent process
        printf("Parent: PID = %d, Child 1 PID = %d\n", getpid(), pid1);

        // Second fork
        pid2 = fork();
        if (pid2 == 0)
        {
            // Child process 2
            printf("Child 2: PID = %d, Parent PID = %d\n", getpid(), getppid());
            sleep(5); // Simulate work by sleeping
            wait(NULL);  // Return immediately since there is no child process for pid2
            exit(0);  // Child 2 exits
        }
        else if (pid2 > 0)
        {
            // Parent process
            printf("Parent: PID = %d, Child 2 PID = %d\n", getpid(), pid2);

            // Wait for the first child to terminate
            waitpid(pid1, &status, 0);
            printf("Parent: Child 1 with PID %d terminated\n", pid1);

            // Wait for the second child to terminate
            waitpid(pid2, &status, 0);
            printf("Parent: Child 2 with PID %d terminated\n", pid2);
        }
        else
        {
            printf("Failed to fork second child\n");
            exit(1);
        }
    }
    else
    {
        printf("Failed to fork first child\n");
        exit(1);
    }

    return 0;
}
