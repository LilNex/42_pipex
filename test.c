#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];
    pid_t pid1, pid2;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) { // child process 1
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        char *cmd[] = {"ls", "-l", NULL};
        execve("/bin/ls", cmd, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) { // child process 2
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        char *cmd[] = {"wc", "-l", NULL};
        execve("/usr/bin/wc", cmd, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    }

    // parent process
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}