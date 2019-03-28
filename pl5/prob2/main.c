#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha.h"

void get_opr(pilha *p, int *opr1, int *opr2)
{
    *opr2 = pilha_top(p);
    pilha_pop(p);
    *opr1 = pilha_top(p);
    pilha_pop(p);
}

float calcula_total(char* expressao_rpn)
{
    pilha *p = pilha_nova();
    if(p == NULL) return 0;
    int flag = 0;
    char *token;
    int opr1, opr2;

    while((token = strtok(!flag ? expressao_rpn : NULL, " ")) != NULL)
    {
        switch (token[0])
        {
            case '+':
                get_opr(p, &opr1, &opr2);
                pilha_push(p, opr1 + opr2);
                break;
            case '*':
                get_opr(p, &opr1, &opr2);
                pilha_push(p, opr1 * opr2);
                break;
            case '-':
                get_opr(p, &opr1, &opr2);
                pilha_push(p, opr1 - opr2);
                break;
            case '/':
                get_opr(p, &opr1, &opr2);
                pilha_push(p, opr1 / opr2);
                break;
            default:
                pilha_push(p, atoi(token));
                break;
        }
        flag = 1;
    }

    opr1 = pilha_top(p);
    pilha_apaga(p);
    return opr1;
}

int main(int argc, char const *argv[])
{
    char ex[500];

    while(1)
    {
        printf("Expressão: ");
        if(fgets(ex, 500, stdin) == NULL) break;
        ex[strlen(ex) - 1] = '\0';

        printf("Resultado: %.0f\n", calcula_total(ex));
    }
    printf("\n");
    return 0;
}
