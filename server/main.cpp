//
//  main.cpp
//  exam
//
//  Created by Samaritan on 04/12/2019.
//  Copyright © 2019 Samaritan. All rights reserved.
//

#include "main.hpp"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main(){
    
    int server_sockfd;
    int client_sockfd;
    
    int len;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;
    int sin_size;
    char buf[BUFSIZ];
    memset(&my_addr,0,sizeof(my_addr));
    my_addr.sin_family=AF_INET;
    my_addr.sin_addr.s_addr=INADDR_ANY;
    my_addr.sin_port=htons(4399);
    
    if(server_sockfd=socket(PF_INET,SOCK_STREAM,0)<0){
        perror("socket error");
        return 1;
    }
    
    if(bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0){
        perror("bind error");
        return 1;
    }
    
    if(listen(server_sockfd,5)<0){
        perror("listen error");
        return 1;
    }
    
    sin_size=sizeof(sockaddr);
    
    client_sockfd=accept(server_sockfd,(struct sockaddr *)&remote_addr,&sin_size);
    if(client_sockfd<0){
    perror("accept error");
        return 1;
    }
    
    len=send("It's Adam!\n",21,0);
    
    while(len=recv(client_sockfd,buf,BUFSIZ,0)>0){
        buf[len]='\0';
        printf("%s\n",buf);
        if(send(client_sockfd,buf,len,0)<0){
            perror("write error");
            return 1;
        }
    }
    
    close(client_sockfd);
    close(server_sockfd);
    return 0;
}
