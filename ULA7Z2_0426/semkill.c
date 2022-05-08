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
    semnum = N;
    key_t semkey = KEY;

    if((semid = semget(semkey, semnum, 0))<0)
    {
        perror("A szemafor nem létezik.");
        exit(-1);
    }

        if(semctl(semid, semnum, IPC_RMID, NULL) < 0)
        {
            perror("Sikertelen törlés!");
        }
        else
        {
            puts("A szemafor sikeresen törölve lett!");
        }
    exit(-1);
}
