#include <stdio.h>
#include <stdlib.h>

int main()
{
    int parancsMaxMeret = 50;
    char parancs[parancsMaxMeret];
    do
    {
        printf("Milyen parancsot szeretne futtatni? (kilepeshez ctrl+C)\n");
        scanf(" %s", parancs);
        int letezik = system(parancs);
        if (letezik != 0)
        {
            printf("A parancs nem letezik\n");
        }
    }while(1);

    return 0;
}
