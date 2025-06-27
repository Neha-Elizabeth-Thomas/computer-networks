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
    int serv_fd,client_addr_len;
    struct sockaddr_in serv_addr,client_addr;
    char buffer[SIZE];
    client_addr_len=sizeof(client_addr);

    serv_fd=socket(AF_INET,SOCK_DGRAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=INADDR_ANY;

    bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

/*    recvfrom(serv_fd,buffer,SIZE,0,(struct sockaddr*)&client_addr,&client_addr_len);
    printf("%s\n",buffer);
    strcpy(buffer,"Nja ");
    sendto(serv_fd,buffer,SIZE,0,(struct sockaddr*)&client_addr,client_addr_len);*/

    while(1){
        recvfrom(serv_fd,buffer,SIZE,0,(struct sockaddr*)&client_addr,&client_addr_len);
        if(strcasecmp(buffer,"exit")==0){
            printf("Client exited chat\n");
            break;
        }
        printf("Client: %s\n",buffer);

        printf("You: ");
        fgets(buffer,SIZE,stdin);
        buffer[strcspn(buffer,"\n")]='\0';
        sendto(serv_fd,buffer,SIZE,0,(struct sockaddr*)&client_addr,client_addr_len);
        if(strcasecmp(buffer,"exit")==0){
            printf("You exited the chat\n");
            break;
        }
    }

    close(serv_fd);
}
