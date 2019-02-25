#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 81
#define N_STRINGS 3

int main()
{
    char *vec[N_STRINGS] = {NULL};
    char aux[MAX_STRING + 1];
    int pos;

    do
    {
        for(int i = 0; i < N_STRINGS; i++)
            printf("[%d] %s\n", i + 1, vec[i] == NULL ? "(vazio)" : vec[i]);

        printf("Posição da nova string (1 a %d): ", N_STRINGS); scanf("%d", &pos);
        pos--;
        getchar();
        if(pos < 0 || pos >= N_STRINGS)
            continue;

        printf("Nova string: ");
        fgets(aux, MAX_STRING + 1, stdin);
        aux[strlen(aux) - 1] = '\0';

        if(vec[pos] != NULL)
            free(vec[pos]);
        vec[pos] = malloc(strlen(aux) + 1);
        strcpy(vec[pos], aux);
    } while(pos != -1);

    for(int i = 0; i < N_STRINGS; i++)
    {
        free(vec[i]);
    }
}