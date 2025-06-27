#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 1200
#define SIZE 1024

void main(int argc,char* argv[]){
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[SIZE];
    FILE* fd;

    if(argc!=2){
        printf("Usage ./a.out filename\n");
        exit(1);
    }
    
    client_fd=socket(AF_INET,SOCK_STREAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(client_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    fd=fopen(argv[1],"r");
    
    while(fgets(buffer,SIZE,fd)!=NULL){
        buffer[strcspn(buffer,"\n")]='\0';
        send(client_fd,buffer,SIZE,0);
    }
    strcpy(buffer,"EOF");
    send(client_fd,buffer,SIZE,0);
    fclose(fd);
    close(client_fd);
}
