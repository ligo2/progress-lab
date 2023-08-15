#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>

// int main() {
//     int fd = open("./text.txt", O_CREAT | O_RDWR, 0777);
//     if (fd == -1) {
//         perror("open");
//         return -1;
//     }
//     // off_t cur = lseek(fd, 2, SEEK_SET);
//     off_t cur = lseek(fd, 100, SEEK_END);
//     if (cur == -1) {
//         perror("lseek");
//         return -2;
//     }
//     printf("%ld", cur);
//     char buffer[512];
//     int rd = read(fd, buffer, sizeof(buffer - 1));
//     if (rd == -1) {
//         perror("read");
//         return -3;
//     }
//     if (rd == 0) {
//         printf("到达文件结尾\n");
//     } else {
//         buffer[rd] = '\0';
//         printf("%s\n", buffer);
//     }
    
//     //写
//     // char write_buffer[] = "这是写入的数据";
//     // int wt = write(fd, write_buffer, sizeof(write_buffer));
//     // if (wt == -1) {
//     //     perror("write");
//     //     return -4;
//     // }
//     // printf("写入数据大小:%d\n", wt);


//     close(fd);
//     return 0;
// }

/*32位机若要支持处理超过2GB大小的文件，可以引入系统对IFS的支持*/
/*大文件I/O，open自动转为open64，和一些其他相关的函数和数据类型*/
#define _FILE_OFFSET _BITS 64

int main() {
    int fd = open("./text.txt", O_CREAT | O_RDWR, 0777);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    int flags, accseMode;
    flags = fcntl(fd, F_GETFL); //获取文件描述符标记
    if (flags == -1) {
        return -1;
    }
    accseMode = flags & O_ACCMODE;
    if (accseMode & O_CREAT) {
        printf("O_CREATE is set\n");
    }
    if (accseMode & O_RDWR)
        printf("O_RDWR is set\n");
    if (accseMode & O_APPEND)
        printf("O_APPEND is set\n");

    close(fd);

    return 0;
}