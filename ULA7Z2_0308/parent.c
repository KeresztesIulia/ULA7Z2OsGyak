#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main()
{
    pid_t child = fork();
    waitpid(child,NULL,0);
    if (child < 0)
    {
        printf("failed");
    }
    else if (child == 0)
    {
        execl("./child","child",(char*)NULL);
    }
    return 0;
}