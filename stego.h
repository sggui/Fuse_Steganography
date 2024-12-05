#ifndef STEGO_H
#define STEGO_H

#include <stdio.h>
#include <stdint.h>

// Funções para esteganografia em arquivos BMP

/**
 * Esconde dados nos bits menos significativos dos pixels de um arquivo BMP.
 * 
 * @param bmp Ponteiro para o arquivo BMP aberto em modo de leitura/escrita
 * @param data Ponteiro para os dados a serem escondidos
 * @param size Tamanho dos dados a serem escondidos
 * @param offset Deslocamento inicial no arquivo BMP onde os dados serão escondidos
 */
void hide_data(FILE* bmp, const void* data, size_t size, uint32_t offset);

/**
 * Recupera dados escondidos nos bits menos significativos dos pixels de um arquivo BMP.
 * 
 * @param bmp Ponteiro para o arquivo BMP aberto em modo de leitura
 * @param data Ponteiro para o buffer onde os dados recuperados serão armazenados
 * @param size Tamanho dos dados a serem recuperados
 * @param offset Deslocamento inicial no arquivo BMP onde os dados estão escondidos
 */
void retrieve_data(FILE* bmp, void* data, size_t size, uint32_t offset);

#endif // STEGO_H

