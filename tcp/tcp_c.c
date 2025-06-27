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
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[SIZE];

    client_fd=socket(AF_INET,SOCK_STREAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(client_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

/*    strcpy(buffer,"Njan Neha");
    send(client_fd,buffer,sizeof(buffer),0);
    recv(client_fd,buffer,sizeof(buffer),0);
    puts(buffer);*/
    while(1){
        printf("You: ");
        fgets(buffer,SIZE,stdin);
        buffer[strcspn(buffer,"\n")]='\0';
        send(client_fd,buffer,SIZE,0);
        if(strcasecmp(buffer,"exit")==0){
            printf("You exited the chat\n");
            break;
        }

        recv(client_fd,buffer,SIZE,0);
        if(strcasecmp(buffer,"exit")==0){
            printf("Serevr exited the chat\n");
            break;
        }
        printf("Server: %s\n",buffer);
    }

    close(client_fd);
}
