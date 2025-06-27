#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<time.h>

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

    while(1){
        recvfrom(serv_fd,buffer,SIZE,0,(struct sockaddr*)&client_addr,&client_addr_len);

        time_t curr_time;
        time(&curr_time);
        strcpy(buffer,ctime(&curr_time));
        sendto(serv_fd,buffer,SIZE,0,(struct sockaddr*)&client_addr,client_addr_len);
    }

    close(serv_fd);
}
