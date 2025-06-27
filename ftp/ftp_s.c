#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 1200
#define SIZE 1024

void reverse(char str[]){
    int low=0,high=strlen(str)-1;

    while(low<high){
        char temp=str[low];
        str[low]=str[high];
        str[high]=temp;

        low++;
        high--;
    }
}

void main(){
    int serv_fd,client_fd,n=0;
    struct sockaddr_in serv_addr;
    char lines[100][SIZE],buffer[SIZE];
    FILE* fd;

    serv_fd=socket(AF_INET,SOCK_STREAM,0);
    
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    listen(serv_fd,5);

    client_fd=accept(serv_fd,NULL,NULL);

    while(1){
        recv(client_fd,buffer,SIZE,0);
        if(strcasecmp(buffer,"eof")==0)
            break;

        strcpy(lines[n++],buffer);
    }

    fd=fopen("out.txt","w");
    for(int i=n-1 ; i>=0 ; i--){
        reverse(lines[i]);   
        printf("%s\n",lines[i]);
        fprintf(fd,"%s\n",lines[i]);
    }

    fclose(fd);
    close(client_fd);
    close(serv_fd);
}
