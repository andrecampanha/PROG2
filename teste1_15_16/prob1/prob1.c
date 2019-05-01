#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vetor.h"
#include "lista.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

void retira_duplicados(vetor *vec) {
    if(vec == NULL) return;
    for(int i = 0; i < vec->tamanho; i++)
    {
        for(int j = i + 1; j < vec->tamanho; j++)
        {
            if(strcmp(vetor_elemento(vec, i), vetor_elemento(vec, j)) == 0)
            {
                vetor_remove(vec, j);
                j--;
            }
        }
    }
}

vetor *interseta(lista *l1, lista *l2)
{
    vetor *res = vetor_novo();
    elemento *e1, *e2;

    for(e1 = l1->inicio; e1 != NULL; e1 = e1->proximo)
    {
        for(e2 = l2->inicio; e2 != NULL; e2 = e2->proximo)
        {
            if(strcmp(e1->str, e2->str) == 0)
            {
                vetor_insere(res, e1->str, res->tamanho);
                break;
            }
        }
    }
    if(res->tamanho == 0) return NULL;
    return res;
}

vetor *anteriores(lista *lst, const int ano)
{
    vetor *res = vetor_novo();

    elemento *e;
    int e_ano;
    char ano_str[5];
    for(e = lst->inicio; e != NULL; e = e->proximo)
    {
        strcpy(ano_str, e->str + strlen(e->str) - 5);
        ano_str[4] = '\0';
        e_ano = atoi(ano_str);
        if(e_ano < ano)
            vetor_insere(res, e->str, res->tamanho);
    }

    return res;
}


/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

vetor *lerAtores(FILE *ficheiro) {
    char buffer[256], *nlptr;
    vetor *atores;

    if (ficheiro == NULL)
        return NULL;

    atores = vetor_novo();

    while (!feof(ficheiro)) {
        fgets(buffer, 255, ficheiro);
        nlptr = strchr(buffer, '\n');
        if (nlptr)
            *nlptr = '\0';

        vetor_insere(atores, buffer, atores->tamanho);
    }

    return atores;
}

lista *lerFilmes(FILE *ficheiro) {
    char buffer[256], *nlptr;
    lista *filmes;

    if (ficheiro == NULL)
        return NULL;

    filmes = lista_nova();

    while (!feof(ficheiro)) {
        fgets(buffer, 255, ficheiro);
        nlptr = strchr(buffer, '\n');
        if (nlptr)
            *nlptr = '\0';

        lista_insere(filmes, buffer, NULL);
    }

    return filmes;
}

int main() {
    FILE *fa, *ff, *ff2;
    vetor *atores, *resultado, *resultado1;
    lista *filmes, *filmes2;

    /* testes */
    fa = fopen("atores2.txt", "r");
    ff = fopen("filmes.txt", "r");
    ff2 = fopen("filmes2.txt", "r");

    atores = lerAtores(fa);
    filmes = lerFilmes(ff);
    filmes2 = lerFilmes(ff2);

    /* testa retira_duplicados */
    printf("Total inicial: %d\n", vetor_tamanho(atores));
    retira_duplicados(atores);
    printf("Unicos: %d (esperado: 30)\n\n", vetor_tamanho(atores));

    /* testa interseta */
    resultado = interseta(filmes, filmes2);
    if (resultado)
        printf("Intersecao: %d (esperado: 75)\n", vetor_tamanho(resultado));
    else
        printf("Intersecao: vetor NULL\n");

    /* testa anteriores */
    resultado1 = anteriores(filmes, 2000);
    if (resultado1)
        printf("\nAnteriores: %d (esperado: 107)\n", vetor_tamanho(resultado1));
    else
        printf("\nAnteriores: vetor NULL\n");

    vetor_apaga(atores);
    vetor_apaga(resultado);
    vetor_apaga(resultado1);
    lista_apaga(filmes);
    lista_apaga(filmes2);

    fclose(fa);
    fclose(ff);
    fclose(ff2);

    return 0;
}
