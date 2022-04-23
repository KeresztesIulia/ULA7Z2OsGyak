#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 24601L

int main()
{
    int msgid, msgflag;
    key_t key = MSGKEY;
    msgflag = 00666;
    msgid = msgget(key, msgflag);

    msgctl(msgid, IPC_RMID, NULL);

    exit(0);
}
