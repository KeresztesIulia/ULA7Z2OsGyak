#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

#define KEY 9430L

struct sembuf up = {0, 1, 0};
struct sembuf down = {0, -1, 0};

int main()
{
    int semid, semflag;
    key_t semkey = KEY;
    semflag = 00666 | IPC_CREAT;

    if((semid = semget(semkey, 1, 0))<0)
    {
        puts("A szemafor nem létezik. Létrehozzuk, és inicializáljuk 1-re.");
        if((semid = semget(semkey, 1, semflag))<0)
        {
            perror("Nem sikerült létrehozni a szemafort.");
            exit(-1);
        }
        semctl(semid, 0, IPC_SET, 4);
    }
    else
    {
        puts("Már létezik a szemafor.");
    }

    pid_t pid = fork();

    if(pid == 0)
    {
        fork();
    }

    semop(semid, &down, 1);
    printf("Process ID: %d", getpid());

    semop(semid, &up, 1);

    if(pid != 0)
    {
        if(semctl(semid, 0, IPC_RMID, NULL)>=0)
        {
            puts("A szemafort töröltük.");
        }
    }

    exit(0);
}
