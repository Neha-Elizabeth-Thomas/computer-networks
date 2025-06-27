#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 1200
#define SIZE 1024

/*void capitalize(char buffer[]){
    char prev_char=' ';
    for(int i=0 ; i<strlen(buffer) ; i++){
        if(prev_char==' ' && buffer[i]>='a' && buffer[i]<='z'){
            buffer[i]-=('a'-'A');
        }
        prev_char=buffer[i];
    }
}
*/
void main(){
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[SIZE];

    client_fd=socket(AF_INET,SOCK_STREAM,0);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(client_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
/*    while(1){
        recv(client_fd,buffer,SIZE,0);
        if(strcasecmp(buffer,"exit")==0)
            break;
        capitalize(buffer);
        printf("Result: %s\n",buffer);
    }*/

    while(1){
        printf("Enter string: ");
        fgets(buffer,SIZE,stdin);
        buffer[strcspn(buffer,"\n")]='\0';
        send(client_fd,buffer,SIZE,0);
        if(strcasecmp(buffer,"exit")==0)
            break;
    }


    close(client_fd);
}


