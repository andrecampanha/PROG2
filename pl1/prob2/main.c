#include <stdio.h>
#include <stdlib.h>

#define PATH "musica.mp3"

int main()
{
    unsigned char b[128];

    FILE *f = fopen(PATH, "rb");
    if(f == NULL) return 0;

    unsigned char titulo[30], artista[30], album[30], ano[5];
    char numero, genero;

    fseek(f, -125, SEEK_END);

    fread(titulo, sizeof(titulo), 1, f);
    fread(artista, sizeof(artista), 1, f);
    fread(album, sizeof(album), 1, f);
    fread(ano, sizeof(ano) - 1, 1, f);
    ano[4] = '\0';

    fseek(f, -2, SEEK_END);
    fread(&numero, sizeof(numero), 1, f);
    fread(&genero, sizeof(genero), 1, f);

    printf("Titulo: %s\n", titulo);
    printf("Artista: %s\n", artista);
    printf("Album: %s\n", album);
    printf("Ano: %s\n", ano);
    printf("Número: %d\n", (int) numero);
    printf("Género: %d\n", (int) genero);
}