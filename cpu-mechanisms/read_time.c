/**
 * Total elapsed time: 86962438 microseconds
 * Average time per 0-byte read: 0.086962 microseconds
 */

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    struct timeval start_tv, end_tv;
    int fd = open("example.txt", O_RDONLY);
    char buf[1024];
    unsigned int num_repeat = 1e9;

    gettimeofday(&start_tv, NULL);
    // printf("Start: %ld.%ld\n", start_tv.tv_sec, start_tv.tv_usec);

    for (unsigned int ix = 0; ix < num_repeat; ix++)
        read(fd, buf, 0);

    gettimeofday(&end_tv, NULL);
    // printf("End: %ld.%ld\n", end_tv.tv_sec, end_tv.tv_usec);

    long elapsed_sec = end_tv.tv_sec - start_tv.tv_sec;
    long elapsed_usec = end_tv.tv_usec - start_tv.tv_usec;
    long total_elapsed_usec = elapsed_sec * 1e6 + elapsed_usec;

    double average_time_per_read = (double)total_elapsed_usec / num_repeat;
    printf("Total elapsed time: %ld microseconds\n", total_elapsed_usec);
    printf("Average time per 0-byte read: %f microseconds\n", average_time_per_read);

    close(fd);

    return 0;
}
