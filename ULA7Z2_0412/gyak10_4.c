#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MSGKEY 24601J

struct msgbuffer{
    long mtype;
    char mtext[50];
} sendbuffer, receivebuffer;

struct msqid_ds msgstruct;

void send(int msgid, int msgsize, int msgflag, char* msg)
{
    sendbuffer.mtype = 1;

    strcpy(sendbuffer.mtext, msg);
    msgsize = strlen(sendbuffer.mtext) + 1;
    msgsnd(msgid, (struct msgbuf *)&sendbuffer, msgsize, msgflag);
}

void receive(int msgsize, int msgid, int msgflag)
{
    int mtype = 0;
    msgrcv(msgid, (struct msgbuf *)&receivebuffer, msgsize, mtype, msgflag);
    printf("Erkezett uzenet: %s\n", receivebuffer.mtext);
}
void receiveAll(int msgsize, int msgid, int msgflag)
{

    msgctl(msgid, IPC_STAT, &msgstruct);

    while(msgstruct.msg_qnum)
    {
        receive(msgsize, msgid, msgflag);
         msgctl(msgid, IPC_STAT, &msgstruct);
    }
    return;
}



int main()
{
    int msgid;
    key_t key = MSGKEY;
    int msgflag, msgsize;

    msgflag = 00666 | IPC_CREAT;
    msgid = msgget(key, msgflag);
    msgsize = 50;

    pid_t pid = fork();

    if(pid != 0)
    {
        wait(NULL);
    }
    if(pid == 0)
    {
        send(msgid, msgsize, msgflag, "Elso uzenet");
        send(msgid, msgsize, msgflag, "Masodik uzenet");
        send(msgid, msgsize, msgflag, "Harmadik uzenet");
        send(msgid, msgsize, msgflag, "Negyedik uzenet");
        exit(0);
    }
    if(pid != 0)
    {
        printf("Mit szeretne csinalni?\n- uzenetek szamanak lekerdezese (s)\n- elso uzenet kiolvasasa (e)\n- osszes uzenet kiolvasasa (k)\n- uzenetsor torlese (t)\n- kilepes (barmilyen karakter az elozoeken kivul)\n");
        char option;
        scanf(" %c", &option);
        switch (option)
        {
            case 's':
                msgctl(msgid, IPC_STAT, &msgstruct);
                printf("%lu", msgstruct.msg_qnum);
                break;
            case 'e':
                receive(msgsize, msgid, msgflag);
                break;
            case 'k':
                receiveAll(msgsize, msgid, msgflag);
                break;
            case 't':
                msgctl(msgid, IPC_RMID, NULL);//clear
                break;
            default:
                printf("Kilepes");
                exit(0);
                break;
        }
    }



    exit(0);
}
