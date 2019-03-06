#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vetor.h"

#define PATH "plantas.txt"
#define MAX_STRING 500

vetor* ler_ficheiro(char *ficheiro)
{
    FILE *fin = fopen(ficheiro, "r");
    if(fin == NULL) return NULL;
    vetor *v = vetor_novo();

    char temp[MAX_STRING];
    while(fgets(temp, MAX_STRING, fin) != NULL)
    {
        if(temp[strlen(temp) - 1] == '\n')
            temp[strlen(temp) - 1] = '\0';
        vetor_insere(v, temp, vetor_tamanho(v));
    }

    return v;
}

void vetor_imprime(vetor *vec)
{
    for(int i = 0; i < vetor_tamanho(vec); i++)
        printf("[%d] %s\n", i, vetor_elemento(vec, i));
}

int main(int argc, char const *argv[])
{
    vetor *vec = ler_ficheiro(PATH);
    printf("Foram lidas %d plantas!\n", vetor_tamanho(vec));
    vetor_imprime(vec);
    printf("A planta Podocarpus macrophyllus (Thunberg) encontra-se na posição %d.\n", vetor_pesquisa(vec, "Podocarpus macrophyllus (Thunberg)"));

    vetor_ordena(vec);
    printf("Vetor ordenado:\n");
    vetor_imprime(vec);

    int count = vetor_num_ocorrencias(vec, "Ginkgo biloba (L.)");
    printf("A planta Ginkgo biloba (L.) aparece %d vezes no vetor.\n", count);

    vetor_remove_repetidas(vec);
    printf("Após remoção das plantas repetidas o vetor tem %d posições.\n", vetor_tamanho(vec));

    vetor *pesquisa = vetor_pesquisa_parcial(vec, "Acacia");
    printf("Pesquisar por: Acacia\n");
    vetor_imprime(pesquisa);

    vetor_apaga(pesquisa);
    vetor_apaga(vec);
    return 0;
}
