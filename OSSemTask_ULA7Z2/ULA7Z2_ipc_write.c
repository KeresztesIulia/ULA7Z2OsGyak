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

int main()
{
    int shmid, shmflag, size = 512;
    key_t key = SHMKEY;

    shmflag = 0;
    if((shmid = shmget(key, size, shmflag))<0)
    {
        shmflag = 00666 | IPC_CREAT;
        shmid = shmget(key, size, shmflag);
    }




    shmflag = 00666 | SHM_RND;
    msgstruct = (struct msgbuff*)shmat(shmid, NULL, shmflag);

    FILE* file = fopen("ULA7Z2_nagyfajl.txt", "rt");
    fscanf(file, "%[^\n]", msgstruct->mtext);
    msgstruct->msize = strlen(msgstruct->mtext);
    fclose(file);

    printf("A memoriaszegmensre kikerult uzenet:\n%s\n", msgstruct->mtext);

    shmdt(msgstruct);

    return 0;
}
