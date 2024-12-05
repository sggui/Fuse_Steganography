#include "fusefs.h"
#include <string.h>
#include <errno.h>
#include <time.h>
#include "bmp.h"
#include "stego.h"

FSState fs_state;

// Simulação de conteúdo de um arquivo para teste
static char file_content[1024] = "Hello from BMP filesystem!";
static size_t file_size = 29;

static void* fs_init(struct fuse_conn_info* conn, struct fuse_config* cfg) {
    (void) conn;
    printf("fs_init\n");

    cfg->use_ino = 1;
    cfg->kernel_cache = 1;

    fs_state.bmp = fopen(fs_state.bmp_filename, "rb+");
    if (!fs_state.bmp) {
        perror("Erro ao abrir arquivo BMP");
        exit(EXIT_FAILURE);
    }
    return NULL;
}

static void fs_destroy(void* private_data) {
    (void) private_data;
    printf("fs_destroy\n");

    if (fs_state.bmp) {
        fclose(fs_state.bmp);
    }
}

static int fs_getattr(const char* path, struct stat* stbuf, struct fuse_file_info* fi) {
    (void) fi;
    printf("fs_getattr: %s\n", path);

    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else if (strcmp(path, "/file") == 0) {
        stbuf->st_mode = S_IFREG | 0644;
        stbuf->st_nlink = 1;
        stbuf->st_size = file_size;
    } else {
        return -ENOENT;
    }

    return 0;
}

static int fs_readdir(const char* path, void* buf, fuse_fill_dir_t filler,
                      off_t offset, struct fuse_file_info* fi, enum fuse_readdir_flags flags) {
    (void) offset;
    (void) fi;
    (void) flags;
    printf("fs_readdir: %s\n", path);

    if (strcmp(path, "/") != 0) {
        return -ENOENT;
    }

    filler(buf, ".", NULL, 0, FUSE_FILL_DIR_PLUS);
    filler(buf, "..", NULL, 0, FUSE_FILL_DIR_PLUS);
    filler(buf, "file", NULL, 0, FUSE_FILL_DIR_PLUS);

    return 0;
}

static int fs_read(const char* path, char* buf, size_t size, off_t offset,
                   struct fuse_file_info* fi) {
    (void) fi;
    printf("fs_read: %s\n", path);

    if (strcmp(path, "/file") != 0) {
        return -ENOENT;
    }

    if (offset >= file_size) {
        return 0;
    }

    if (offset + size > file_size) {
        size = file_size - offset;
    }

    memcpy(buf, file_content + offset, size);
    return size;
}

static int fs_write(const char* path, const char* buf, size_t size, off_t offset,
                    struct fuse_file_info* fi) {
    (void) fi;
    printf("fs_write: Caminho = %s, Tamanho = %zu, Offset = %ld\n", path, size, offset);

    if (strcmp(path, "/file") != 0) {
        return -ENOENT;
    }

    if (offset + size > sizeof(file_content)) {
        return -EFBIG;
    }

    memcpy(file_content + offset, buf, size);
    file_size = offset + size > file_size ? offset + size : file_size;

    printf("fs_write: Dados escritos: %.*s\n", (int)size, buf);

    return size;
}

static int fs_create(const char* path, mode_t mode, struct fuse_file_info* fi) {
    printf("fs_create: Criando arquivo em %s\n", path);

    if (strcmp(path, "/test_file") == 0) {
        return 0; // Sucesso
    }

    return -EACCES; // Proíbe a criação de outros arquivos
}

static int fs_mkdir(const char* path, mode_t mode) {
    (void) mode;
    printf("fs_mkdir: %s\n", path);

    return 0;
}

struct fuse_operations fs_oper = {
    .getattr = fs_getattr,
    .readdir = fs_readdir,
    .read = fs_read,
    .write = fs_write,
    .mkdir = fs_mkdir,
    .init = fs_init,
    .destroy = fs_destroy,
    .create = fs_create,
};

