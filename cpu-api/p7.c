#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int rc = fork();
    if (rc == 0)
    {
        close(STDOUT_FILENO);
        printf("Hello World!\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}
