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

    shmflag = 00666|IPC_CREAT;
    shmid = shmget(key, size, shmflag);

    printf("Azonosito: %d\n", shmid);
    return 0;
}
