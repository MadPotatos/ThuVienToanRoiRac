#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"graph.h" 
#include"dagtopo.h" 
#include"dijkbell.h"
void docfile(Graph g, char *filename){
    FILE *fp = fopen(filename,"r");
    if(fp==NULL){
        printf("Errot file\n");
        exit(1);
    }
    int n,m;
    fscanf(fp,"%d %d\n",&n,&m);
    int v;
    char dinh[20];
    for(int i=0;i<n;i++){
        fscanf(fp,"%d %s\n",&v,dinh);
        printf("%d %s\n",i,dinh);
        addVertex(g,i,dinh);
    }
    int x,y;
    double z;
    for(int i=0;i<m;i++){
        fscanf(fp,"%d %d %lf",&x,&y,&z);
        addEdge(g,x,y,z);
        addEdge(g,y,x,z);
        printf("%d %d %lf\n",x,y,z);
    }
    fclose(fp);
}

void  dagtopol(){
    int n,i,output[10000];
    Graph g =createGraph();
    g=readfile_g("DAG.txt");
    if(DAG){
        printf("Do thi phi chu trinh(DAG)\n");
        printf("Topologi: ");
        n = topologicalsort(g,output);
        for(i = 0;i<n;i++){
            printf("%d ",output[i]);
        }
        printf("\n");
    }else{
        printf("Do thi phi chu trinh\n");
    }

}
void short_dijkstra(){
    printf("Dijkstra: \n");
    Graph g= createGraph();
    g = readfile_g("graph.txt");
    print_dijkstra(g,0,4);
    printf("\n");
    
}
void short_bellman(){
    printf("Bellman: \n");
    Graph g= createGraph();
    g = readfile_g("graph.txt");
    print_bellman(g,0,4);
    printf("\n");
}

int main(){
    dagtopol(); 
    short_dijkstra();
    short_bellman();
    Graph g=createGraph();
    g= readfile("graph.txt");
    graphiz(g);
    return 0;
}