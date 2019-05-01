#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"

arvore_avl *avl_read(FILE *fin)
{
    arvore_avl *avl = avl_nova();
    char str[500];
    char *token;
    no_avl *no;

    while(fgets(str, 500, fin) != NULL)
    {
        str[strlen(str) - 1] = '\0';
        strtok(str, ",");
        token = strtok(NULL, ",");
        if((no = avl_pesquisa(avl, token)) != NULL)
        {
            no->cont++;
        }
        else if(avl_insere(avl, token, 1) == -1) 
        {
            avl_apaga(avl);
            return NULL;
        }
    }

    return avl;
}

int main(int argc, char const *argv[])
{
    FILE *fin = fopen("cidades.txt", "r");
    if(fin == NULL) return 0;

    arvore_avl *avl = avl_read(fin);

    printf("Portugal: %d\n", avl_pesquisa(avl, "Portugal")->cont);
    printf("Spain: %d\n", avl_pesquisa(avl, "Spain")->cont);
    printf("Russia: %d\n", avl_pesquisa(avl, "Russia")->cont);

    return 0;
}
