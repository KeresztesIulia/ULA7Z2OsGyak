#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* file = fopen("Keresztes.txt", "r+");
    int nevhossz = 15;
    int szakhossz = 27;
    int NKhossz = 6;
    char nev[nevhossz+1], szak[szakhossz + 1], NK[NKhossz + 1];

    fread(nev,sizeof(char), nevhossz, file);
    nev[nevhossz] = '\0';
    printf("%s", nev);

    fread(szak,sizeof(char), szakhossz, file);
    szak[szakhossz] = '\0';
    printf("%s", szak);

    fread(NK,sizeof(char), NKhossz, file);
    NK[NKhossz] = '\0';
    printf("%s", NK);

    fclose(file);

    getchar();
    return 0;
}
