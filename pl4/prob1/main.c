#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

#define PATH "arquivo.txt"
#define PATH2 "jogos2.txt"
#define PATH_OLDIES "oldies.txt"
#define MAX_STRING 255

lista* ler_ficheiro(char *path)
{
    char tmp[MAX_STRING];
    FILE *fin = fopen(path, "r");
    if(fin == NULL) return NULL;
    
    lista *lst = lista_nova();

    while(fgets(tmp, MAX_STRING, fin) != NULL)
    {
        if(tmp[strlen(tmp) - 1] == '\n')
            tmp[strlen(tmp) - 1] = '\0';
        lista_insere(lst, tmp, NULL);
    }

    return lst;
}

void print_lista(lista *lst)
{
    l_elemento *el = lista_inicio(lst);
    int i = 0;
    while(el != NULL)
    {
        printf("[%d] %s\n", i, el->str);
        el = el->proximo;
        i++;
    }
}

void guardar_lista(lista *lst, char *path)
{
    FILE *fout = fopen(path, "w");
    if(fout == NULL) return;

    l_elemento *el = lista_inicio(lst);
    while(el != NULL)
    {
        fprintf(fout, "%s\n", el->str);
        el = el->proximo;
    }
}

int main(int argc, char const *argv[])
{
    lista *lst = ler_ficheiro(PATH);

    printf("Foram carregados %d jogos.\n", lista_tamanho(lst));
    print_lista(lst);

    lista *ps2 = lista_pesquisa_substring(lst, "PS2");
    printf("\n-----\n\nJogos PS2\n\n");
    print_lista(ps2);
    lista_apaga(ps2);

    l_elemento *el = lst->inicio;
	while(el != NULL)
	{
		if (strstr(el->str, "PS2") != NULL)
			lista_remove(lst, el);
		el = el->proximo;
	}
    printf("\n---\n\nApos remocao de jogos PS2 a lista tem %d jogos.\n", lst->tamanho);
    guardar_lista(lst, PATH2);

    lista *oldies = ler_ficheiro(PATH_OLDIES);
    printf("\n---\n\nForam carregados %d jogos antigos:\n", oldies->tamanho);
    print_lista(oldies);

    lista_concatena(lst, oldies);
    lista_apaga(oldies);
    printf("\n---\n\nApos concatenacao, a lista final contem %d jogos:\n", lst->tamanho);
    print_lista(lst);

    lista_ordena(lst);
    printf("\n---\n\nLista ordernada:\n");
    print_lista(lst);


    int i = 0;
    for (el = lst->inicio; el != NULL; el = el->proximo)
    {
        if (strcmp(el->str, "Duke Nukem (PS3)") == 0) break;
        i++;
    }
    printf("\n---\n\nO jogo Duke Nukem (PS3) encontra-se na posicao %d.\n", i);

    int pos = lista_insere_ordenada(lst, "j");
    printf("O jogo Minesweeper (PC) foi inserido na posicao %d.\n", pos);
    print_lista(lst);

    lista_apaga(lst);
    return 0;
}
