#include<stdio.h>

void main(){
    int bucket,bsize,out,n,in;

    printf("How many input? ");
    scanf("%d",&n);

    printf("Enter the bucket size: ");
    scanf("%d",&bsize);

    bucket=0;
    printf("Enter the outgoing rate: ");
    scanf("%d",&out);

    for(int i=0 ; i<n ; i++){
        printf("----------------------------------\n");
        printf("Enter the packet size at time%d: ",i+1);
        scanf("%d",&in);

        if(in<=(bsize-bucket)){
            bucket+=in;
            printf("Bucket status: %d out of %d\n",bucket,bsize);
        }else{
            printf("Dropped packets=%d\n",in-(bsize-bucket));
            bucket=bsize;
            printf("Bucket status: %d out of %d\n",bucket,bsize);
        }
        int sent=bucket>=out?out:bucket;
        bucket-=sent;
        printf("After outgoing,bucket status: %d out of %d\n",bucket,bsize);
    }
}