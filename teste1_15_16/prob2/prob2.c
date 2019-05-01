#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    char palavra[100];
    int ocorrencias;
} registo;

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** exercicio 2.1 ***/
registo *analisarFicheiro(FILE *ficheiro, int *num_palavras)
{
    registo *vetor = malloc(sizeof(registo));
    *num_palavras = 0;
    int capacidade = 1;
    char str[100];
    int flag;

    while(fscanf(ficheiro, "%s", str) == 1)
    {
        flag = 0;
        for(int i = 0; i < *num_palavras; i++)
        {
            if(strcmp(vetor[i].palavra, str) == 0)
            {
                vetor[i].ocorrencias++;
                flag = 1;
            }
        }
        if(!flag)
        {
            if(capacidade == *num_palavras)
            {
                capacidade *= 2;
                vetor = realloc(vetor, sizeof(registo) * capacidade);
            }

            strcpy(vetor[*num_palavras].palavra, str);
            vetor[*num_palavras].ocorrencias = 1;
            (*num_palavras)++;
        }
    }

    return vetor;
}

/*** exercicio 2.2 ***/
void gerarRelatorio(FILE *ficheiro, registo *resultados, int num_palavras)
{
    fprintf(ficheiro, "Palavra encontradas:\n-----------------------\n");
    for(int i = 0; i < num_palavras; i++)
    {
        fprintf(ficheiro, "%d\t%s (%d)\n", i + 1, resultados[i].palavra, resultados[i].ocorrencias);
    }
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main() {
    FILE *fin, *fout;
    char nomeIn[50], nomeOut[50];
    registo *resultados;
    int n;

    printf("Ficheiro de entrada? ");
    scanf("%s", nomeIn);
    printf("Ficheiro de saida? ");
    scanf("%s", nomeOut);

    fin = fopen(nomeIn, "r");
    if (fin == NULL)
        return 1;

    fout = fopen(nomeOut, "w");
    if (fout == NULL)
        return 1;

    resultados = analisarFicheiro(fin, &n);
    gerarRelatorio(fout, resultados, n);

    fclose(fin);
    fclose(fout);
    free(resultados);

    return 0;
}