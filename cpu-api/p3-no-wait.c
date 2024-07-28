#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int fd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0)
    {
        // First child process
        // Close the read end of the pipe
        close(fd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]); // Close the original file descriptor after duplication

        // Send PID to the pipe
        printf("Child process PID: %d, parent process PID: %d\n", getpid(), getppid());
        fflush(stdout); // Ensure all output is sent through the pipe

        exit(EXIT_SUCCESS);
    }
    else
    {
        // Fork the second child
        pid2 = fork();
        if (pid2 == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0)
        {
            // Second child process
            // Close the write end of the pipe
            close(fd[1]);

            // Read from the pipe
            char buffer[1024];
            int nbytes = read(fd[0], buffer, sizeof(buffer));
            if (nbytes > 0)
            {
                // Print what was read from the pipe
                write(STDOUT_FILENO, buffer, nbytes);
            }
            close(fd[0]);

            exit(EXIT_SUCCESS);
        }
        else
        {
            // Parent process
            // Close both ends of the pipe
            close(fd[0]);
            close(fd[1]);

            // Wait for both children to exit
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }

    return 0;
}
