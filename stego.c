#include "bmp.h"
#include <stdio.h>
#include <stdint.h>

// Função para recuperar dados escondidos
void retrieve_data(FILE* bmp, void* data, size_t size, uint32_t offset) {
    uint8_t* bytes = (uint8_t*)data; // Converte o buffer para bytes
    unsigned char r, g, b;

    for (size_t i = 0; i < size; i++) {
        uint8_t byte = 0; // Inicializa o byte
        for (int bit = 0; bit < 8; bit += 3) {
            // Lê o pixel no offset
            read_pixel(bmp, offset, 100, 100, &r, &g, &b);

            // Reconstrói o byte
            byte |= (r & 0x01) << bit;
            byte |= (g & 0x01) << (bit + 1);
            byte |= (b & 0x01) << (bit + 2);

            offset++; // Move para o próximo pixel
        }
        bytes[i] = byte; // Armazena o byte reconstruído
    }
}

// Função para esconder dados nos bits menos significativos
void hide_data(FILE* bmp, const void* data, size_t size, uint32_t offset) {
    const uint8_t* bytes = (const uint8_t*)data; // Converte os dados para bytes
    unsigned char r, g, b;

    for (size_t i = 0; i < size; i++) {
        uint8_t byte = bytes[i]; // Obtém o byte atual
        for (int bit = 0; bit < 8; bit += 3) {
            // Lê o pixel no offset
            read_pixel(bmp, offset, 100, 100, &r, &g, &b);

            // Modifica os bits menos significativos
            r = (r & 0xFE) | ((byte >> bit) & 0x01);
            g = (g & 0xFE) | ((byte >> (bit + 1)) & 0x01);
            b = (b & 0xFE) | ((byte >> (bit + 2)) & 0x01);

            // Escreve de volta no BMP
            write_pixel(bmp, offset, 100, 100, r, g, b);
            offset++; // Move para o próximo pixel
        }
    }
}

