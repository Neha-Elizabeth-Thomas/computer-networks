#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 1200
#define SIZE 1024

pthread_mutex_t mutex;
int clients[20],n;
int serv_fd;

void sendtoall(int client_fd,char buffer[]){
    pthread_mutex_lock(&mutex);
    for(int i=0 ; i<n ; i++)
        if(clients[i]!=client_fd)
            send(clients[i],buffer,SIZE,0);
    pthread_mutex_unlock(&mutex);
}

void* recvmg(void * arg){
    char buffer[SIZE];
    int client_fd=*((int*)arg);
    free(arg);

    while(1){
        recv(client_fd,buffer,SIZE,0);
        if(strcasecmp(buffer,"exit")==0)
            break;
        sendtoall(client_fd,buffer);
    }

    pthread_mutex_lock(&mutex);
    for(int i=0 ; i<n ; i++)
        if(clients[i]==client_fd){
            for(int j=i ; j<n-1 ; j++){
                clients[j]=clients[j+1];
            }
            n--;
            break;
        }
    pthread_mutex_unlock(&mutex);
    close(client_fd);
    if(n==0)
        close(serv_fd);

    return NULL;
}

void main(){
    int* client_fd;
    struct sockaddr_in serv_addr;
    pthread_t thread;

    pthread_mutex_init(&mutex,NULL);

    serv_fd=socket(AF_INET,SOCK_STREAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    listen(serv_fd,10);

    while(1){
        client_fd=(int*)malloc(sizeof(int));
        *client_fd=accept(serv_fd,NULL,NULL);

        pthread_mutex_lock(&mutex);
        clients[n++]=*client_fd;
        pthread_create(&thread,NULL,recvmg,client_fd);
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_destroy(&mutex);
    close(serv_fd);
}
