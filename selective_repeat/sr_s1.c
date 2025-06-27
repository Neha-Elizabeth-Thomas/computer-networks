#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define PORT 1200
#define TOTAL_PACKETS 10
void main(){
    int serv_fd,client_fd;
    struct sockaddr_in serv_addr;

    serv_fd=socket(AF_INET,SOCK_STREAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    listen(serv_fd,5);

    client_fd=accept(serv_fd,NULL,NULL);

    int received[TOTAL_PACKETS],tot_received=0;
    for(int i=0 ; i<TOTAL_PACKETS ; i++)
        received[i]=0;
    int seq_no;

    while(tot_received<TOTAL_PACKETS){
        printf("\n");
        recv(client_fd,&seq_no,sizeof(seq_no),0);
        printf("RECEIVED: seq %d\n",seq_no);
        if(received[seq_no]){
            printf("Duplicate packet discarded\n");
            continue;
        }else{
            received[seq_no]=1;
            tot_received++;
        }

        //SEND ACK
        send(client_fd,&seq_no,sizeof(seq_no),0);
        printf("SENT: ACK %d\n",seq_no);   
    }
    
    close(client_fd);
    close(serv_fd);
}
