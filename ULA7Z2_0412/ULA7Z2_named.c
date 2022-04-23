#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fileDescriptor;
    int pid = fork();
    char buffer[] = "Keresztes Iulia";

    if(pid != 0)
    {
        fileDescriptor = mkfifo("ULA7Z2.txt", O_RDWR);
        close(fileDescriptor);
    }
    if(pid == 0)
    {
        fileDescriptor = open("ULA7Z2.txt", O_RDWR);
        write(fileDescriptor,buffer,strlen(buffer));
        close(fileDescriptor);
        exit(0);
    }
    if(pid != 0)
    {
        fileDescriptor = open("ULA7Z2.txt", O_RDWR);
        read(fileDescriptor, buffer, 20);
        printf("%s", &buffer);
        close(fileDescriptor);
    }
    return 0;
}
