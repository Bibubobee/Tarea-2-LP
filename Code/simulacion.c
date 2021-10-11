#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Animal.c"
int main()
{
    srand((unsigned) time(0));
    char get[4];
    scanf("%4s", get);
    printf("%s\n", get);
}
