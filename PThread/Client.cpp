#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
#include<strings.h>

void *Recv(void *args)
{
    int sockfd = *(int *)args;
    char buffer[1024] = "";
    while(recv(sockfd,buffer,sizeof(buffer),0)>0)
    {
        std::cout<<"recive msg:"<<buffer<<std::endl;
        buffer[0] = '\0';
    }
    std::cout<<"server closed"<<std::endl;
    close(sockfd);
    return NULL;
}

void setclient(const char *sIP,int iPort)
{
    int socketfd = 0;
    socketfd = socket(AF_INET,SOCK_STREAM,0);
    if(socketfd < 0)
    {
        std::cout<<"create socket failed"<<std::endl;
        return;
    }
    struct sockaddr_in serveraddr;
    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(iPort);//将主机字序转换为网络字序
    if(inet_pton(AF_INET,sIP,&serveraddr.sin_addr.s_addr)<0)
    {
        std::cout<<"server ip transform error"<<std::endl;
        return ;
    }
    if(connect(socketfd,(sockaddr*)&serveraddr,sizeof(serveraddr))<0)
    {
        std::cout<<"connect server failed"<<std::endl;
        close(socketfd);
        return ;
    }
    pthread_t pt1;
    pthread_create(&pt1,NULL,Recv,&socketfd);
    pthread_detach(pt1);
    while(true)
    {
        std::string s;
        std::cin>>s;
        if(send(socketfd,s.c_str(),s.length(),0)>0)
        {
            std::cout<<"send msg to server:"<<s<<std::endl;
        }
        else
        {
            close(socketfd);
            return;
        }
        
    }
    close(socketfd);
}
int main(int arg, char* args[])
{
    setclient("127.0.0.1",8080);
    return 0;
}
