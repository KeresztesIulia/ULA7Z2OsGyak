#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int size = 100;
    char buffer[size];
    int fileDescriptor;
    int writeInfo;
    int seekInfo;
    int readInfo;

    fileDescriptor = open("ULA7Z2.txt", O_RDWR);
    if(fileDescriptor == -1)
    {
        perror("open error");
        exit(fileDescriptor);
    }
    printf("File descriptor erteke: %d\n", fileDescriptor);

    seekInfo = lseek(fileDescriptor,0,SEEK_SET);
    if(seekInfo == -1)
    {
        perror("A pozicionalas nem volt sikeres!");
        exit(seekInfo);
    }

    readInfo = read(fileDescriptor, buffer, size);
    if(readInfo == -1)
    {
        perror("sikertelen olvasas");
        exit(readInfo);
    }
    printf("read() erteke: %d\n", readInfo);
    printf("A beolvasott szoveg: %s\n", buffer);

    strcpy(buffer, "Valami szoveg, hogy legyen mit write-oljon");
    writeInfo = write(fileDescriptor, buffer, strlen(buffer));

    if(writeInfo == -1)
    {
        perror("sikertelen iras");
        exit(writeInfo);
    }
    printf("Kiiras mennyisege: %d\n", writeInfo);


    return 0;
}
