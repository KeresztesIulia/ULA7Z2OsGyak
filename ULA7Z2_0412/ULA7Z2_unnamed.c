#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main()
{
    char buffer[] = "Keresztes Iulia ULA7Z2";
    int size = strlen(buffer);
    int pipefd[2];
    pipe(pipefd);
    int pid = fork();

    if(pid != 0)
    {
        close(pipefd[1]);
        wait(NULL);
    }
    if(pid == 0)
    {
        close(pipefd[0]);
        write(pipefd[1], buffer, size);
        close(pipefd[1]);
        exit(0);
    }
    if(pid!=0)
    {
        read(pipefd[0], buffer, size);
        close(pipefd[0]);
        printf("%s", buffer);
    }

    return 0;

}
