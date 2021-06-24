#include"graph.h"

//Kruskal
int find(int x,int *cha);
void unionz(int x, int y,int *rank,int *cha);
int Kruskal(Graph graph, int *out);
int checking(Graph  g,int *edge,int n,int u,int v);
int checking2(Graph  g,int *edge,int n,int u);
void graphiz_kru(Graph  g,int *edge,int n);
void graphiz_mst(Graph  g,int *edge,int n);
