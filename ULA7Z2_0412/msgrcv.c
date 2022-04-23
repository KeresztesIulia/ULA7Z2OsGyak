#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 24601L

struct msgbuffer{
    long mtype;
    char mtext[50];
} receivebuffer;

struct msqid_ds msgstruct;

int main()
{
    int msgid;
    key_t key = MSGKEY;
    int msgflag, msgsize, mtype;

    msgflag = 00666 | IPC_CREAT | MSG_NOERROR;

    msgid = msgget(key, msgflag);

    msgsize = 50;
    mtype = 0;

    msgctl(msgid, IPC_STAT, &msgstruct);

    while(msgstruct.msg_qnum)
    {
        msgrcv(msgid, (struct msgbuf *)&receivebuffer, msgsize, mtype, msgflag);
        printf("Erezett uzenet: %s\n", receivebuffer.mtext);
         msgctl(msgid, IPC_STAT, &msgstruct);
    }

    exit(0);
}
