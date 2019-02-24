#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH "lusiadas-utf8.txt"

int main()
{
    FILE *f = fopen(PATH, "r");
    if(f == NULL) return 0;

    int count_a = 0, count_o = 0, count_c = 0;    

    int c, flag = 0;
    while((c = getc(f)) != EOF)
    {
        if(c == 0xc3)
            flag = 1;
        else if(flag) {
            flag = 0;
            switch (c)
            {
                case 0xa3:
                case 0x83:
                    count_a++;
                    break;
                case 0x95:
                case 0xb5:
                    count_o++;
                    break;
                case 0x87:
                case 0xa7:
                    count_c++;
                    break;
                default:
                    break;
            }
        }
    }
    fclose(f);

    printf("A com til = %d\n", count_a);
    printf("O com til = %d\n", count_o);
    printf("C com cedilha = %d\n", count_c);
}