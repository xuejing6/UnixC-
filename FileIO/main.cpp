#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //close()  lseek() read() write() pread() pwrite()
#include <fcntl.h>  //open() openat() creat() fcntl()
#include <sys/stat.h>
#include <sys/ioctl.h> //ioctl()

int main(int argc, char *args[])
{
    //文件描述符以文件形式保存于/dev/fd下
    //mode用于在创建新文件时指定文件的权限,如S_IRUSR表示用户读
    //int fd1 = open("./test.txt", O_RDWR | O_APPEND | O_CREAT, S_IRUSR);
    int fd1 = open("./test.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR);
    if (fd1 < 0)
    {
        perror("open test.txt error");
    }
    int fd2 = openat(fd1,"test1.txt",O_RDWR | O_APPEND | O_CREAT);
    if (fd2 < 0)
    {
        perror("open text1.txt error");
    }
    int fd3 = creat("./test2.txt",O_RDWR);
    if (fd3 < 0)
    {
        perror("create text2.txt error");
    }
    close(fd3);
    fd2 = open("./test.txt", O_RDWR);
    fd3 = open("./test2.txt", O_RDWR);
    //off_t lseek(int __fildes, off_t __offset, int __whence)
    //若whence为SEEK_SET 则偏移设置为距离文件offset处
    //若whence为SEEK_CUR 则偏移设置为当前偏移 + offset
    //若whence为SEEK_END 则偏移设置为文件长度 + offset（可正可负）
    off_t curpos = lseek(fd3, 0, SEEK_CUR);
    if (curpos == -1)
    {
        perror("lseek file error");
    }
    //sysconf(_SC_V7_LP64_OFF64); //可设置off_t的范围
    char *sBuf = new char[1024];
    ssize_t len = 0;
    while ((len = read(fd3, sBuf, 1024)) > 0)
    {
        if (write(fd2, sBuf , len) != len)
        {
            perror("write file error");
        }
        printf("%s \n",sBuf);
    }

    //pread() 相当于lseek() + read()
    //pwrite() 相当于lseek() + write()
    off_t offset3 = lseek(fd3, 0, SEEK_SET);
    off_t offset2 = lseek(fd2, 0, SEEK_END);
    while ((len = pread(fd3, sBuf, 1024,offset3)) > 0)
    {
        offset3 = lseek(fd3, 0, SEEK_CUR);
        if (pwrite(fd2, sBuf, len, offset2) != len)
        {
            perror("write file error");
        }
        offset2 = lseek(fd2, 0, SEEK_END);
    }
    int newfd = dup(fd3); // 将文件描述符fd3赋给newfd，都指向test2.txt文件
    dup2(fd3, newfd); // 可以用newfd来指定新描述符数值，若newfd指向的文件已经被打开，会先将其关闭
                     //若newfd等于oldfd，就不关闭newfd，newfd和oldfd共同指向一份文件。等效于以下两函数
    //close(newfd);
    //fcntl(fd3, F_DUPFD, newfd); //更改已经打开文件的属性

    //      int fcntl (int fd, int cmd, ...);
    //      1.复制一个现有的描述符（cmd=F_DUPFD）.

    // 　　 2.获得／设置文件描述符标记(cmd=F_GETFD或F_SETFD).

    //      3.获得／设置文件状态标记(cmd=F_GETFL或F_SETFL).

    //      4.获得／设置异步I/O所有权(cmd=F_GETOWN或F_SETOWN).

    //      5.获得／设置记录锁(cmd=F_GETLK,F_SETLK或F_SETLKW).

    //在修改文件描述符标志或者状态时，必须先进行获取，然后修改，最后进行设置，不能直接设置，否则会关闭之前的标志位

    //为保证磁盘内容与缓冲区内容的一致性，提供以下三个函数。
    sync();  //只是将修改过的缓冲区排入到队列即返回。
    int res1 = fsync(fd3);   //若正确，返回0；失败则返回-1。等待磁盘写入才返回，适合数据库写入操作，同步更新文件内容与属性
    if (res1 == -1)
    {
        perror("fsync file error");
    }
    int res2 = fdatasync(fd3);  //若正确，返回0；失败则返回-1。等待磁盘写入才返回，只同步更新文件内容
    if (res2 == -1)
    {
        perror("fdatasync file error");
    }
    // int ioctl (int __fd, int __cmd, ...); //多用于终端I/O

    char str[10];
    scanf("%s",str);
    return 0;
}