#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "market.h"

#define MAX_CATEGNAME_LEN 100
#define CAP_ALL_CATEG 10

#pragma region VECTOR

#define V_INIT(vec) vector_t *vec = malloc(sizeof(vector_t)); vector_init(vec)
#define V_SET(vec, elem, pos) vector_set(vec, (void *) elem, pos)
#define V_GET(vec, type, pos) ((type) vector_get(vec, pos))
#define V_REMOVE(vec, pos) vector_remove(vec, pos)
#define V_FREE(vec) vector_free(vec); free(vec)

typedef struct vector_
{
    void **data;
    int len;
    int capacity;
} vector_t;

void vector_init(vector_t *v)
{
    v->data = NULL;
    v->len = 0;
    v->capacity = 0;
}

void vector_set(vector_t *v, void *elem, int pos)
{
    if(pos < -1 || pos > v->len) return;
    
    if(v->data == NULL || v->capacity == 0)
    {
        v->capacity = 10;
        v->data = malloc(sizeof(void*) * v->capacity);
    }


    if(pos == -1)
    {
        pos = v->len;

        if(v->capacity == v->len)
        {
            v->capacity *= 2;
            v->data = realloc(v->data, sizeof(void*) * v->capacity);
        }
        v->len++;
    }

    v->data[pos] = elem;
}

void *vector_get(vector_t *v, int pos)
{
    if(pos < 0 || pos > v->len) return NULL;
    return v->data[pos];
}

void vector_remove(vector_t *v, int pos)
{
    if(pos < 0 || pos > v->len) return;
    for(int i = pos + 1; i < v->len; i++)
        v->data[i - 1] = v->data[i];
}

void vector_free(vector_t *v)
{
    free(v->data);
}

#pragma endregion VECTOR

#pragma region UTILS

#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define WHITE_BOLD "\033[1;37m"
#define RESET "\033[0m"

#define ASSERT_F(cond, rtrn, func, ...) \
    if(cond) { \
        err_f(func, __VA_ARGS__); \
        return rtrn; \
    } \

#define ASSERT(cond, ...) \
    if(cond) { \
        err(__VA_ARGS__); \
        return; \
    } \

void report(FILE *f, const char *fmt, ...)
{
    if(!f) return;
    va_list ap;
    va_start(ap, fmt);
    vfprintf(f, fmt, ap);
    va_end(ap);
}

void write(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
    fputc('\n', stdout);
}

void write_f(const char *func, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%s%s:%s ", WHITE_BOLD, func, RESET);
    vfprintf(stdout, fmt, ap);
    va_end(ap);
    fputc('\n', stdout);
}

void err(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%sERRO:%s ", RED, RESET);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
}

void err_f(const char *func, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%s%s: %sERRO:%s ", WHITE_BOLD, func, RED, RESET);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
}

void warn(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%sAVISO:%s ", YELLOW, RESET);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
}

void heap_imprime(FILE *fout, heap *h)
{
    if(!h)
        return;

    for(int indice =1; indice<=(h->tamanho); indice++)
    {
        report(fout, "%s %s %d %d %f\n",h->elementos[indice]->nameItem, h->elementos[indice]->expirationDate,
                        h->elementos[indice]->qty,h->elementos[indice]->sellRate,
                        h->elementos[indice]->priorityVal);
    }
}

void avl_preordem(no_avl* no)
{
    if(no == NULL)
        return;

    printf("\n\n---- Categoria %s ----\n", no->categ->categName);
    mostraHeap(no->categ->itemTree);

    avl_preordem(no->esquerda);
    avl_preordem(no->direita);
}

int avl_count(no_avl *no)
{
    if(!no) return 0;
    return 1 + avl_count(no->esquerda) + avl_count(no->direita);
}

#pragma endregion UTILS

typedef struct {
    char name[MAX_CATEGNAME_LEN];
    int qty;
} e_categ;

#pragma region TESTS

int test_elemento_novo(FILE *fin, FILE *fout)
{
    printf("\n");
    write_f("elemento_novo", "Verfica se o elemento é criado e preenchido com os valores esperados");

    char itemName[100], categName[MAX_CATEGNAME_LEN], expirationDate[11];
    int qty, itemsPerDay;
    elemento_t *elem;

    fseek(fin, 0, SEEK_SET);
    fscanf(fin, "%s %s %d %d %s\n", itemName, categName, &qty, &itemsPerDay, expirationDate);

    elem = elemento_novo(itemName, expirationDate, qty, itemsPerDay);

    ASSERT_F(!elem, 0, "elemento_novo", "Elemento não foi criado");
    ASSERT_F(strcmp(itemName, elem->nameItem) != 0, 0, "elemento_novo", "Elemento criado com o nome errado");
    ASSERT_F(strcmp(expirationDate, elem->expirationDate) != 0, 0, "elemento_novo", "Elemento criado com a data de expiração errada");
    ASSERT_F(elem->qty != qty, 0, "elemento_novo", "Elemento criado com a quantidade errada");
    ASSERT_F(elem->sellRate != itemsPerDay, 0, "elemento_novo", "Elemento criado com o número de artigos vendidos por dia errado");
    ASSERT_F(elem->priorityVal != calcMetrica(elem), 0, "elemento_novo", "Elemento criado com a prioridade não calculada");

    write_f("elemento_novo", "Teste passou");

    report(fout, "===elemento_novo\n%s %s %d %d %f\n", elem->nameItem,
        elem->expirationDate, elem->qty, elem->sellRate, elem->priorityVal);

    free(elem);
    return 1;
}

int test_calc_metrica(FILE *fin, FILE *fout)
{
    printf("\n");
    write_f("calc_metrica", "Verfica se a metrica está entre 0 e 1");
    
    char itemName[100], categName[MAX_CATEGNAME_LEN], expirationDate[11];
    int qty, itemsPerDay;
    elemento_t *elem;

    fseek(fin, 0, SEEK_SET);
    fscanf(fin, "%s %s %d %d %s\n", itemName, categName, &qty, &itemsPerDay, expirationDate);

    elem = elemento_novo(itemName, expirationDate, qty, itemsPerDay);

    ASSERT_F(elem->priorityVal < 0 || elem->priorityVal > 1, 0, "calc_metrica", "Métrica não se encontra entre 0 e 1 (%f)", elem->priorityVal);

    free(elem);
    write_f("calc_metrica", "Teste passou");
    return 1;
}


int test_heap_nova(FILE *fin, FILE *fout)
{
    #define TESTE_HEAP_NOVA_CAPACIDADE 10


    printf("\n");
    write_f("heap_nova", "Verifica se a heap foi criada com sucesso");

    heap *hp = heap_nova(TESTE_HEAP_NOVA_CAPACIDADE);
    ASSERT_F(!hp, 0, "heap_nova", "Heap não foi criada");
    ASSERT_F(hp->capacidade != TESTE_HEAP_NOVA_CAPACIDADE, 0, "heap_nova", "Heap foi criada com a capacidade errada");
    ASSERT_F(!hp->elementos, 0, "heap_nova", "O vetor de elementos da heap não foi criado");

    heap_apaga(hp);

    write_f("heap_nova", "Teste passou");
    return 1;
}

int test_heap_remove(FILE *fin, FILE *fout)
{
    #define TESTE_HEAP_REMOVE_CAPACIDADE 10


    printf("\n");
    write_f("heap_remove", "Verifica se a heap remove os items com sucesso");

    heap *hp = heap_nova(TESTE_HEAP_REMOVE_CAPACIDADE);
    ASSERT_F(!hp, 0, "heap_remove", "Heap não foi criada");

    char itemName[100], categName[MAX_CATEGNAME_LEN], expirationDate[11];
    int qty, itemsPerDay;
    elemento_t *elem;

    int count = 0;
    while(count < TESTE_HEAP_REMOVE_CAPACIDADE && fscanf(fin, "%s %s %d %d %s\n",
        itemName, categName, &qty, &itemsPerDay, expirationDate) == 5)
    {

        elem = elemento_novo(itemName, expirationDate, qty, itemsPerDay);
        heap_insere(hp, elem);
        count++;
    }

    report(fout, "===heap_remove\n");
    heap_imprime(fout, hp);

    float priority_last = 1;

    for(count--; count >= 0; count--)
    {
        elem = heap_remove(hp);
        ASSERT_F(!elem, 0, "heap_remove", "Função retornou NULL quando deveria retornar um elemento");
        ASSERT_F(hp->tamanho != count, 0, "heap_remove", "O tamanho da heap está errado (%d quando deveria ser %d)", hp->tamanho, count);
        ASSERT_F(elem->priorityVal > priority_last, 0,"heap_remove",
            "O item removido anteriormente tinha uma prioridade mais baixa, o que sugere que a heap não está ordenada (%f para %f)",
            priority_last, elem->priorityVal);
 
        priority_last = elem->priorityVal;
        report(fout, "\n");
        heap_imprime(fout, hp);
        free(elem);
    }

    heap_apaga(hp);

    write_f("heap_remove", "Teste passou");
    return 1;
}

int test_avl_insere(FILE *fin, FILE *fout)
{
    #define AVL_INSERE_FOR_TEST(v_avl, str, h) \
        h = heap_nova(0);\
        ASSERT_F(!h, 0, "avl_insere", "Heap não foi criada");\
        if(v_avl->raiz == NULL) v_avl->raiz = avl_novo_no(novaCategoria(h, str));\
        else v_avl->raiz = avl_insere(v_avl->raiz, novaCategoria(h, str))

    #define AVL_INSERE_CHECK_TESTE(no, str) \
        !no || strcmp(no->categ->categName, str) != 0
    
    printf("\n");

    write_f("avl_insere", "Verifica se a avl é introduzida com sucesso");
    arvore_avl *avl = avl_nova();
    ASSERT_F(!avl, 0, "avl_insere", "AVL não foi criada");\


    heap *h;

    AVL_INSERE_FOR_TEST(avl, "a", h);
    AVL_INSERE_FOR_TEST(avl, "b", h);
    AVL_INSERE_FOR_TEST(avl, "c", h);
    AVL_INSERE_FOR_TEST(avl, "d", h);
    AVL_INSERE_FOR_TEST(avl, "e", h);
    AVL_INSERE_FOR_TEST(avl, "f", h);

    ASSERT_F(avl_count(avl->raiz) != 6, 0, "avl_insere", "AVL não tem o tamanho esperado");
    
    ASSERT_F(AVL_INSERE_CHECK_TESTE(avl->raiz, "d")
        || AVL_INSERE_CHECK_TESTE(avl->raiz->esquerda, "b")
        || AVL_INSERE_CHECK_TESTE(avl->raiz->esquerda->esquerda, "a")
        || AVL_INSERE_CHECK_TESTE(avl->raiz->esquerda->direita, "c")
        || AVL_INSERE_CHECK_TESTE(avl->raiz->direita, "e")
        || AVL_INSERE_CHECK_TESTE(avl->raiz->direita->direita, "f"),
        0, "avl_insere", "Elementos não estão a ser inseridos na ordem correta");

    avl_apaga(avl);

    write_f("avl_insere", "Teste passou");
    return 1;
}

int test_avl_pesquisa(FILE *fin, FILE *fout)
{
    #define AVL_PESQUISA_TEST(v_avl, str) \
        no = avl_pesquisa(v_avl->raiz, str); \
        ASSERT_F(!no, 0, "avl_pesquisa", "Pesquisa retornou NULL quando o elemento existe");\
        ASSERT_F(strcmp(no->categ->categName, str) != 0, 0, "avl_pesquisa", "avl_pesquisa", "Pesquisa retornou um elemento diferente ao procurado");

    printf("\n");
    write_f("avl_pesquisa", "Verifica se a avl é pesquisada corretamente");
    arvore_avl *avl = avl_nova();

    heap *h;

    AVL_INSERE_FOR_TEST(avl, "a", h);
    AVL_INSERE_FOR_TEST(avl, "b", h);
    AVL_INSERE_FOR_TEST(avl, "c", h);
    AVL_INSERE_FOR_TEST(avl, "d", h);
    AVL_INSERE_FOR_TEST(avl, "e", h);
    AVL_INSERE_FOR_TEST(avl, "f", h);

    no_avl *no;
    AVL_PESQUISA_TEST(avl, "a");
    AVL_PESQUISA_TEST(avl, "b");
    AVL_PESQUISA_TEST(avl, "c");
    AVL_PESQUISA_TEST(avl, "d");
    AVL_PESQUISA_TEST(avl, "e");
    AVL_PESQUISA_TEST(avl, "f");

    avl_apaga(avl);

    write_f("avl_pesquisa", "Teste passou");
    return 1;
}

e_categ *n_categ(vector_t *vec, const char *categName)
{    
    // Check if categ already exists
    e_categ *categ = NULL;
    for(int i = 0; i < vec->len; i++)
    {
        if(strcmp(V_GET(vec, e_categ*, i)->name, categName) == 0)
        {
            categ = V_GET(vec, e_categ*, i);
            break;
        }
    }

    if(!categ)
    {
        categ = malloc(sizeof(e_categ));
        strcpy(categ->name, categName);
        categ->qty = 0;
        V_SET(vec, categ, -1);
    }
    return categ;
}

int test_artigo_adiciona(FILE *fin, FILE *fout)
{
    printf("\n");
    write_f("artigo_adiciona", "Verifica se o artigo é adiciona corretamente");
    arvore_avl *avl = avl_nova();
    ASSERT_F(!avl, 0, "artigo_adiciona", "AVL não foi criada");

    char itemName[100], categName[MAX_CATEGNAME_LEN], expirationDate[11];
    int qty, itemsPerDay;
    elemento_t *elem;

    V_INIT(vec);

    report(fout, "===artigo_adiciona\n");

    fseek(fin, 0, SEEK_SET);
    while(fscanf(fin, "%s %s %d %d %s\n", itemName, categName, &qty, &itemsPerDay, expirationDate) == 5)
    {
        elem = elemento_novo(itemName, expirationDate, qty, itemsPerDay);

        no_avl *no = avl_pesquisa(avl->raiz, categName);
        e_categ *categ = n_categ(vec, categName);

        int s = artigo_adiciona(avl, elem, categName, CAP_ALL_CATEG);
        ASSERT_F(s && categ->qty >= CAP_ALL_CATEG, 0, "artigo_adiciona",
            "Elemento %s foi inserido na categoria %s embora já não houvesse capacidade (%d/%d)", itemName, categName, categ->qty, CAP_ALL_CATEG);

        ASSERT_F(!s && categ->qty < CAP_ALL_CATEG, 0, "artigo_adiciona",
            "Elemento %s não foi inserido na categoria %s embora houvesse capacidade (%d/%d)", itemName, categName, categ->qty, CAP_ALL_CATEG);

        ASSERT_F(s && !avl_pesquisa(avl->raiz, categName), 0, "artigo_adiciona", "A categoria %s nao foi introduzida na AVL", categName);

        report(fout, "%s %s %d %d %f\n", elem->nameItem, elem->expirationDate, elem->qty, elem->sellRate, elem->priorityVal);

        if(s) categ->qty++;
        else free(elem);
    }

    for(int i = 0; i < vec->len; i++)
    {
        free(V_GET(vec, e_categ*, i));
    }
    V_FREE(vec);

    avl_apaga(avl);
    write_f("artigo_adiciona", "Teste passou");
    return 1;
}

int test_criar_montra_impl(arvore_avl *avl, no_avl *no, FILE *fout)
{
    if(!no) return 1;
    #define NUM_POR_ITEM 5
    #define TOTAL_ITEMS 10
    int len;

    heap *h_cpy = heap_nova(no->categ->itemTree->capacidade);
    elemento_t *elem;

    for(int i = 1; i <= no->categ->itemTree->tamanho; i++)
    {
        elem = elemento_novo(no->categ->itemTree->elementos[i]->nameItem, no->categ->itemTree->elementos[i]->expirationDate,
            no->categ->itemTree->elementos[i]->qty, no->categ->itemTree->elementos[i]->sellRate);
        heap_insere(h_cpy, elem);
    }

    elemento_t **arr = criar_montra(avl, no->categ->categName, NUM_POR_ITEM, TOTAL_ITEMS, &len);

    ASSERT_F(len != 0 && !arr, 0, "criar_montra", "Tamanho da montra não é zero mas criar_montra retornou NULL");
    ASSERT_F(len == 0 && arr, 0, "criar_montra", "Montra foi criada, mas criar_montra retornou o tamanho como 0");

    report(fout, "\nMontra %s\n", no->categ->categName);
    if(!arr)
        report(fout, "Montra Vazia\n");
    else
    {
        int tot = 0;
        for(int i = 0; i < len; i++)
        {
            report(fout, "%s %s %d %d %f\n",arr[i]->nameItem, arr[i]->expirationDate,
                        arr[i]->qty,arr[i]->sellRate,
                        arr[i]->priorityVal);
            tot += arr[i]->qty;
            ASSERT_F(arr[i]->qty > NUM_POR_ITEM, 0, "criar_montra", "Artigo excede limite máximo de items (%d/%d)", arr[i]->qty, NUM_POR_ITEM);
            
            for(int j = 1; j <= h_cpy->tamanho; j++)
            {
                if(strcmp(h_cpy->elementos[j]->nameItem, arr[i]->nameItem) == 0
                    && strcmp(h_cpy->elementos[j]->expirationDate, arr[i]->expirationDate) == 0)
                {
                    h_cpy->elementos[j]->qty -= arr[i]->qty;
                }
            }
            free(arr[i]);
        }
        ASSERT_F(tot != TOTAL_ITEMS, 0, "criar_montra", "Montra não tem o total de items pedido (%d/%d)\n", tot, TOTAL_ITEMS);
        free(arr);
    }

    for(int i = 1; i <= h_cpy->tamanho; i++)
    {
        ASSERT_F(h_cpy->elementos[i]->qty < 0, 0, "criar_montra",
            "Foram utilizados na montra mais artigos do que os que haviam em stock (%s, foram utilizados %d a mais)",
            h_cpy->elementos[i]->nameItem, -h_cpy->elementos[i]->qty);

        int flag = 0;

        for(int j = 1; j <= no->categ->itemTree->tamanho; j++)
        {
            if(strcmp(h_cpy->elementos[i]->nameItem, no->categ->itemTree->elementos[j]->nameItem) == 0
                && strcmp(h_cpy->elementos[i]->expirationDate, no->categ->itemTree->elementos[j]->expirationDate) == 0)
            {
                ASSERT_F(h_cpy->elementos[i]->qty == 0, 0, "criar_montra", "Artigo %s continua na categoria, quando não deveria",
                    h_cpy->elementos[i]->nameItem);
                
                ASSERT_F(h_cpy->elementos[i]->qty != no->categ->itemTree->elementos[j]->qty, 0, "criar_montra",
                    "Artigo %s tem quantidade %d, mas deveria de ter %d",
                    h_cpy->elementos[i]->nameItem, no->categ->itemTree->elementos[j]->qty, h_cpy->elementos[i]->qty);
                flag = 1;
            }
        }

        ASSERT_F(!flag && h_cpy->elementos[i]->qty != 0, 0, "criar_montra", "Artigo %s não está na categoria, quando deveria",
                    h_cpy->elementos[i]->nameItem);
    }

    heap_apaga(h_cpy);

    if(!test_criar_montra_impl(avl, no->esquerda, fout)) return 0;
    if(!test_criar_montra_impl(avl, no->direita, fout)) return 0;
    return 1;
}

int test_criar_montra(FILE *fin, FILE *fout)
{
    printf("\n");
    write_f("criar_montra", "Verifica se a montra é criada corretamente");

    arvore_avl *avl = avl_nova();
    ASSERT_F(!avl, 0, "criar_montra", "AVL não foi criada");

    char itemName[100], categName[MAX_CATEGNAME_LEN], expirationDate[11];
    int qty, itemsPerDay;
    elemento_t *elem;

    fseek(fin, 0, SEEK_SET);
    while(fscanf(fin, "%s %s %d %d %s\n", itemName, categName, &qty, &itemsPerDay, expirationDate) == 5)
    {
        elem = elemento_novo(itemName, expirationDate, qty, itemsPerDay);
        if(!artigo_adiciona(avl, elem, categName, CAP_ALL_CATEG)) free(elem);
    }

    report(fout, "===criar_montra\n");
    if(!test_criar_montra_impl(avl, avl->raiz, fout)) return 0;

    avl_apaga(avl);

    write_f("criar_montra", "Teste passou");
    return 1;
}

#pragma endregion TESTS

#pragma region COMMAND_LOGIC

typedef struct command_
{
    void (*func)(int, const char*[]);
    char** aliases;
    int n_aliases;
} command_t;

void registerCommand(vector_t *vec, void (*func)(int, const char*[]), int num, ...)
{
    va_list ap;
    va_start(ap, num);
    
    command_t *cmd = malloc(sizeof(command_t));
    cmd->func = func;
    cmd->aliases = malloc(sizeof(char*) * num);
    cmd->n_aliases = num;

    char *arg;
    for(int i = 0; i < num; i++)
    {
        arg = va_arg(ap, char*);
        cmd->aliases[i] = malloc(sizeof(char) * (strlen(arg) + 1));
        strcpy(cmd->aliases[i], arg);
    }
    V_SET(vec, cmd, -1);
}

void dispatchCommand(vector_t *vec, int argc, char const *argv[])
{
    if(argc > 1)
    {
        command_t *cmd;
        for(int i = 0; i < vec->len; i++)
        {
            cmd = V_GET(vec, command_t*, i);
            for(int j = 0; j < cmd->n_aliases; j++)
            {
                if(strcmp(cmd->aliases[j], argv[1]) == 0)
                {
                    cmd->func(argc, argv);
                    return;
                }
            }
        }
    }
    V_GET(vec, command_t*, 0)->func(argc, argv);
}

void free_commands(vector_t *vec)
{
    command_t *cmd;
    for(int i = 0; i < vec->len; i++)
    {
        cmd = V_GET(vec, command_t*, i);
        for(int j = 0; j < cmd->n_aliases; j++)
        {
            free(cmd->aliases[j]);
        }
        free(cmd->aliases);
        free(cmd);
    }
    V_FREE(vec);
}

#pragma endregion COMMAND_LOGIC

#pragma region COMMANDS

void cmd_default(int argc, char const *argv[])
{
    if(argc <= 1)
        printf("trab2-tester: nenhuma operação especificada.\n");
    else
        printf("trab2-tester: operação especificada inválida.\n");
    printf("trab2-tester: Utilize --help para mais informação.\n");
}

void cmd_help(int argc, char const *argv[])
{
    printf("utilização: tester <operação> [...]\n");
    printf("operações:\n");
    printf("    tester {-h --help} - Listagem das operações disponíves.\n");
    printf("    tester {-v --version} - Mostra a versão do programa.\n");
    printf("    tester {-r --report} <entrada> [saída] - Gera o relatório do programa compilado em relação ao ficheiro de entrada.\n");
}

void cmd_version(int argc, char const *argv[])
{
    printf("MIEEC PROG2 Trab2 Tester v1.1\n");
    printf("Copyright (C) 2019 André Campanhã\n");
    printf("\nThis program may be freely redistributed under\nthe terms of the GNU General Public License.\n");
}

void cmd_report(int argc, char const *argv[])
{
    printf("A iniciar o relatório...\n");

    ASSERT(argc <= 2, "Nenhum ficheiro de entrada especificado.")

    const char *input_file = argv[2];
    FILE *fin = fopen(input_file, "r");

    ASSERT(!fin, "Ficheiro de entrada %s não existe.", input_file)

    FILE *fout;
    if(argc >= 4)
    {
        const char *output_file = argv[3];
        fout = fopen(output_file, "w");

        ASSERT(!fout, "Falha ao escrever no ficheiro %s.", output_file)
        warn("O relatório vai ser escrito para o ficheiro %s.", output_file);
    }
    else
        fout = NULL;


    int count = 0;    
    
    count += !test_elemento_novo(fin, fout);
    count += !test_calc_metrica(fin, fout);
    count += !test_heap_nova(fin, fout);
    count += !test_heap_remove(fin, fout);
    count += !test_avl_insere(fin, fout);
    count += !test_avl_pesquisa(fin, fout);
    count += !test_artigo_adiciona(fin, fout);
    count += !test_criar_montra(fin, fout);

    if(count == 0)
    {
        printf("\n\n");
        write("%sTodos os testes passaram com sucesso!%s", GREEN, RESET);
    }
    else
    {
        fprintf(stderr, "\n\n");
        if(count == 1)
            err("Falhou %d teste", count);
        else
            err("Falharam %d testes", count);
    }

    fclose(fin);
    if(fout)
        fclose(fout);
    
}

#pragma endregion COMMANDS

int main(int argc, char const *argv[])
{
    V_INIT(commands);
    registerCommand(commands, cmd_default, 0);
    registerCommand(commands, cmd_help, 2, "--help", "-h");
    registerCommand(commands, cmd_version, 2, "--version", "-v");
    registerCommand(commands, cmd_report, 2, "--report", "-r");
    dispatchCommand(commands, argc, argv);
    free_commands(commands);

    return 0;
}


