#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    float real, imaginary;
} ComplexRect;

typedef struct {
    float mod, ang;
} ComplexAng;

void rectToAng(ComplexRect *rect, ComplexAng *ang)
{
    ang->mod = sqrt(rect->real * rect->real + rect->imaginary * rect->imaginary);
    #ifndef __INTELLISENSE__
        ang->ang = atan2(rect->imaginary, rect->real) * (180.0 / M_PI);
    #endif
}

int main(int argc, char const *argv[])
{
    int n;
    ComplexRect *rec;
    ComplexAng *ang;

    printf("Quantidade de numeros complexos a converter: ");
    scanf("%d", &n);
    rec = malloc(sizeof(ComplexRect) * n);
    ang = malloc(sizeof(ComplexAng) * n);

    printf("Insira os coeficientes das partes real e imaginaria...\n");
    for(int i = 0; i < n; i++)
    {
        printf("...do %dº numero complexo: ", i + 1);
        scanf("%f %f", &rec[i].real, &rec[i].imaginary);
        rectToAng(&rec[i], &ang[i]);
    }

    printf("As respectivas representacoes polares sao:\n");
    for(int i = 0; i < n; i++)
    {
        printf("mod=%.2f\tang=%.2f\n", ang[i].mod, ang[i].ang);
    }

    return 0;
}
