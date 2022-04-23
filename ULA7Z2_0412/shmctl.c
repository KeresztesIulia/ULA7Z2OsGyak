#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHMKEY 24601L



int main()
{
    int shmid, shmflag, size = 512;
    key_t key = SHMKEY;

    struct shmid_ds shmstruct;

    shmflag = 0;
    shmid = shmget(key, size, shmflag);
    if(shmid < 0)
    {
        printf("shmget() sikertelen\n");
        exit(-1);
    }

    shmctl(shmid, IPC_STAT, &shmstruct);
    printf("Szegmens merete: %lu\nPID: %d", shmstruct.shm_segsz, shmstruct.shm_lpid);

    return 0;
}
