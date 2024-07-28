#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int x = 100;
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "Error when creating child process");
        exit(1);
    }
    else if (rc == 0)
    {
        x = 200;
        printf("Child process: x = %d\n", x);
        exit(0);
    }
    else
    {
        x = 300;
        printf("Parent process: x = %d\n", x);
    }
    printf("Bye!\n");
    return 0;
}
