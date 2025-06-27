#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 1200

void main(){
    int client_fd,serv_addr_len;
    struct sockaddr_in serv_addr;
    char buffer[100];

    serv_addr_len=sizeof(serv_addr);

    client_fd=socket(AF_INET,SOCK_DGRAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

/*    strcpy(buffer,"makri");
    sendto(client_fd,buffer,sizeof(buffer),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    recvfrom(client_fd,buffer,sizeof(buffer),0,(struct sockaddr*)&serv_addr,&serv_addr_len);
    puts(buffer);*/

    while(1){
        int num;
        printf("Enter a number: ");
        scanf("%d",&num);
        sendto(client_fd,&num,sizeof(num),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
        if(num==9999)
            break;
    }

    close(client_fd);
}
