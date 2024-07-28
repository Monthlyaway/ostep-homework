#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // Open a file
    int fd = open("./p2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd < 0)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }

    // Fork a new process
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "Error when creating child process\n");
        close(fd);
        exit(1);
    }
    else if (rc == 0)
    {
        // Child process
        printf("Child process\n");
        const char *child_msg = "This is the child writing to the file.\n";
        write(fd, child_msg, strlen(child_msg));
    }
    else
    {
        // Parent process
        printf("Parent process\n");
        const char *parent_msg = "This is the parent writing to the file.\n";
        write(fd, parent_msg, strlen(parent_msg));
        wait(NULL); // Wait for the child to finish
    }

    // Close the file descriptor
    close(fd);
    return 0;
}
