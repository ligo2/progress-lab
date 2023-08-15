#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // int fd = open("./text.txt", O_RDONLY);
    // if (fd == -1) {
    //     perror("open hole");
    //     return -1;
    // }
    // printf("%d\n", fd);
    // sleep(20);
    fprintf(stderr, "错误\n");
    int new_fd = dup2(1, 2);
    printf("%d\n", new_fd);

    return 0;
}