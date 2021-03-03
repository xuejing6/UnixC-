#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h> //stat() fstat() lstat() fstatat() umask()
#include <unistd.h>   //access() faccessat() 

int main()
{
    //int	stat (const char *__restrict __path, struct stat *__restrict __sbuf );  //获得给定路径文件的信息结构 stat
    //int	fstat (int __fd, struct stat *__sbuf );                                 //获得已在文件描述符fd上打开的文件的信息结构
    //int	lstat (const char *__restrict __path, struct stat *__restrict __buf );  //获得给定路径文件的符号链接信息
    //int	fstatat (int fd, const char *__restrict , struct stat *__restrict, int flag);   //获得打开目录（fd指向）下文件的信息结构,flag可控制返回是链接信息还是指向文件信息
    // unix文件类型宏定义
    // #define	S_ISBLK(m)	(((m)&_IFMT) == _IFBLK)  块特殊文件
    // #define	S_ISCHR(m)	(((m)&_IFMT) == _IFCHR)  字符特殊文件
    // #define	S_ISDIR(m)	(((m)&_IFMT) == _IFDIR)  目录文件
    // #define	S_ISFIFO(m)	(((m)&_IFMT) == _IFIFO)  管道或FIFO
    // #define	S_ISREG(m)	(((m)&_IFMT) == _IFREG)  普通文件
    // #define	S_ISLNK(m)	(((m)&_IFMT) == _IFLNK)  符号链接
    // #define	S_ISSOCK(m)	(((m)&_IFMT) == _IFSOCK) 套接字
    // #define S_TYPEISMQ(buf)  ((void)(buf)->st_mode,0) 消息队列
    // #define S_TYPEISSEM(buf) ((void)(buf)->st_mode,0) 信号量
    // #define S_TYPEISSHM(buf) ((void)(buf)->st_mode,0) 共享存储对象
    struct stat tFileStat;
    int res = stat("./main.cpp", &tFileStat);
    
    // int	access (const char *__path, int __amode);                             //按实际用户ID和实际组ID测试文件访问权限
    // int	faccessat (int __dirfd, const char *__path, int __mode, int __flags); //按实际用户ID和实际组ID测试文件访问权限，若flag为AT_EACCESS，则表示用进程的有效ID和有效组ID
    //mode的取值宏定义
    // #define	F_OK	0 文件存在
    // #define	R_OK	4 读权限
    // #define	W_OK	2 写权限
    // #define	X_OK	1 执行权限

    // mode_t	umask (mode_t __mask ); //进程设置文件模式创建屏蔽字
    // #define	S_IRWXU 	(S_IRUSR | S_IWUSR | S_IXUSR)
    // #define		S_IRUSR	0000400	/* read permission, owner */
    // #define		S_IWUSR	0000200	/* write permission, owner */
    // #define		S_IXUSR 0000100/* execute/search permission, owner */
    // #define	S_IRWXG		(S_IRGRP | S_IWGRP | S_IXGRP)
    // #define		S_IRGRP	0000040	/* read permission, group */
    // #define		S_IWGRP	0000020	/* write permission, grougroup */
    // #define		S_IXGRP 0000010/* execute/search permission, group */
    // #define	S_IRWXO		(S_IROTH | S_IWOTH | S_IXOTH)
    // #define		S_IROTH	0000004	/* read permission, other */
    // #define		S_IWOTH	0000002	/* write permission, other */
    // #define		S_IXOTH 0000001/* execute/search permission, other */
    // #define	S_ISUID		0004000	/* set user id on execution */
    // #define	S_ISGID		0002000	/* set group id on execution */
    // #define	S_ISVTX		0001000	/* save swapped text even after use */


    // int	chmod (const char *__path, mode_t __mode );  //更改给定路径文件权限
    // int  fchmod (int __fd, mode_t __mode);             //更改已在文件描述符fd上打开的文件的文件权限
    // int	fchmodat (int fd, const char *, mode_t mode, int flag); //更改相对路径fd下文件权限，flag改变其行为，为AT_SYMLINK_NOFOLLOW，不会跟随符号链接
    if (chmod("./main.cpp", S_IRUSR) == -1) 
    {
        perror("chmod set error");
    }
    // int     chown (const char *__path, uid_t __owner, gid_t __group); //更改给定路径文件的UID GID 设为-1则不改变
    // int     fchown (int __fildes, uid_t __owner, gid_t __group);      //更改已在文件描述符fd上打开的文件的文件UID GID 设为-1则不改变
    // int	fchownat (int __dirfd, const char *__path, uid_t __owner, gid_t __group, int __flags); //更改相对路径fd下文件UID GID，flag改变其行为，为AT_SYMLINK_NOFOLLOW，更改符号链接本生文件
    // int     lchown (const char *__path, uid_t __owner, gid_t __group); //更改链接本身文件UID GID
    return 0;
}