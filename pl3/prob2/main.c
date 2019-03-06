#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 50

typedef struct
{
    char pais[MAX_STRING], capital[MAX_STRING];
    int habitantes;
} capital;

capital* analisarFicheiro(FILE *ficheiro, int *num_capitais)
{
    int vec_size = 1;
    *num_capitais = 0;
    capital* vec = malloc(sizeof(capital) * vec_size);

    while(fscanf(ficheiro, "%s %s %d", vec[*num_capitais].pais, vec[*num_capitais].capital, &vec[*num_capitais].habitantes) == 3)
    {
        (*num_capitais)++;
        if(*num_capitais >= vec_size)
        {
            vec_size *= 2;
            vec = realloc(vec, sizeof(capital) * vec_size);
        }
    }

    if(vec_size != *num_capitais)
        vec = realloc(vec, sizeof(capital) * (*num_capitais));

    return vec;
}

void gerarRelatorio(char *nome_ficheiro, capital *resultados, int num_capitais)
{
    capital **order = malloc(sizeof(capital*) * num_capitais);
    for(int i = 0; i < num_capitais; i++)
        order[i] = &resultados[i];
    
    FILE *f = fopen(nome_ficheiro, "w");
    if(f == NULL)
    {
        printf("Erro a escrever o relatório!\n");
        return;
    }

    int max;
    capital *temp;
    for(int i = 0; i < num_capitais - 1; i++)
    {
        max = i;
        for(int j = i + 1; j < num_capitais; j++)
        {
            if(order[j]->habitantes > order[max]->habitantes)
                max = j;
        }
        temp = order[i];
        order[i] = order[max];
        order[max] = temp;
    }

    fprintf(f, "Capitais:\n");
    for(int i = 0; i < num_capitais; i++)
    {
        fprintf(f, "%d - %s - %s - %d\n", i + 1, order[i]->capital, order[i]->pais, order[i]->habitantes);
    }
    fprintf(f, "---\ntotal: %d capitais", num_capitais);
    fclose(f);
    free(order);
}

int main(int argc, char const *argv[])
{
    char in_file[MAX_STRING], out_file[MAX_STRING];
    printf("Ficheiro de entrada e saída: ");
    scanf("%s %s", in_file, out_file);

    FILE *fin = fopen(in_file, "r");
    if(fin == NULL)
    {
        printf("Erro a abrir o ficheiro!\n");
        return 0;
    }

    int num_capitais;
    capital *capitais = analisarFicheiro(fin, &num_capitais);

    gerarRelatorio(out_file, capitais, num_capitais);

    fclose(fin);
    free(capitais);
    return 0;
}
