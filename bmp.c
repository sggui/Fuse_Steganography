#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_pixel(FILE* fp, int pixel_index, int width, int height, unsigned char r, unsigned char g, unsigned char b) {
    BMPHeader header;
    BMPInfoHeader info;
    read_bmp_headers(fp, &header, &info);

    int padding = (4 - (width * 3) % 4) % 4;
    int row = pixel_index / width;
    int col = pixel_index % width;
    int actual_row = height - row - 1;

    long row_size = width * 3 + padding;
    long pixel_offset = header.offset + actual_row * row_size + col * 3;

    fseek(fp, pixel_offset, SEEK_SET);
    fwrite(&b, 1, 1, fp);
    fwrite(&g, 1, 1, fp);
    fwrite(&r, 1, 1, fp);
}

void read_bmp_headers(FILE* fp, BMPHeader* header, BMPInfoHeader* info) {
    fseek(fp, 0, SEEK_SET);
    fread(header, sizeof(BMPHeader), 1, fp);
    fread(info, sizeof(BMPInfoHeader), 1, fp);
}

void create_bmp(const char* filename, int width, int height) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        perror("Erro ao criar arquivo BMP");
        exit(EXIT_FAILURE);
    }

    int padding = (4 - (width * 3) % 4) % 4;
    int row_size = width * 3 + padding;
    int image_size = row_size * height;

    BMPHeader header = {
        .type = 0x4D42,
        .size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + image_size,
        .reserved1 = 0,
        .reserved2 = 0,
        .offset = sizeof(BMPHeader) + sizeof(BMPInfoHeader),
    };

    BMPInfoHeader info = {
        .size = sizeof(BMPInfoHeader),
        .width = width,
        .height = height,
        .planes = 1,
        .bits_per_pixel = 24,
        .compression = 0,
        .image_size = image_size,
        .x_resolution = 2835,
        .y_resolution = 2835,
        .colors_used = 0,
        .important_colors = 0,
    };

    fwrite(&header, sizeof(header), 1, fp);
    fwrite(&info, sizeof(info), 1, fp);

    unsigned char pixel[3] = {255, 255, 255};
    unsigned char pad[3] = {0, 0, 0};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fwrite(pixel, 3, 1, fp);
        }
        if (padding > 0) {
            fwrite(pad, padding, 1, fp);
        }
    }

    fclose(fp);
}

void read_pixel(FILE* fp, int pixel_index, int width, int height, unsigned char* r, unsigned char* g, unsigned char* b) {
    BMPHeader header;
    BMPInfoHeader info;
    read_bmp_headers(fp, &header, &info);

    int padding = (4 - (width * 3) % 4) % 4;
    int row = pixel_index / width;
    int col = pixel_index % width;
    int actual_row = height - row - 1;

    long row_size = width * 3 + padding;
    long pixel_offset = header.offset + actual_row * row_size + col * 3;

    fseek(fp, pixel_offset, SEEK_SET);
    fread(b, 1, 1, fp);
    fread(g, 1, 1, fp);
    fread(r, 1, 1, fp);
}

