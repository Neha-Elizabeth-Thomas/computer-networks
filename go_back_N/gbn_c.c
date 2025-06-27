#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<time.h>
#include<sys/time.h>

#define PORT 1200
#define SIZE 1024
#define TOTAL_PACKETS 10
#define WINDOW_SIZE 4

void main(){
    int client_fd;
    struct sockaddr_in serv_addr;

    client_fd=socket(AF_INET,SOCK_STREAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(client_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    int seq_no=0;
    int ack;
    int base=0;
    srand(time(NULL));
    while(base<TOTAL_PACKETS){
        printf("\n\n");
        //SEND current window
        while(seq_no<base+WINDOW_SIZE && seq_no<TOTAL_PACKETS){
            if(rand()%4!=0){
                send(client_fd,&seq_no,sizeof(seq_no),0);
                printf("Sent: seqno=%d[%d - %d]\n",seq_no,base,base+WINDOW_SIZE-1);
                seq_no++;
            }else{
                printf("Lost: seqno=%d[%d - %d]\n",seq_no,base,base+WINDOW_SIZE-1);
                seq_no++;
            }
        }

        //RECV ack
        fd_set read_fd;   
        struct timeval timeout={3,0};

        FD_ZERO(&read_fd);
        FD_SET(client_fd,&read_fd);
        int ret=select(client_fd+1,&read_fd,NULL,NULL,&timeout);

        if(ret>0){
            recv(client_fd,&ack,sizeof(ack),0);
            if(ack>base){
                printf("ACK received: [ACK%d]\nWindow advanced [%d - %d]\n",ack,ack,ack+WINDOW_SIZE-1);
                base=ack;
            }
        }else{
            printf("TIMEOUT: RESENDING CURRENT WINDOW[%d - %d]..\n",base,base+WINDOW_SIZE-1);
            seq_no=base;
        }
    }

    close(client_fd);
}
