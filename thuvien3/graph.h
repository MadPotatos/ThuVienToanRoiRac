#ifndef _GRAPH_H_
#define _GRAPH_H_
#define INFINITIVE_VALUE 10000000
#include "jrb.h"
#include "dllist.h"
typedef struct
{
  JRB edges;
  JRB vertices;
} Graph;
// Do thi lien ket
Graph createGraph();
void addVertex(Graph graph, int id, char *name);
char *getVertex(Graph graph, int id);
int hasEdge(Graph graph, int v1, int v2);
void addEdge(Graph graph, int v1, int v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2);
int getAdjacentVertices(JRB graph, int v, int *output);
int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);
void dropGraph(Graph graph);
double shortestPath(Graph graph, int s, int t, int *path, int *length);
//file graph.txt dothi
Graph readfile_gr(char *filename);
Graph readfile_g(char *filename);
Graph readfile(char *filename);
void graphiz(Graph g);
//lienthong
int lienthongdothivohuong(Graph graph);
//lien thong manh
int MIN(int a, int b);
void Tarjan(Graph graph, int vertex, Dllist stack);
int lienthongmanh(Graph g);
void solienthongmanh(Graph g);

#endif
