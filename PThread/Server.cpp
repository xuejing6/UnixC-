#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<pthread.h>
#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>  //sockaddr_in结构定义头文件
#include<unistd.h>      //close()
#include<arpa/inet.h>   //inet_ntop()将网络地址转换为字符地址
#include<map>
#include<sys/msg.h>

pthread_mutex_t mutex;
std::map<uint32_t,struct sockaddr_in> clientsock;
std::map<uint32_t,uint32_t> mThreadToMsg;
const int MSGKEY = 2020;
void* Recv(void *args)
{
    pthread_mutex_unlock(&mutex);
    int acceptf = *(int*)args;
    char buffer[1024] = "";
    while(recv(acceptf,buffer,sizeof(buffer),0)>0)
    {
        int msgid = msgget(MSGKEY+getpid(),0600 | IPC_CREAT);
        mThreadToMsg.insert(std::pair<uint32_t,uint32_t>(getpid(),msgid));
        std::cout<<"recv msg:"<<buffer<<std::endl;
        send(acceptf,buffer,sizeof(buffer),0);
        buffer[0] = '\0';
    }
    if(auto iter = clientsock.find(acceptf) != clientsock.end())
    {
        clientsock.erase(iter);
    }
    close(acceptf);
    std::map<uint32_t,struct sockaddr_in>::iterator iter = clientsock.begin();
    for(;iter != clientsock.end();++iter)
    {
        char sIP[INET_ADDRSTRLEN] = "";
        inet_ntop(AF_INET,&(iter->second.sin_addr.s_addr),sIP,INET_ADDRSTRLEN);
        std::cout<<sIP<<"    "<< ntohs(iter->second.sin_port) << std::endl;
    }    
    
    return NULL;
}

void SetServer(int port)
{
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in my_addr;
    int bindf = 0;
    int listenf = 0;
    pthread_mutex_init(&mutex,NULL);
    if(socketfd < 0)
    {
        std::cout<<"create socket failed"<<std::endl;
        return ;
    }
    bzero(&my_addr,sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = ntohs(port);
    my_addr.sin_addr.s_addr = ntohl(INADDR_ANY);
    bindf = bind(socketfd,(struct sockaddr*)&my_addr,sizeof(my_addr));
    if(bindf !=0)
    {
        perror("bindf");
        std::cout<<"server bind socket failed"<<std::endl;
        close(socketfd);
        return ;
    }
    listenf = listen(socketfd,10);
    if(listenf != 0)
    {
        std::cout<<"set server listening failed"<<std::endl;
        close(socketfd);
        return ;
    }
    std::cout<<"server is ready"<<std::endl;
    clientsock.clear();
    while(true)
    {
        char sIP[INET_ADDRSTRLEN] = "";
        struct sockaddr_in tClient;
        bzero(&tClient,sizeof(tClient));
        socklen_t clientlen = sizeof(tClient);
        int acceptf = accept(socketfd,(struct sockaddr *)&tClient,&clientlen);
        if(acceptf < 0)
        {
            std::cout<<"accept error"<<std::endl;
            continue;
        }
        pthread_t pt1;
        pthread_mutex_lock(&mutex);
        clientsock.insert(std::pair<uint32_t,struct sockaddr_in>(acceptf,tClient));
        inet_ntop(AF_INET,&tClient.sin_addr.s_addr,sIP,INET_ADDRSTRLEN);
        std::cout<<"IP:"<<sIP<<"  port:"<<ntohs(tClient.sin_port)<<std::endl;
        pthread_create(&pt1,NULL,Recv,&acceptf);
        std::cout<<"Create PThread id is "<<pt1<<std::endl;
        pthread_detach(pt1);
    }
    close(socketfd);
    return ;
}

int  main(int arg , char * args[])
{
    SetServer(8080);
    return 0;
}