#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "pagina.html"

int main()
{
    FILE *f = fopen(PATH, "r");
    char line[500];
    char *token, *tag;
    int flag;

    char nome[500], link[500];

    while(fgets(line, 500, f) != NULL)
    {
        flag = 0;
        while((token = strtok(flag ? NULL : line, "<")) != NULL)
        {
            flag = 1;
            if(token[0] != 'a') continue;

            strtok(token, "\"");
            tag = strtok(NULL, "\"");
            strcpy(link, tag);

            tag = strtok(NULL, "<");
            tag+=2;
            strcpy(nome, tag);

            printf("%s - %s\n", nome, link);
        }
        
    }
}