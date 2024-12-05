#include <stdio.h>
#include <string.h>

// Declaração das funções dos testes
void teste_bmp();
void teste_stego();

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Uso: %s [teste_bmp | teste_stego]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "teste_bmp") == 0) {
        teste_bmp();
    } else if (strcmp(argv[1], "teste_stego") == 0) {
        teste_stego();
    } else {
        printf("Teste inválido. Use 'teste_bmp' ou 'teste_stego'.\n");
        return 1;
    }

    return 0;
}

