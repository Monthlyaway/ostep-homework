#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

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
        // Close the unnecessary end of the pipe
        // START
        // Close the read end of the pipe
        close(fd[0]);
        // END

        // Redirect stdout to the write end of the pipe
        // START
        // Use dup2 to redirect stdout to the write end of the pipe
        open("./p8.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        // END

        // Execute the desired program
        // START
        // Use execlp or similar to execute a command that writes to stdout
        printf("Child process PID: %d\n", getpid());
        // END

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
            // Close the unnecessary end of the pipe
            // START
            // Close the write end of the pipe
            
            // END

            // Redirect stdin to the read end of the pipe
            // START
            // Use dup2 to redirect stdin to the read end of the pipe
            // END

            // Execute the desired program
            // START
            // Use execlp or similar to execute a command that reads from stdin
            // END

            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            // Close both ends of the pipe
            // START
            // Close both read and write ends of the pipe
            // END

            // Wait for both children to exit
            // START
            // Use waitpid or wait to wait for both child processes
            // END
        }
    }

    return 0;
}
