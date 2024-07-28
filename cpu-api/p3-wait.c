#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "Error when creating child process");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("Hello!\n");
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("Goodbye!\n");
    }

    return 0;
}
