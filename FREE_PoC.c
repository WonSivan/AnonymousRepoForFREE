#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char FILE_PATH[1024];

int main() {
    printf("input FILE_PATH.\n");
    scanf("%s", FILE_PATH);

    int fd = open(FILE_PATH, O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    uint64_t FILE_SIZE = 8UL * 1024 * 1024 * 1024;
    printf("input FILE_SIZE (GB).\n");
    scanf("%lu", &FILE_SIZE);
    FILE_SIZE *= 1024UL * 1024UL * 1024UL;

    uint32_t CHUNK_SIZE = 64 * 1024 * 1024;
    printf("input CHUNK_SIZE (MB).\n");
    scanf("%u", &CHUNK_SIZE);
    CHUNK_SIZE *= 1024 * 1024;

    uint32_t _unlink = 0;
    printf("unlink?\n");
    scanf("%u", &_unlink);
    if(_unlink) unlink(FILE_PATH);

    if (ftruncate(fd, FILE_SIZE) < 0) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    void *addr = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    printf("Start massive dirtying loop...\n");

    for (size_t offset = 0; offset < FILE_SIZE; offset += CHUNK_SIZE) {
        memset((char*)addr + offset, 0xCD, CHUNK_SIZE);
        printf("Dirty %lu MiB\n", (offset + CHUNK_SIZE) / (1024 * 1024));
    }

    printf("Enter Ctrl + C to kill this process.\n");
	getchar();
    munmap(addr, FILE_SIZE);
    close(fd);
    return 0;
}