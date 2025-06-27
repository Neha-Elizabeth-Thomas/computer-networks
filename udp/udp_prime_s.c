#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 1200
int factors[20],n;

int isPrime(int num){
    int  prime=1;
    for(int i=2 ; i<num ; i++)
        if(num%i==0){
            prime=0;
            factors[n++]=i;
        }
    return prime;
}

void main(){
    int serv_fd,client_addr_len;
    struct sockaddr_in serv_addr,client_addr;
    char buffer[100];
    client_addr_len=sizeof(client_addr);

    serv_fd=socket(AF_INET,SOCK_DGRAM,0);
    
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=INADDR_ANY;

    bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

/*    recvfrom(serv_fd,buffer,sizeof(buffer),0,(struct sockaddr*)&client_addr,&client_addr_len);
    puts(buffer);
    strcpy(buffer,"thavala");
    sendto(serv_fd,buffer,sizeof(buffer),0,(struct sockaddr*)&client_addr,client_addr_len);*/

    while(1){
        int num;
        recvfrom(serv_fd,&num,sizeof(num),0,(struct sockaddr*)&client_addr,&client_addr_len);
        printf("Number received: %d\n",num);
        if(num==9999)
            break;

        if(isPrime(num)){
            printf("%d PRIME\n",num);
        }else{
            printf("%d NOT PRIME\nFactors are:\n",num);
            for(int i=0 ; i<n ; i++)
                printf("%5d",factors[i]);
            printf("\n");
        }
    }


    close(serv_fd);
}
