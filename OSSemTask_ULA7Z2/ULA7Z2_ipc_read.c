#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHMKEY 94300L

struct msgbuff{
    int msize;
    char mtext[512];
} *msgstruct;

struct shmid_ds shmstruct;

int main()
{
    int shmid, shmflag, size = 512;
    key_t key = SHMKEY;

    shmflag = 0;
    shmid = shmget(key, size, shmflag);

    if(shmid < 0)
    {
        printf("Nem letezik a memoria szegmens!");
        exit(0);
    }

    shmflag = 00666 | SHM_RND;
    msgstruct = (struct msgbuff *)shmat(shmid,NULL, shmflag);

    printf("A memoria szegmensen levo uzenet:\n%s", msgstruct->mtext);

    FILE* file = fopen("ULA7Z2_nagyfajl_masolat.txt", "w");
    fprintf(file, "%s", msgstruct->mtext);
    fclose(file);

    shmdt(msgstruct);

    return 0;
}
