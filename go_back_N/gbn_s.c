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
    int expected_seq=0;
    int seq_no,ack;
    srand(time(NULL));
    while(expected_seq<TOTAL_PACKETS){
        printf("\n\n");
        //recv PACKET
        recv(client_fd,&seq_no,sizeof(seq_no),0);
        if(seq_no==expected_seq){
            printf("Received coorect: seqno=%d\n",seq_no);
            expected_seq++;
            ack=expected_seq;
        }else{
            printf("Received out of order: seqno=%d..DISCARDED\n",seq_no);
            ack=expected_seq;
        }

        if(rand()%4!=0){
            printf("SENT : ACK%d\n",ack);
            send(client_fd,&ack,sizeof(ack),0);
        }else{
            printf("SENT but LOST: ACK%d\n",ack);
        }
    }

    close(serv_fd);
    close(client_fd);
}





