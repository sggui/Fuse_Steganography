#include "bmp.h"
#include <stdio.h>

void teste_bmp() {
    const char* filename = "test_image.bmp";
    int width = 100, height = 100;

    printf("Criando imagem BMP...\n");
    create_bmp(filename, width, height);

    FILE* bmp = fopen(filename, "rb+");
    if (!bmp) {
        perror("Erro ao abrir o arquivo BMP");
        return;
    }

    unsigned char r, g, b;
    printf("Escrevendo pixels...\n");
    write_pixel(bmp, 0, width, height, 255, 0, 0);
    write_pixel(bmp, 1, width, height, 0, 255, 0);
    write_pixel(bmp, 2, width, height, 0, 0, 255);

    printf("Lendo pixels...\n");
    read_pixel(bmp, 0, width, height, &r, &g, &b);
    printf("Pixel 0: R=%d, G=%d, B=%d\n", r, g, b);

    read_pixel(bmp, 1, width, height, &r, &g, &b);
    printf("Pixel 1: R=%d, G=%d, B=%d\n", r, g, b);

    read_pixel(bmp, 2, width, height, &r, &g, &b);
    printf("Pixel 2: R=%d, G=%d, B=%d\n", r, g, b);

    fclose(bmp);
}

