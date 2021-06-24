#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"graph.h" 
#include"dagtopo.h" 
#include"dijkbell.h"
void  dagtopol(char *filename);
void short_dijkstra(char *filename);
void short_bellman(char *filename);
void short_dijkstra1(char *filename);
void testcase1(){
    printf("\n=============================\n");
    dagtopol("DAG.txt"); 
    printf("\n=============================\n");
    short_dijkstra("graph1.txt");
    printf("\n=============================\n");
    short_bellman("graph2.txt");
    printf("\n=============================\n");
}
void testcase2(){
    printf("\n=============================\n");
    dagtopol("DAG1.txt"); 
    printf("\n=============================\n");
    short_dijkstra1("graph1.txt");
    printf("\n=============================\n");
    short_bellman("graph3.txt");
    printf("\n=============================\n");
}

int main(){
    //testcase1();
    testcase2();
    return 0;
}


void  dagtopol(char *filename){
    int n,i,output[10000];
    //Doc du lieu tu file txt
    Graph g =createGraph();
    g = readfile_g(filename);
    //Chay thuat toan topo
    if(DAG(g)){
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
void short_dijkstra(char *filename){
    printf("Dijkstra: \n");
    //Doc du lieu tu file
    Graph g= createGraph();
    g = readfile_g(filename);
    //chay thuat toan topo
    print_dijkstra(g,0,5);
    printf("\n");

}
void short_dijkstra1(char *filename){
    printf("Dijkstra: \n");
    //Doc du lieu tu file
    Graph g= createGraph();
    g = readfile_g(filename);
    //chay thuat toan topo
    print_dijkstra(g,5,0);
    printf("\n");

}
void short_bellman(char *filename){
    printf("Bellman: \n");
    //Doc du lieu tu file
    Graph g= createGraph();
    g = readfile_g(filename);
    //chay thuat toan to po
    print_bellman(g,0,5);
    printf("\n");
}