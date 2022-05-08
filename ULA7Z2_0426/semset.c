#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#define KEY 24601L
#define N 3

int main()
{
    int semid, semflag, semnum;
    key_t semkey = KEY;
    semflag = 00666 | IPC_CREAT;
    semnum = N;

    if((semid = semget(semkey, semnum, 0)) < 0)
    {
        if((semid = semget(semkey, semnum, semflag)) < 0)
        {
            perror("Szemaforlétrehozás error!");
            exit(-1);
        }
    }
    else
    {
        puts("A szemafor már létezik, megpróbáljuk 0-ra állítani.");
    }

        if(semctl(semid, 0, SETVAL, 0) < 0)
        {
            perror("Nem sikerült az inicializálás.");
        }
        else
        {
            puts("Sikeres inicializálás.");
        }
    exit(0);
}
