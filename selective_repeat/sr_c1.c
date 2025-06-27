#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<time.h>

#define PORT 1200
#define TOTAL_PACKETS 10
#define WINDOW_SIZE 4

struct packet{
    int seq_no;
    int acked;
    int sent;
};

void main(){
    int client_fd;
    struct sockaddr_in serv_addr;

    client_fd=socket(AF_INET,SOCK_STREAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(client_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    struct packet packets[TOTAL_PACKETS];
    for(int i=0 ; i<TOTAL_PACKETS ; i++){
        packets[i].seq_no=i;
        packets[i].sent=0;
        packets[i].acked=0;
    }
    int base=0;
    srand(time(NULL));

    while(base<TOTAL_PACKETS){
        //SENDING
        for(int i=base ; i<base+WINDOW_SIZE && i<TOTAL_PACKETS ; i++){
            if(packets[i].acked==0 && packets[i].sent==0){
                if(rand()%4!=0){
                    send(client_fd,&i,sizeof(i),0);
                    printf("SENT: seq %d\n",i);
                }else{
                    printf("LOST: seq %d\n",i);
                }
                packets[i].sent=1;
            }
        }

        //RECEIVING
        struct timeval timeout={2,0};
        fd_set read_fd;
        FD_ZERO(&read_fd);
        FD_SET(client_fd,&read_fd);
        int ret=select(client_fd+1,&read_fd,NULL,NULL,&timeout);
        int ack;
        if(ret>0){
            recv(client_fd,&ack,sizeof(ack),0);
            printf("RECEIVED: ack %d\n",ack);
            if(packets[ack].acked){
                printf("Duplicate Ack..Discarded\n");
            }else{
                packets[ack].acked=1;
            }

            while(base<TOTAL_PACKETS && packets[base].acked){
                    base++;
            }
            printf("Window slided: [%d - %d]\n",base,base+WINDOW_SIZE-1);
        }else{
            printf("TIMEOUT..Resending unacknowledged packets in the window [%d - %d]\n",base,base+WINDOW_SIZE-1);
            for(int i=base ; i<base+WINDOW_SIZE && i<TOTAL_PACKETS ; i++)
                packets[i].sent=0;
        }

    }
    close(client_fd);
}




