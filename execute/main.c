#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

void run_ls_al_single_arg(void)
{
    int fd[2];
    pid_t pid;
    char *argv[] = {"/bin/sh", "-c", "ls -al", NULL};
    char *envp[] = {NULL};
    char buffer[1024];
    ssize_t bytes_read;

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // Child process
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        execve("/bin/sh", argv, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        close(fd[1]);
        while ((bytes_read = read(fd[0], buffer, sizeof(buffer) - 1)) > 0)
        {
            buffer[bytes_read] = '\0';
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        close(fd[0]);
        waitpid(pid, NULL, 0);
    }
}

int main(void)
{
    run_ls_al_single_arg();
    return 0;
}
