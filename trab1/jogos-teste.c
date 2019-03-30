/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#include "jogos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define FICH1 "./stats.txt"
#define FICH2 "./statsSaved.txt"
#define FICH3 "./errata.txt"

#define INICIA_TESTE() \
	int erros = 0;

#define ERRO(msg)            \
	{                        \
		printf("\n\t" #msg); \
		erros++;             \
	}

#define FINALIZA_TESTE() \
	if (!erros)          \
		printf("OK\n");  \
	else                 \
		printf("\n");    \
	return erros;

int teste_jogos_load()
{
	INICIA_TESTE()

	printf("jogos_load(): ");

	vetor *v = jogos_load(FICH1);
	if (!v)
	{
		printf("\n\terro na leitura do ficheiro '%s'", FICH1);
		erros++;
		FINALIZA_TESTE();
	}

	if (v->tamanho != 1140)
		ERRO("o vetor resultante deveria ter tamanho 1140")
	else{
		printf("Carregados 1140 jogos. ");
	}

	vetor_apaga(v);

	FINALIZA_TESTE()
}

int teste_jogos_save()
{
	INICIA_TESTE()

	printf("jogos_save(): ");

	vetor *v = jogos_load(FICH1);
	if (!v)
	{
		printf("\n\terro na leitura do ficheiro '%s'", FICH1);
		erros++;
		vetor_apaga(v);
		FINALIZA_TESTE();
	}

	remove(FICH2);

	if (jogos_save(v, FICH2) != 1140)
		ERRO("o valor de retorno deveria ser 1140")

	FILE *f = fopen(FICH2, "r");
	if (!f)
	{
		printf("\n\terro na leitura do ficheiro '%s'", FICH2);
		erros++;
		vetor_apaga(v);
		FINALIZA_TESTE();
	}

	fclose(f);
	vetor_apaga(v);

	FINALIZA_TESTE()
}

int teste_stats_equipa()
{
	INICIA_TESTE()

	printf("stats_equipa(): ");

	vetor *v = jogos_load(FICH1); 
	vetor_equipas * stats = stats_equipa(v);
	if(stats==NULL){
		printf("\n\terro na criação do vetor_equipas");
		erros++;
		vetor_apaga(v);
		vetor_equipas_apaga(stats);
		FINALIZA_TESTE();
	}

	if(stats->tamanho!=25){
		printf("\n\tnúmero de equipas no vetor devia ser de 25 ");
		erros++;
		vetor_apaga(v);
		vetor_equipas_apaga(stats);
		FINALIZA_TESTE();		
	}
	else{
		printf("Foram calculadas estatísticas para 25 equipas. ");
	}
	vetor_apaga(v);
	vetor_equipas_apaga(stats);

	FINALIZA_TESTE()
}

int teste_equipas_ordena()
{
	clock_t inicio, fim;
	double t_alfa, t_diff;

	INICIA_TESTE()

	printf("equipas_ordena(): ");

	vetor *v = jogos_load(FICH1);
	vetor_equipas * stats = stats_equipa(v);

	inicio = clock();
	equipas_ordena(stats, 0);
	fim = clock();
	t_alfa = (double)(fim - inicio) / CLOCKS_PER_SEC;
	if (strcmp(vetor_equipas_elemento(stats, 0)->nome_equipa, "Arsenal") != 0){
		ERRO("elemento inicial errado depois de ordenar por ordem alfabética.")}
	else{
		printf("\n\tElemento inicial quando ordenado por ordem alfabética: %s\n\t", vetor_equipas_elemento(stats, 0)->nome_equipa);
	}
	vetor_apaga(v);
	vetor_equipas_apaga(stats);
	v = jogos_load(FICH1);
	stats = stats_equipa(v);
	inicio = clock();
	equipas_ordena(stats, 1);
	fim = clock();
	t_diff = (double)(fim - inicio) / CLOCKS_PER_SEC;
	if (strcmp(vetor_equipas_elemento(stats, 0)->nome_equipa, "Stoke") != 0){
		ERRO("Elemento inicial errado depois de ordenar por diferenca de golos")}
	else{
		printf("Elemento inicial quando ordenado por diferença de golos: %s, com diferença de golos de %d",\
		vetor_equipas_elemento(stats,0)->nome_equipa, vetor_equipas_elemento(stats,0)->diff_golos);
	}
	vetor_apaga(v);
	vetor_equipas_apaga(stats);
	printf("\n\tTempo de execucao ordenacao por ordem alfabética (s): %f.", t_alfa);
	printf("\n\tTempo de execucao ordenacao por diferença de golos (s): %f.\n\t", t_diff);

	FINALIZA_TESTE()
}

int teste_corrige_jogo()
{
	INICIA_TESTE()

	printf("corrige_jogo(): ");
	vetor *v = jogos_load(FICH1);
	int corrigido =  corrige_jogo(v, FICH3);

	if(corrigido==-1){
		ERRO("Erro ao corrigir informação guardada no vetor vec");
	}
	vetor_apaga(v);
	FINALIZA_TESTE()
}

int teste_pontos_de_equipa()
{	
	INICIA_TESTE()

	printf("pontos_de_equipa(): ");
	vetor *v = jogos_load(FICH1); 
	corrige_jogo(v, FICH3); 
	int pontos = pontos_de_equipa(v, "Man_City", "17/18");  

	if(pontos==-1){
		ERRO("Erro ao calcular pontos do Man_City na época 17/18");
	}
	else{
		printf("O Man_City conquistou %d pontos na época 17/18. ", pontos);
	}
	vetor_apaga(v);

	FINALIZA_TESTE()
}


int main()
{

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int erros = 0;

	erros += teste_jogos_load();
	if (erros == 0)
	{
		erros += teste_jogos_save();
		erros += teste_stats_equipa();
		erros += teste_equipas_ordena();
		erros += teste_corrige_jogo();
		erros += teste_pontos_de_equipa();
	}

	if (!erros)
		printf("FIM DE TODOS OS TESTES.\n");
	else
		printf("FOI ENCONTRADO UM TOTAL DE %d ERROS.\n", erros);
	return 0;
}
