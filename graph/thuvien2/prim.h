#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"
#include <string.h>
#include "dllist.h"
typedef struct
{
    JRB edges;
    JRB vertices;
} Graph_prim;
Graph_prim createGraph_prim();
void addVertex_prim(Graph_prim g, int id, char *name);
char *getVertex_prim(Graph_prim g, int id);
void addEdge_prim(Graph_prim g, int v1, int v2, int dist);
int hasEdge_prim(Graph_prim g, int v1, int v2);
int indegree_prim(Graph_prim g, int v, int *output);
int outdegree_prim(Graph_prim g, int v, int *output);
int getEdgeValue_prim(Graph_prim graph, int v1, int v2);
void dropGraph_prim(Graph_prim graph);
int prim(Graph_prim g, int s, int *edge);
void readfile_prim(Graph_prim g, char *filename);




