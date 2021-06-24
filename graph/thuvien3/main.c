#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"graph.h" 
#include"dagtopo.h" 
#include"dijkbell.h"

void  dagtopol(){
    int n,i,output[10000];
    Graph g =createGraph();
    g=readfile_g("DAG.txt");
    if(DAG){
        printf("Do thi phi chu trinh(DAG)\n");
        printf("Topologi: ");
        n = topologicalsort(g,output);
        for(i = 0;i<n;i++){
            printf("%s ",getVertex(g,output[i]));
        }
        printf("\n");
    }else{
        printf("Do thi co chu trinh\n");
    }
    graphiz_ch(g);
    dropGraph(g);
}
void short_dijkstra(){
    printf("Dijkstra: \n");
    Graph g= createGraph();
    g = readfile_g("graph1.txt");
    print_dijkstra(g,0,5);
    printf("\n");

}
void short_bellman(){
    printf("Bellman: \n");
    Graph g= createGraph();
    g = readfile_g("graph2.txt");
    print_bellman(g,0,5);
    printf("\n");
}

int main(){
    printf("\n=============================\n");
    dagtopol(); 
    printf("\n=============================\n");
    short_dijkstra();
    printf("\n=============================\n");
    short_bellman();
    printf("\n=============================\n");
    return 0;
}