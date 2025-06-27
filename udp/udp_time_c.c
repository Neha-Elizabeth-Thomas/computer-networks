#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 1200
#define SIZE 1024

void main(){
    int client_fd,serv_addr_len;
    struct sockaddr_in serv_addr;
    char buffer[SIZE];
    serv_addr_len=sizeof(serv_addr);

    client_fd=socket(AF_INET,SOCK_DGRAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    for(int i=0 ; i<10 ; i++){
        strcpy(buffer,"TIME REQUEST");
        sendto(client_fd,buffer,SIZE,0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
        recvfrom(client_fd,buffer,SIZE,0,(struct sockaddr*)&serv_addr,&serv_addr_len);
        printf("Time Reply: %s\n",buffer);
        sleep(2);
    }

    close(client_fd);
}
