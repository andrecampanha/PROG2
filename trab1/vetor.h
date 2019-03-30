/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#ifndef VETOR_H

/**
* registo para armazenar cada elemento (um jogo neste caso)
*/
typedef struct
{
  char epoca[6];
  char nome_casa[30];
  char nome_fora[30];
  int golos_casa;
  int golos_fora; 
  int vermelhos_casa; 
  int vermelhos_fora;
} jogo;


/**
 * registo para armazenar cada elemento (informação sobre uma equipa neste caso)
*/
typedef struct{
  char nome_equipa[30];
  int diff_golos; 
  float vermelhos[3];
} equipa;

/**
* este registo contem um vetor de elementos, um contador do tamanho e outro para a capacidade
*/
typedef struct
{
  /** numero de elementos do vetor */
  int tamanho;

  /** capacidade do vetor */
  int capacidade;

  /** array de elementos (jogos) armazenados */
  jogo* elementos;

} vetor;


/**
* este registo contem um vetor_equipas de elementos, um contador do tamanho e outro para a capacidade
*/
typedef struct
{
  /** numero de elementos do vetor */
  int tamanho;

  /** capacidade do vetor */
  int capacidade;

  /** array de elementos (equipas) armazenados */
  equipa* elementos;

} vetor_equipas;

/**
*  cria um novo vetor com tamanho 0 e capacidade 0
*  retorno: apontador para o vetor criado
*  nota: se vetor nao foi criado retorna NULL
*/
vetor* vetor_novo();

/**
*  cria um novo vetor_equipas com tamanho 0 e capacidade 0
*  retorno: apontador para o vetor_equipas criado
*  nota: se vetor_equipas nao foi criado retorna NULL
*/
vetor_equipas* vetor_equipas_novo();

/**
*  elimina um vetor, libertando toda a memoria ocupada
*  parametro: vec apontador para vetor
*  nota: se vec = NULL retorna sem fazer nada
*/
void vetor_apaga(vetor *vec);

/**
*  elimina um vetor_equipas, libertando toda a memoria ocupada
*  parametro: vec_eq apontador para vetor_equipas
*  nota: se vec_eq = NULL retorna sem fazer nada
*/
void vetor_equipas_apaga(vetor_equipas *vec_eq);

/**
*  indica o o numero de elementos do vetor
*  parametro: vec apontador para vetor
*  retorno: -1 se ocorrer algum erro ou numero de elementos do vetor
*/
int vetor_tamanho(vetor *vec);

/**
*  indica o o numero de elementos do vetor_equipas
*  parametro: vec_eq apontador para vetor_equipas
*  retorno: -1 se ocorrer algum erro ou numero de elementos do vetor_equipas
*/
int vetor_equipas_tamanho(vetor_equipas *vec_eq);

/**
*  retorna o elemento armazenado na posicao especificada
*  parametro: vec apontador para vetor
*  parametro: pos indice do elemento
*  retorno: apontador para o elemento (jogo) na posicao correspondente
*  nota: se ocorrer algum erro retorna NULL (p.ex. se valor pos indicar uma posicao invalida)
*/
jogo* vetor_elemento(vetor *vec, int pos);


/**
*  retorna o elemento armazenado na posicao especificada
*  parametro: vec_eq apontador para vetor_equipas
*  parametro: pos indice do elemento
*  retorno: apontador para o elemento (equipa) na posicao correspondente
*  nota: se ocorrer algum erro retorna NULL (p.ex. se valor pos indicar uma posicao invalida)
*/
equipa* vetor_equipas_elemento(vetor_equipas *vec_eq, int pos);

/**
*  insere um elemento na posicao especificada
*  parametro: vec apontador para vetor
*  parametro: jogo1 elemento (jogo) a inserir
*  parametro: pos indice do vetor onde se pretende inserir o jogo, se pos=tamanho ou pos=-1 insere no fim do vetor
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou o valor de pos se bem sucedido
*  nota: se a capacidade nao for suficiente para guardar novo elemento, devera ser aumentada para 2x em relacao a capacidade anterior; inicialmente aumenta para capacidade 1
*/
int vetor_insere(vetor *vec, jogo jogo1, int pos);

/**
*  insere um elemento na posicao especificada
*  parametro: vec_eq apontador para vetor_equipas
*  parametro: equipa1 elemento (equipa) a inserir
*  parametro: pos indice do vetor_equipas onde se pretende inserir a equipa, se pos=tamanho ou pos=-1 insere no fim do vetor_equipas
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou o valor de pos se bem sucedido
*  nota: se a capacidade nao for suficiente para guardar novo elemento, devera ser aumentada para 2x em relacao a capacidade anterior; inicialmente aumenta para capacidade 1
*/
int vetor_equipas_insere(vetor_equipas *vec_eq, equipa equipa1, int pos);

/**
*  remove o elemento da posicao especificada
*  parametro: vec apontador para vetor
*  parametro: pos posicao
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou 0 se bem sucedido
*/
int vetor_remove(vetor* vec, int pos);


/**
*  remove o elemento da posicao especificada
*  parametro: vec_eq apontador para vetor_equipas
*  parametro: pos posicao
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou 0 se bem sucedido
*/
int vetor_equipas_remove(vetor_equipas* vec_eq, int pos);

/**
*  atribui o valor especificado a uma posicao
*  parametro: vec apontador para vetor
*  parametro: pos posicao onde colocar elemento
*  parametro: jogo1 elemento (jogo) a colocar na posicao pos do vetor
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou pos se bem sucedido
*/
int vetor_atribui(vetor *vec, int pos, jogo jogo1);


/**
*  atribui o valor especificado a uma posicao
*  parametro: vec_eq apontador para vetor_equipas
*  parametro: pos posicao onde colocar elemento
*  parametro: equipa1 elemento (equipa) a colocar na posicao pos do vetor_equipas
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou pos se bem sucedido
*/
int vetor_equipas_atribui(vetor_equipas *vec_eq, int pos, equipa equipa1);

#define VETOR_H
#endif
