#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "lusiadas.txt"

int main()
{
    FILE *f = fopen(PATH, "r");
    if(f == NULL) return 0;

    int freq[26];
    memset(freq, 0, sizeof(freq));
    

    int c, count = 0;
    while((c = getc(f)) != EOF)
    {
        if(c >= 'A' && c <= 'Z')
            c -= 'A' - 'a';
        else if((c >= 192 && c <= 195) || (c >= 224 && c <= 227))
            c = 'a';
        else if((c >= 211 && c <= 213) || (c >= 243 && c <= 245))
            c = 'o';
        else if(c == 205 || c == 237)
            c = 'i';
        else if(c == 201 || c == 202 || c == 233 || c == 234)
            c = 'e';
        else if(c == 218 || c == 250)
            c = 'u';
        else if(c == 199 || c == 231)
            c = 'c';

        if(c >= 'a' && c <= 'z')
        {
            count++;
            freq[c - 'a']++;
        }
    }
    fclose(f);

    printf("Numero de letras do ficheiro: %d\n", count);

    for(int i = 0; i < 26; i++)
    {
        printf("Letra %c = %.2f%%\n", i + 'a', ((float)freq[i] / count)*100);
    }
}