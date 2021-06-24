//lien thong + cay bao trum + dfs bfs 

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"graph.h"  
#include"dfsbfs.h"
#include"krukal.h"
#include"prim.h"
void lienthongmanhz(){
    Graph g =createGraph();
    addVertex(g,1,"A");
    addVertex(g,2,"B");
    addVertex(g,3,"C");
    addVertex(g,4,"D");
    addVertex(g,5,"E");
    addVertex(g,6,"F");
    addVertex(g,7,"G");
    addVertex(g,8,"H");
    addEdge(g,1,2,1);
    addEdge(g,2,3,1);
    addEdge(g,3,1,1);
    addEdge(g,4,5,1);
    addEdge(g,5,4,1);
    addEdge(g,5,6,1);
    addEdge(g,7,6,1);
    printf("\nSo thanh phan lien thanh manh %d",lienthongmanh(g));
    graphiz_ch(g);
    dropGraph(g);
}

void lienthong()
{
    Graph g =createGraph();
    g = readfile("graph.txt");
    printf("\nSo thanh phan lien thong: %d",lienthongdothivohuong(g));
    graphiz_vh(g);
    dropGraph(g);
}


void caybaotrum_kru(){
    printf("Cay bao trum Kru:\n");
    int edge[10000],i,u,n;
    Graph g = createGraph();
    g = readfile("graph2.txt");
    //
    n = Kruskal(g,edge);
    graphiz_mst(g,edge,n);
    dropGraph(g);
   
}
void caybaotrum_prim(){

    printf("\nCay bao trum prim:\n");
    Graph_prim g2 = createGraph_prim();
    // tao đồ thị
    readfile_prim(g2, "graph2.txt");
    //
    int edge[10000];
    prim(g2, 1, edge);
    dropGraph_prim(g2);
}
void bfsanddfs(){
    Graph g= createGraph();
    g = readfile_g("graph2.txt");
    printf("\nDuyet DFS: ");
    DFS(g);
    printf("\nDuyet BFS: ");
    BFS(g);
    printf("\n");
    //BFSc7(g,0);
    dropGraph(g);
}

int main(){
    printf("\n=================\n");
    caybaotrum_kru(); 
    printf("\n=================\n");
    caybaotrum_prim();
    printf("\n=================\n");
    lienthong();
    printf("\n=================\n");
    lienthongmanhz();
    printf("\n=================\n");
    bfsanddfs(); 
    printf("\n=================\n");
    return 0;
}