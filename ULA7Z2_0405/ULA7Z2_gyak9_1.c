#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signAlarm(int alrm)
{
    printf("\nULA7Z2\n");
    sleep(1);
    printf("\nKilepes\n");
}

int main()
{
    if(signal(SIGALRM, signAlarm) == SIG_ERR)
    {
        printf("Hiba");
    }
    else
    {

        kill(getpid(),SIGALRM);

    }
    return 0;
}
