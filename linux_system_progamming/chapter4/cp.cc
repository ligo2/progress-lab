#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>

/*
    模拟实现拷贝空洞文件，省略部分资源释放，暂不优化
*/
int main() {
    int fd = open("./hole", O_RDONLY);
    if (fd == -1) {
        perror("open hole");
        return -1;
    }
    int fd_cp = open("./hole.cp", O_CREAT | O_WRONLY, 0777);
    if (fd == -1) {
        perror("open hole.cp");
        return -2;
    }
    char buffer[512];
    enum Status
    {
        NULL_ST,
        NORMAL_ST,
        BEGIN_ST,
    };
    while(true) {
        int rd = read(fd, buffer, sizeof(buffer));
        if (rd == -1) {
            perror("read");
            return -3;
        }
        if (rd == 0) {
            printf("\n拷贝结束\n");
            break;
        }
        std::string s;
        int null_len = 0;//记录区间NULL个数
        Status status = BEGIN_ST;
        for (int i = 0; i < rd; ++i)
        {
           switch(status) {
            case BEGIN_ST:
                if (buffer[i] == NULL) {
                    status = NULL_ST;
                    null_len++;
                } else {
                    status = NORMAL_ST;
                    s += buffer[i];
                }
                break;
            case NULL_ST:
                if (buffer[i] == NULL) {
                    null_len++;
                } else {
                    status = NORMAL_ST;
                    lseek(fd_cp, null_len, SEEK_CUR);
                    s.clear();
                    null_len = 0;
                    s += buffer[i];
                }
                break;
            case NORMAL_ST:
                if (buffer[i] == NULL) {
                    status = NULL_ST;
                    null_len = 1;
                    int wt = write(fd_cp, s.c_str(), s.size());
                    if (wt == -1) {
                        printf("写入失败\n");
                        return -4;
                    }
                    s.clear();
                } else {
                    s += buffer[i];
                }
                break;
            }  
        }
        int wt = write(fd_cp, s.c_str(), s.size());
            if (wt == -1) {
                printf("写入失败\n");
                return -5;
        }
    }
    close(fd);
    close(fd_cp);
    
    return 0;
}
    


