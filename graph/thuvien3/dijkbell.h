#include"graph.h"
//
double dijkstra(Graph g, int s, int t,int *path,int *length);
void print_dijkstra(Graph g, int s, int t); // In ra duong di ngan nhat
void graphiz_dijkstra(Graph g, int *path, int n ,char *filename);
void graphiz_dij(Graph g, int *path,int length);
double shortestPath_version_BellMan(Graph g, int s, int t, int *path, int *length);
void print_bellman(Graph g, int s, int t);
//

