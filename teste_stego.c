#include "bmp.h"
#include "stego.h"
#include <stdio.h>
#include <string.h>

void teste_stego() {
    const char* filename = "test_image.bmp";
    FILE* bmp = fopen(filename, "rb+");
    if (!bmp) {
        perror("Erro ao abrir o arquivo BMP");
        return;
    }

    const char* message = "Hello, BMP!";
    char recovered_message[20] = {0};

    printf("Escondendo mensagem...\n");
    hide_data(bmp, message, strlen(message), 0);

    printf("Recuperando mensagem...\n");
    retrieve_data(bmp, recovered_message, strlen(message), 0);

    printf("Mensagem recuperada: %s\n", recovered_message);

    fclose(bmp);
}

