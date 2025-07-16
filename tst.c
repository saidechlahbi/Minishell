#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

int main ()
{
    int pid = fork();
    if (pid == 0)
    {
        execve(NULL, NULL, NULL);
        perror("failed\n")
    }

}
