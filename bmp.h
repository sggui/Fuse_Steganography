#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdio.h> // Para o tipo FILE e manipulação de arquivos

// Estruturas de Cabeçalho BMP
#pragma pack(push, 1)

// Cabeçalho do BMP
typedef struct {
    uint16_t type;           // Tipo do arquivo (BM para BMP)
    uint32_t size;           // Tamanho total do arquivo em bytes
    uint16_t reserved1;      // Reservado
    uint16_t reserved2;      // Reservado
    uint32_t offset;         // Deslocamento até os dados da imagem
} BMPHeader;

// Cabeçalho de Informação do BMP
typedef struct {
    uint32_t size;           // Tamanho do cabeçalho de informações
    int32_t width;           // Largura da imagem em pixels
    int32_t height;          // Altura da imagem em pixels
    uint16_t planes;         // Número de planos de cor (sempre 1)
    uint16_t bits_per_pixel; // Bits por pixel (geralmente 24 para RGB)
    uint32_t compression;    // Tipo de compressão (0 = sem compressão)
    uint32_t image_size;     // Tamanho dos dados de imagem
    int32_t x_resolution;    // Resolução horizontal em pixels por metro
    int32_t y_resolution;    // Resolução vertical em pixels por metro
    uint32_t colors_used;    // Número de cores usadas na paleta
    uint32_t important_colors; // Cores importantes para a exibição
} BMPInfoHeader;

#pragma pack(pop)

// Funções para manipulação de arquivos BMP

/**
 * Cria uma imagem BMP com as dimensões especificadas.
 * 
 * @param filename Nome do arquivo BMP a ser criado
 * @param width Largura da imagem
 * @param height Altura da imagem
 */
void create_bmp(const char* filename, int width, int height);

/**
 * Lê os cabeçalhos de um arquivo BMP.
 * 
 * @param fp Ponteiro para o arquivo BMP
 * @param header Estrutura para armazenar os dados do cabeçalho BMP
 * @param info Estrutura para armazenar os dados do cabeçalho de informações do BMP
 */
void read_bmp_headers(FILE* fp, BMPHeader* header, BMPInfoHeader* info);

/**
 * Lê o valor de um pixel específico em um arquivo BMP.
 * 
 * @param fp Ponteiro para o arquivo BMP
 * @param pixel_index Índice do pixel (0 baseado)
 * @param width Largura da imagem
 * @param height Altura da imagem
 * @param r Ponteiro para armazenar o valor do componente vermelho
 * @param g Ponteiro para armazenar o valor do componente verde
 * @param b Ponteiro para armazenar o valor do componente azul
 */
void read_pixel(FILE* fp, int pixel_index, int width, int height, unsigned char* r, unsigned char* g, unsigned char* b);

/**
 * Escreve a cor de um pixel específico em um arquivo BMP.
 * 
 * @param fp Ponteiro para o arquivo BMP
 * @param pixel_index Índice do pixel (0 baseado)
 * @param width Largura da imagem
 * @param height Altura da imagem
 * @param r Valor do componente vermelho
 * @param g Valor do componente verde
 * @param b Valor do componente azul
 */
void write_pixel(FILE* fp, int pixel_index, int width, int height, unsigned char r, unsigned char g, unsigned char b);

#endif // BMP_H

