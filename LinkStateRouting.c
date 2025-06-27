#include<stdio.h>
#include<limits.h>

void main(){
    int adj_mat[10][10],src,dist[10],visited[10],n;

    printf("How many routers? ");
    scanf("%d",&n);

    printf("Enter the adjacency matrix: \n");
    for(int i=0 ; i<n ; i++)
        for(int j=0 ; j<n ; j++)
            scanf("%d",&adj_mat[i][j]);

    printf("Enter the source vertex: ");
    scanf("%d",&src);

    for(int i=0 ;i<n ; i++){
        visited[i]=0;
        dist[i]=INT_MAX;
    }

    dist[src]=0;

    for(int i=0 ; i<n-1 ; i++){
        int min_index,min=INT_MAX;

        for(int j=0 ; j<n-1 ; j++)
            if(!visited[j] && dist[j]<min){
                min_index=j;
                min=dist[min_index];
            }

        visited[min_index]=1;

        for(int j=0 ; j<n ; j++){
            if(!visited[j] && dist[min_index]!=INT_MAX && adj_mat[min_index][j]!=0 && dist[j]>dist[min_index]+adj_mat[min_index][j]){
                dist[j]=dist[min_index]+adj_mat[min_index][j];
            }
        }
    }

    printf("vertex\tdistance from source\n");
    for(int i=0 ; i<n ; i++){
        printf("%d\t%d\n",i,dist[i]);
    }
}