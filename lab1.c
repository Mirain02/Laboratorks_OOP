#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(void)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    printf("Hello, world!");
    return 0;
}
