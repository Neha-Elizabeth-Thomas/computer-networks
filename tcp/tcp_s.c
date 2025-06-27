#define PORT 1200
#define SIZE 1024

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void main(){
    int serv_fd,client_fd,client_addr_len;
    struct sockaddr_in serv_addr,client_addr;
    char buffer[SIZE];

    serv_fd=socket(AF_INET,SOCK_STREAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    listen(serv_fd,5);

    client_fd=accept(serv_fd,(struct sockaddr*)&client_addr,&client_addr_len);

    while(1){
        recv(client_fd,buffer,SIZE,0);
        if(strcasecmp(buffer,"exit")==0){
            printf("Client exited the chat\n");
            break;
        }
        printf("Client: %s\n",buffer);

        printf("You: ");
        fgets(buffer,SIZE,stdin);
        buffer[strcspn(buffer,"\n")]='\0';
        send(client_fd,buffer,SIZE,0);
        if(strcasecmp(buffer,"exit")==0){
            printf("You exited the chat\n");
            break;
        }
    }

    close(client_fd);
    close(serv_fd);
}
