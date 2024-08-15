#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <memory_in_MB> [<time_in_seconds>]\n", argv[0]);
        return 1;
    }

    int memory_mb = atoi(argv[1]);
    int run_time = (argc > 2) ? atoi(argv[2]) : -1;

    size_t memory_size = (size_t)memory_mb * 1024 * 1024; // Convert MB to bytes
    char *memory = (char *)malloc(memory_size);

    if (memory == NULL)
    {
        perror("Failed to allocate memory");
        return 1;
    }

    printf("Allocated %d MB of memory.\n", memory_mb);

    time_t start_time = time(NULL);
    while (1)
    {
        for (size_t i = 0; i < memory_size; i++)
        {
            memory[i] = (char)(i % 256); // Touch each byte of the memory
        }

        if (run_time > 0 && (time(NULL) - start_time) >= run_time)
        {
            break;
        }

        // Sleep for a short period to avoid excessive CPU usage
        // usleep(200);
    }

    printf("Finished.\n");
    free(memory);
    return 0;
}
