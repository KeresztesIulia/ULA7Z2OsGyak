#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHMKEY 94300L

int main()
{
    int shmid, shmflag, size = 512;
    key_t key = SHMKEY;

    shmflag = 0;
    if((shmid = shmget(key, size, shmflag))<0)
    {
        printf("A memoriaszegmens nem letezik.");
        exit(0);
    }

    shmctl(shmid, IPC_RMID, NULL);
    printf("Torolve");
    return 0;
}
