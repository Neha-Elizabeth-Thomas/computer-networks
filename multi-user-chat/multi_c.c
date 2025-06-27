#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 1200
#define SIZE 1024

void* recvmg(void* arg){
    int client_fd=*((int*)arg);
    char buffer[SIZE];

    while(1){
        recv(client_fd,buffer,SIZE,0);
        puts(buffer);
    }

    return NULL;
}

void main(int argc,char* argv[]){
    char client_name[20];
    strcpy(client_name,argv[1]);
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[SIZE];
    pthread_t thread;

    client_fd=socket(AF_INET,SOCK_STREAM,0);
    
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(client_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    pthread_create(&thread,NULL,recvmg,&client_fd);
    printf("Hello\n");
    while(1){
        char msg[SIZE];
        fgets(buffer,SIZE,stdin);
        buffer[strcspn(buffer,"\n")]='\0';
        sprintf(msg,"%s: %s",client_name,buffer);
        if(strcasecmp(buffer,"exit")==0){
            send(client_fd,buffer,SIZE,0);
            break;
        }
        send(client_fd,msg,SIZE,0);
    }

    close(client_fd);
}
