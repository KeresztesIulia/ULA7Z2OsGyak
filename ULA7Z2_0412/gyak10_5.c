#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

#define SHMKEY 24601L

struct msgbuff {
    int msize;
    char mtext[512];
} *msgstruct;

struct shmid_ds shmstruct;

int main()
{
    int shmid, shmflag, size = 512;
    key_t key = SHMKEY;
    pid_t pid;

    shmflag = 0;
    pid = fork();

    if(pid == 0)
    {
        shmid = shmget(key, size, shmflag);
        if(shmid < 0)
        {
            shmflag = 00666|IPC_CREAT;
            shmid = shmget(key, size, shmflag);
        }
        exit(0);
    }
    if(pid != 0)
    {
        shmid = shmget(key, size, shmflag);
        shmflag = 00666 | SHM_RND;
        msgstruct = (struct msgbuff *)shmat(shmid, NULL, shmflag);

        if(strlen(msgstruct->mtext) > 0)
        {
            printf("Uzenet a memoriaszegmensen: %s, hossz: %d\n", msgstruct->mtext, msgstruct->msize);
        }
        printf("Mi legyen az uj uzenet?\n");
        scanf("%[^\n]", msgstruct->mtext);
        printf("Az uj uzenet: %s\n", msgstruct->mtext);
        msgstruct->msize = strlen(msgstruct->mtext);

        shmdt(msgstruct);

        pid_t pid2 = fork();
        if(pid2 == 0)
        {
            printf("Mit szeretne csinalni?\n");
            printf("- státusz lekérése (s)\n");
            printf("- osztott memoria megszuntetese (e)\n");
            printf("- kilepes (elozo betuktol eltero)\n");
            char option;
            scanf(" %c", &option);
            switch (option)
            {
                case 's'|'S':
                    shmctl(shmid, IPC_STAT, &shmstruct);
                    printf("Szegmens merete: %lu\n", shmstruct.shm_segsz);
                    printf("PID: %d\n", shmstruct.shm_lpid);
                    break;
                case 'e'|'E':
                    shmctl(shmid, IPC_RMID, NULL);
                    printf("Szegmens torolve.\n");
                    break;
                default:
                    printf("Kilepes");
                    exit(0);
                    break;
            }
        }
        if(pid2 != 0)
        {
            wait(NULL);
            wait(NULL);
        }

    }


    return 0;
}
