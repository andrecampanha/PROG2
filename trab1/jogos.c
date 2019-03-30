/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "jogos.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_STRING 30
#define N_EPOCAS 3
#define N_JOGOS_EPOCA 38


vetor* jogos_load(const char *nomef)
{
    vetor *vec = vetor_novo();
    if(vec == NULL)
        return NULL;

    FILE *fin = fopen(nomef, "r");
    if(fin == NULL)
        return NULL;
    
    jogo j;
    while(fscanf(fin, "%s %s %s %d %d %d %d",
        j.epoca, j.nome_casa, j.nome_fora, &j.golos_casa, &j.golos_fora, &j.vermelhos_casa, &j.vermelhos_fora) == 7)
    {
        if(vetor_insere(vec, j, -1) == -1) // Se der erro ao inserir no vetor, sair
        {
            fclose(fin);
            vetor_apaga(vec);
            return NULL;
        }
    }
    fclose(fin);
    return vec;
}


int jogos_save(vetor *vec, const char *nomef)
{
    if(vec == NULL)
        return -1;

    FILE *fout = fopen(nomef, "w");
    if(fout == NULL)
        return -1;

    int i;
    jogo *j;
    for(i = 0; i < vec->tamanho; i++)
    {
        j = vetor_elemento(vec, i);
        fprintf(fout, "%s %s %s %d %d %d %d\n",
            j->epoca, j->nome_casa, j->nome_fora, j->golos_casa, j->golos_fora, j->vermelhos_casa, j->vermelhos_fora);
    }
    fclose(fout);
    return i;
}

int equipa_insere_nova(vetor_equipas *vec_e, char *nome)
{
    equipa nova;
    nova.diff_golos = 0;
    memset(&nova.vermelhos, 0, N_EPOCAS * sizeof(float));
    strcpy(nova.nome_equipa, nome);

    return vetor_equipas_insere(vec_e, nova, -1);
}

vetor_equipas *stats_equipa(vetor *vec)
{
    if(vec == NULL)
        return NULL;

    vetor_equipas *vec_e = vetor_equipas_novo();
    if(vec_e == NULL)
        return NULL;

    int i, j, pos;

    jogo *jog;
    equipa *eq;

    int casa, fora;
    for(i = 0; i < vec->tamanho; i++)
    {
        jog = vetor_elemento(vec, i);
        casa = fora = -1;

        for(j = 0; j < vec_e->tamanho; j++) // Procurar as duas equipas do jogo no vetor de equipas
        {
            eq = vetor_equipas_elemento(vec_e, j);
            if(casa == -1 && strcmp(eq->nome_equipa, jog->nome_casa) == 0)
                casa = j;
            else if(fora == -1 && strcmp(eq->nome_equipa, jog->nome_fora) == 0)
                fora = j;

            if(casa != -1 && fora != -1) // Caso já tenha encontrado as duas equipas, sai do ciclo
                break;
        }
        
        // Caso alguma das equipas ainda não tenha sido inserida no vetor de equipas, insere
        if((casa == -1 && (casa = equipa_insere_nova(vec_e, jog->nome_casa)) == -1)
            || (fora == -1 && (fora = equipa_insere_nova(vec_e, jog->nome_fora)) == -1))
        {
            // Se ocorrer um erro ao inserir, elimina o vetor de equipas e retorna um erro
            vetor_equipas_apaga(vec_e);
            return NULL;
        }

        pos = jog->epoca[1] - '5'; // 15/16 -> 0, 16/17 -> 1, 17/18 -> 2

        // Casa
        eq = vetor_equipas_elemento(vec_e, casa);
        eq->diff_golos += jog->golos_casa - jog->golos_fora;        
        eq->vermelhos[pos] += jog->vermelhos_casa; 

        // Fora
        eq = vetor_equipas_elemento(vec_e, fora);
        eq->diff_golos += jog->golos_fora - jog->golos_casa;
        eq->vermelhos[pos] += jog->vermelhos_fora; 
    }

    for(i = 0; i < vec_e->tamanho; i++)
    {
        for(j = 0; j < N_EPOCAS; j++)
        {
            vetor_equipas_elemento(vec_e, i)->vermelhos[j] /= N_JOGOS_EPOCA;
        }
    }
    return vec_e;
}

void swap(equipa *e1, equipa *e2)
{
    equipa tmp;
    tmp = *e1;
    *e1 = *e2;
    *e2 = tmp;
}

int compara_equipas_alfabetico(equipa *e1, equipa *e2)
{
    return strcmp(e1->nome_equipa, e2->nome_equipa) <= 0;
}
int compara_equipas_diffgolos(equipa *e1, equipa *e2)
{
    return e1->diff_golos <= e2->diff_golos;
}

int quick_sort(vetor_equipas *v, int (*compara)(equipa*,equipa*), int left, int right)
{
    int i, j, tamanho = right - left + 1;
    if(tamanho < 2)
        return 1;
    
    int pos = rand() % tamanho + left;
    swap(vetor_equipas_elemento(v, pos), vetor_equipas_elemento(v, right));
    i = left;
    j = right - 1;

    equipa *vi, *vj, *vr;
    vi = vetor_equipas_elemento(v, i);
    vj = vetor_equipas_elemento(v, j);
    vr = vetor_equipas_elemento(v, right);

    while(1)
    {
        while (i < right && compara(vi, vr))
        {
            i++;
            vi = vetor_equipas_elemento(v, i);
        }
        while (j >= 0 && compara(vr, vj))
        {
            j--;
            vj = vetor_equipas_elemento(v, j);
        }
        if (i < j)
            swap(vi, vj);
        else
            break;
    }

    swap(vi, vr);
    quick_sort(v, compara, left, i-1);
    quick_sort(v, compara, i+1, right);

    return 1;
}

int equipas_ordena(vetor_equipas *v, int criterio)
{
    if(v == NULL)
        return -1;
    srand(time(NULL));

    int (*compara)(equipa*,equipa*);

    switch (criterio)
    {
        case 0:
            compara = compara_equipas_alfabetico;
            break;
        case 1:
            compara = compara_equipas_diffgolos;
            break;
        default:
            return -1;
    }
    return quick_sort(v, compara, 0, v->tamanho - 1);
    
}

int corrige_jogo(vetor *vec, const char *nomef)
{
    if(vec == NULL)
        return -1;

    FILE *fin = fopen(nomef, "r");
    if(fin == NULL)
        return -1;

    jogo j, *el;
    int i;
    while(fscanf(fin, "%s %s %s %d %d %d %d",
        j.epoca, j.nome_casa, j.nome_fora, &j.golos_casa, &j.golos_fora, &j.vermelhos_casa, &j.vermelhos_fora) == 7)
    {
        for(i = 0; i < vec->tamanho; i++)
        {
            el = vetor_elemento(vec, i);
            if(strcmp(el->epoca, j.epoca) == 0 && strcmp(el->nome_casa, j.nome_casa) == 0 && strcmp(el->nome_fora, j.nome_fora) == 0)
            {
                el->golos_casa = j.golos_casa;
                el->golos_fora = j.golos_fora;
                el->vermelhos_casa = j.vermelhos_casa;
                el->vermelhos_fora = j.vermelhos_fora;
                break;
            }
        }
    }

    fclose(fin);
    return 0;
}

int pontos_de_equipa(vetor *vec, char *nome_equipa, char *epoca)
{
    if(vec == NULL)
        return -1;
        
    int i, count = 0;
    jogo *el;
    for(i = 0; i < vec->tamanho; i++)
    {
        el = vetor_elemento(vec, i);
        if(strcmp(epoca, el->epoca) == 0)
        {
            if(strcmp(nome_equipa, el->nome_casa) == 0)
            {
                if(el->golos_casa > el->golos_fora)
                    count += 3;
                else if(el->golos_casa == el->golos_fora)
                    count++;
            }
            else if(strcmp(nome_equipa, el->nome_fora) == 0)
            {
                if(el->golos_fora > el->golos_casa)
                    count += 3;
                else if(el->golos_fora == el->golos_casa)
                    count++;
            }
        }
    }
    return count;
}



