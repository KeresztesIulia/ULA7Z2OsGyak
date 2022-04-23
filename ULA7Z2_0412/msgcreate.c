#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSGKEY 24601L

struct msgbuffer{
    long mtype;
    char mtext[50];
} sendbuffer;

int main()
{
    int msgid;
    key_t key = MSGKEY;
    int msgflag, msgsize;

    msgflag = 00666 | IPC_CREAT;
    msgid = msgget(key, msgflag);

    sendbuffer.mtype = 1;

    strcpy(sendbuffer.mtext, "Az elso uzenet");
    msgsize = strlen(sendbuffer.mtext) + 1;
    msgsnd(msgid, (struct msgbuf *)&sendbuffer, msgsize, msgflag);

    strcpy(sendbuffer.mtext, "A masodik uzenet ami az uzenetsorba kerult");
    msgsize = strlen(sendbuffer.mtext) + 1;
    msgsnd(msgid, (struct msgbuf *)&sendbuffer, msgsize, msgflag);

    exit(0);
}
