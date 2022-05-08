#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#define KEY 24601L
#define N 3

int main()
{
    int semid, semnum;
    int val;

    key_t semkey = KEY;
    semnum = N;

    if((semid = semget(semkey, semnum, 0))<0)
    {
        perror("A szemafor nem létezik!");
        exit(-1);
    }

    if((val = semctl(semid, 0, GETVAL))<0)
    {
        perror("Érték lekérdezése sikertelen.");
    }
    else
    {
        printf("A szemafor értéke: %d\n", val);
    }
    exit(0);
}
