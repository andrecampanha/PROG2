#include <stdio.h>
#include <stdlib.h>

int largura, altura;
short bpt;

int cordToPos(int l, int c)
{
    return ((altura - 1 - l) * largura + c) * bpt;
}

int main(int argc, char const *argv[])
{
    FILE *f;
    FILE *out;
    f = fopen("imagem.bmp", "rb");

    unsigned char vec[122];
    int ftam;

    fseek(f, 0, SEEK_END);
    ftam = ftell(f);

    fseek(f, 0, SEEK_SET);
    fread(vec, 1, 122, f);

    largura = *((int *) (vec + 14 + 4));
    altura = *((int *) (vec + 14 + 8));
    bpt = *((short *) (vec + 14 + 14)) / 8;

    printf("Tamanho total do ficheiro BMP: %d\n", ftam);
    printf("Largura da imagem: %d\n", largura);
    printf("Altura da imagem: %d\n", altura);
    printf("Bits por pixel: %d\n", bpt);

    char a = 0;

    unsigned char *img = malloc(sizeof(unsigned char) * largura * altura * bpt);
    fread(img, 1, largura * altura * bpt, f);

    printf("Valor RGB no pixel (0,0): %d %d %d\n", img[cordToPos(0, 0) + 2], img[cordToPos(0, 0) + 1], img[cordToPos(0, 0)]);
    printf("Valor RGB no pixel (532,0): %d %d %d\n", img[cordToPos(532, 0) + 2], img[cordToPos(532, 0) + 1], img[cordToPos(532, 0)]);
    printf("Valor RGB no pixel (408,443): %d %d %d\n", img[cordToPos(408, 443) + 2], img[cordToPos(408, 443) + 1], img[cordToPos(408, 443)]);

    fclose(f);

    return 0;
}