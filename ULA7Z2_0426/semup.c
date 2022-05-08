#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#define KEY 24601L
#define N 3

int main()
{
    int semnum = N;
    struct sembuf semup = { 0, 1, 0 };

    int semid;
    key_t semkey = KEY;

    if((semid = semget(semkey, semnum, 0))<0)
    {
        perror("A szemafor nem létezik!");
        exit(-1);
    }

    if(semop(semid, &semup, 1) < 0)
    {
        perror("Nem sikerült a semop művelet!");
    }
    else
    {
        puts("Szemafor inkrementálva!");
    }


    exit(0);
}
