/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#ifndef JOGOS_H
#define JOGOS_H

#include "vetor.h"

/**
 * coloca num vetor inicialmente vazio a informacao contida no ficheiro de texto
 * parametro: nomef nome do ficheiro
 * retorno: apontador para o vetor criado
 * nota: se ocorrer algum erro na leitura do ficheiro ou vetor nao foi criado retorna NULL
 */
vetor* jogos_load(const char *nomef);


/**
 * coloca num ficheiro de texto inicialmente vazio a informacao contida no vetor
 * parametro: nomef nome do ficheiro
 * parametro: vec apontador para o vetor
 * retorno: -1 se aconteceu algum erro ou número de elementos guardados no ficheiro
 */
int jogos_save(vetor *vec, const char *nomef);


/**
*  lê o conteúdo do vetor vec e calcula as estatísticas referidas por equipa: 
*  nome da equipa; total de diferença de golos nas três épocas, média de cartões vermelhos por época
*  parametro: vec apontador para o vetor
*  retorno: apontador para o vetor_equipas criado. Em caso de erro, retornar NULL
*/
vetor_equipas *stats_equipa(vetor *vec);


/**
*  ordena equipas de forma crescente de acordo com o critério especificado 
*  usando o algoritmo quicksort
*  parametro: apontador para o vetor_equipas
*  parametro: critério a utilizar (se 0: ordenar equipas por ordem alfabética, 
*  se 1: ordenar equipas por diferença de golos)
*  retorno: -1 se ocorrer um erro ou 0 se for bem sucedido
*/
int equipas_ordena(vetor_equipas *v, int criterio);


/*
* Corrige a informação guardado no vetor vec (referente a resultado e
* número de cartões vermelhos).
* parametro: apontador para o vetor de jogos vec
* parametro: nomef nome do ficheiro
* retorno: -1 se ocorrer erro ou 0 se for bem sucedido.
*/
int corrige_jogo(vetor *vec, const char *nomef);

/**
calcula o número de pontos de uma determinada equipa numa determinada época
* Épocas em análise: 15/16, 16/17, e 17/18
* parametro: apontador para o vetor vec
* parametro: nome_equipa nome da equipa a pesquisar
* parametro: epoca época que queremos pesquisar
* retorno: número de pontos da equipa na época em questão
* nota: se ocorrer algum erro retornar -1
*/
int pontos_de_equipa(vetor *vec, char *nome_equipa, char *epoca);

#endif
