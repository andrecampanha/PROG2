#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int *vec;
    int tam;

    printf("Número de elementos: "); scanf("%d", &tam);
    vec = malloc(tam * sizeof(int));

    for(int i = 0; i < tam; i++)
    {
        printf("Introduza o %dº elemento: ", i + 1); scanf("%d", &vec[i]);
    }

    printf("Vetor original: [ ");
    for(int i = 0; i < tam; i++) printf("%d ", vec[i]);
    printf("]\n");


    printf("Números pares: [ ");
    for(int i = 0; i < tam; i++)
        if(vec[i] % 2 == 0) printf("%d ", vec[i]);
    printf("]\n");

    printf("Números impares: [ ");
    for(int i = 0; i < tam; i++)
        if(vec[i] % 2 != 0) printf("%d ", vec[i]);
    printf("]\n");


}