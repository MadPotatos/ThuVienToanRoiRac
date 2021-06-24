//lien thong + cay bao trum + dfs bfs 

#include<stdlib.h>
#include<stdio.h>
#include<string.h>


#include"graph.h"  
#include"dfsbfs.h"
#include"mst.h"
#include"prim.h"

void lienthong()
{
    Graph g =createGraph();
    g = readfile("graph.txt");
    printf("\nSo thanh phan lien thong: %d",lienthongdothivohuong(g));
    JRB tmp;
    graphiz_vh(g);
    dropGraph(g);
}
void lienthongmanhz(){
    Graph g =createGraph();
    addVertex(g,1,"A");
    addVertex(g,2,"B");
    addVertex(g,3,"C");
    addVertex(g,4,"D");
    addVertex(g,5,"E");
    
    addEdge(g,1,2,1);
    addEdge(g,2,3,1);
    addEdge(g,3,1,1);
    addEdge(g,4,5,1);
    addEdge(g,5,4,1);
    //g=readfile_g("graph.txt");
    printf("\nSo thanh phan lien thanh manh %d",lienthongmanh(g));
    graphiz_ch(g);
    dropGraph(g);
}

void caybaotrum_kru(){
    printf("Cay bao trum Kru:\n");
    int edge[10000],i,u,n;
    Graph g = createGraph();
    g = readfile("DAG.txt");
    n = Kruskal(g,edge);
    graphiz_mst(g,edge,n);
    dropGraph(g);
   
}
void caybaotrum_prim(){

    printf("\nCay bao trum prim:\n");
    Graph_prim g2 = createGraph_prim();
    readfile_prim(g2, "DAG.txt");
    int edge1[10000];
    prim(g2, 1, edge1);
}
void bfsanddfs(){
    Graph g= createGraph();
    g = readfile_g("DAG.txt");
    printf("\nDuyet DFS: ");
    DFS(g);
    printf("\nDuyet BFS: ");
    BFS(g);
    printf("\n");
    //BFSc7(g,0);
    dropGraph(g);
}

int main(){
    caybaotrum_kru(); 
    caybaotrum_prim();
    lienthong();
    lienthongmanhz();
    bfsanddfs(); 

    return 0;
}