/*
 * exec() Family Functions Explanation:
 *
 * 1. execl():
 *    - Usage: execl(const char *path, const char *arg, ..., NULL);
 *    - "l" in execl stands for list.
 *    - This function takes a path to the executable and a variable-length list of arguments terminated by NULL.
 *    - It is useful when the number of arguments is fixed and known at compile time.
 *
 * 2. execle():
 *    - Usage: execle(const char *path, const char *arg, ..., NULL, char *const envp[]);
 *    - "e" in execle indicates that the environment can be explicitly specified.
 *    - Similar to execl(), but allows specifying the environment of the executed program.
 *    - Useful when you need to control the environment variables of the new process.
 *
 * 3. execlp():
 *    - Usage: execlp(const char *file, const char *arg, ..., NULL);
 *    - "p" in execlp stands for path.
 *    - Similar to execl(), but the executable is searched in the directories specified by the PATH environment variable.
 *    - Useful when the full path of the executable is not known.
 *
 * 4. execv():
 *    - Usage: execv(const char *path, char *const argv[]);
 *    - "v" in execv stands for vector.
 *    - This function takes a path to the executable and an array of pointers to null-terminated strings that represent the argument list.
 *    - This variant is suitable when the number of arguments is dynamic or determined at runtime.
 *
 * 5. execvp():
 *    - Usage: execvp(const char *file, char *const argv[]);
 *    - Combines features of execv and execlp.
 *    - Like execv, it takes an array of arguments; like execlp, it searches for the executable in the PATH.
 *    - Useful when the number of arguments is dynamic and the full path of the executable is not known.
 *
 * 6. execvpe():
 *    - Usage: execvpe(const char *file, char *const argv[], char *const envp[]);
 *    - "e" indicates that the environment can be explicitly specified.
 *    - Combines features of execvp and execle.
 *    - Like execvp, it searches for the executable in the PATH and takes an array of arguments; like execle, it allows specifying the environment.
 *    - Useful when you need full control over the executable's environment and arguments, especially when the executable's path is not fully known.
 *
 * Each function replaces the current process image with a new process image specified by the path or file argument and does not return on success.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    char *args[] = {"/bin/ls", "-l", NULL}; // Arguments for execv and execvp

    // Using execl()
    pid = fork();
    if (pid == 0)
    {
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }

    wait(NULL); // Wait for the child process to finish

    // Using execle()
    pid = fork();
    if (pid == 0)
    {
        char *env[] = {NULL};
        execle("/bin/ls", "ls", "-l", NULL, env);
        perror("execle");
        exit(EXIT_FAILURE);
    }

    wait(NULL);

    // Using execlp()
    pid = fork();
    if (pid == 0)
    {
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    wait(NULL);

    // Using execv()
    pid = fork();
    if (pid == 0)
    {
        execv("/bin/ls", args);
        perror("execv");
        exit(EXIT_FAILURE);
    }

    wait(NULL);

    // Using execvp()
    pid = fork();
    if (pid == 0)
    {
        execvp("ls", args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    wait(NULL);

    // // Using execvpe() - Not in POSIX.1-2001, but available in glibc.
    // pid = fork();
    // if (pid == 0)
    // {
    //     char *envp[] = {NULL};
    //     execvpe("ls", args, envp);
    //     perror("execvpe");
    //     exit(EXIT_FAILURE);
    // }

    // wait(NULL);

    return 0;
}
