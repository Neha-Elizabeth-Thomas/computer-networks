#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 1200
#define SIZE 1024

void main(){
    int client_fd,serv_addr_len;
    struct sockaddr_in serv_addr,client_addr;
    char buffer[SIZE];
    serv_addr_len=sizeof(serv_addr);

    client_fd=socket(AF_INET,SOCK_DGRAM,0);
    
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

/*    strcpy(buffer,"Neha is a good girl");
    sendto(client_fd,buffer,SIZE,0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    recvfrom(client_fd,buffer,SIZE,0,(struct sockaddr*)&serv_addr,&serv_addr_len);
    puts(buffer);*/

    while(1){
        printf("You: ");
        fgets(buffer,SIZE,stdin);
        buffer[strcspn(buffer,"\n")]='\0';
        sendto(client_fd,buffer,SIZE,0,(struct sockaddr*)&serv_addr,serv_addr_len);
        if(strcasecmp(buffer,"exit")==0){
            printf("You exited the chat\n");
            break;
        }

        recvfrom(client_fd,buffer,SIZE,0,(struct sockaddr*)&serv_addr,&serv_addr_len);
        if(strcasecmp(buffer,"exit")==0){
            printf("Server exited the chat\n");
            break;
        }
        printf("Server: %s\n",buffer);
    }

    close(client_fd);
}
