#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int sigIntnr = 0;

void handleSignals(int signalCode)
{
    if(signalCode == SIGINT)
    {
        if(sigIntnr == 0)
        {
            printf("\nSIGINT, visszateresi ertek: %d\n", signalCode);
        }
        if(sigIntnr == 1)
        {
            printf("\nAlapertelmezett: %d\n", (int)SIG_DFL);
        }
        if(sigIntnr == 2)
        {
            printf("\nKilepes\n");
            exit(0);
        }
        sigIntnr++;
    }
    else if(signalCode == SIGQUIT)
    {
        printf("\nVisszateresi ertek: %d\n", signalCode);
    }

}

int main()
{
    if(signal(SIGQUIT, handleSignals) == SIG_ERR)
    {
        printf("hiba");
    }
    if(signal(SIGINT, handleSignals) == SIG_ERR)
    {
        printf("hiba");
    }

    while(1)
        sleep(1);

    return 0;
}


