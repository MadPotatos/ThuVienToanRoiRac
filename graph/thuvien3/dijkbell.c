#include "dijkbell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
int checkdij1(Graph g, int *path, int n, int u)
{
  for (int i = 0; i < n; i++)
  {
    if (u == path[i])
      return 1;
  }
  return 0;
}
int checkdij2(Graph g, int *path, int n, int u, int v)
{
  int x, y;
  for (int i = 0; i < n - 1; i++)
  {
    x = path[i];
    y = path[i + 1];
    if (x == u && y == v)
      return 1;
    if (x == v && y == u)
      return 1;
  }
  return 0;
}
void graphiz_dijkstra(Graph g, int *path, int nz, char *filename)
{
  FILE *fp = fopen(filename, "wb");
  if (fp == NULL)
    printf("Error\n");
  fprintf(fp, "digraph{\n");
  JRB tmp;
  int dist, n, u, v, i, output[10000];
  int visited[10000] = {};
  jrb_traverse(tmp, g.vertices)
  {
    u = tmp->key.i;
    if (checkdij1(g, path, nz, u))
    {
      fprintf(fp, "%s [fillcolor=red, style=filled, style = bold, color=red, fontcolor=red];\n", getVertex(g, u));
    }
    else
      fprintf(fp, "%s [fillcolor=white, style=filled];\n", getVertex(g, u));
  }
  int x, y;
  /*
  for(int i = 0; i<nz-1;i++){
      x= path[i];
      y= path[i+1];
      dist=(int)getEdgeValue(g,x,y);
      fprintf(fp,"%s -> %s [weight = %d] [label = %d];\n",getVertex(g,x),getVertex(g,y),dist,dist);
  }*/
  Dllist queue, node;
  queue = new_dllist();
  int z;
  jrb_traverse(tmp, g.vertices)
  {
    z = tmp->key.i;
    if (!visited[z])
    {
      dll_append(queue, new_jval_i(z));
      while (!dll_empty(queue))
      {
        node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[u])
        {
          visited[u] = 1;
          n = outdegree(g, u, output);
          for (i = 0; i < n; i++)
          {

            v = output[i];
            if (!visited[v])
              dll_append(queue, new_jval_i(v));
              //if (visited[u] == 0 || visited[v] == 0)
              //fprintf(fp,"%d -- %d [];\n",u,v);
              if (u != v)
              {
                x = u;
                y = v;
                dist = (int)getEdgeValue(g, x, y);
                if (checkdij2(g, path, nz, u, v))
                {
                  fprintf(fp, "%s -> %s [weight = %d,label = %d, style = bold, color=red];\n", getVertex(g, x), getVertex(g, y), dist, dist);
                }
                else
                  fprintf(fp, "%s -> %s [weight = %d,label = %d];\n", getVertex(g, x), getVertex(g, y), dist, dist);
              }
          }
        }
      }
    }
  }

  fprintf(fp, "}");

  fclose(fp);
}
double dijkstra(Graph g, int s, int t, int *path, int *length)
{
  double dist[10000], min, w, total;
  int pre[10000], u, v, n, output[10000];
  for (int i = 0; i < 10000; i++)
  {
    dist[i] = INFINITIVE_VALUE;
  }
  int *visited = (int *)calloc(10000, sizeof(int));
  Dllist queue = new_dllist(), node, ptr;
  dll_append(queue, new_jval_i(s));
  JRB tmp, tmp1, tmp2;
  dist[s] = 0;
  while (!dll_empty(queue))
  {
    min = INFINITIVE_VALUE;
    //queue uu tien
    dll_traverse(ptr, queue)
    {
      u = jval_i(ptr->val);
      if (min > dist[u])
      {
        min = dist[u];
        node = ptr;
      }
    }
    u = jval_i(node->val);
    dll_delete_node(node);

    if (u == t)   break;

    n = outdegree(g, u, output);
    tmp = jrb_find_int(g.edges, u);
    if (!visited[u])
    {
      for (int i = 0; i < n; i++)
      {
        v = output[i];
        w = getEdgeValue(g, u, v);
        dll_append(queue, new_jval_i(output[i]));
        if (dist[output[i]] == INFINITIVE_VALUE)
        {
          dist[v] = w + dist[u];
          pre[v] = u;
        }
        else if (w + dist[u] < dist[v])
        {
          dist[v] = w + dist[u];
          pre[v] = u;
        }
      }
    }
    visited[u] = 1;
  }
  total = dist[t];
  if (total != INFINITIVE_VALUE)
  {
    int arr[10000];
    int x = 0;
    int y = t;
    while (y != s)
    {
      arr[x++] = y;
      y = pre[y];
    }
    arr[x++] = s;
    *length = 0;
    for (int i = x - 1; i >= 0; i--)
    {
      path[(*length)++] = arr[i];
    }
  }
  return total;
}

void print_dijkstra(Graph g, int s, int t)
{
  int i, length, path[10000];
  int w;
  w = (int)dijkstra(g, s, t, path, &length);
  if (w == INFINITIVE_VALUE)
  {
    printf("Khong co duong di tu %s den %s\n", getVertex(g, s), getVertex(g, t));
  }
  else
  {
    printf("Duong di %s den %s || Het %dm\n", getVertex(g, s), getVertex(g, t), w);
    for (i = 0; i < length; i++)
      printf(" => %s", getVertex(g, path[i]));
    //printf(" => %s %s", getVertex(g, path[i]),getVertex(g, path[i+1]));
    graphiz_dijkstra(g, path, length, "dijkstra.dot");
  }
    printf("\nDa xuat ra file dijkstra.dot\n");
}

int save_pos[10000];
double shortestPath_version_BellMan(Graph g, int s, int t, int* path, int* length) {
   double * dist = calloc(sizeof(double), 10000);
   int* pre = calloc(sizeof(int),30000);
   int* visit = calloc(sizeof(int),30000);
   double total;
   int i, j,u,v,w,sodinh,n,output[10000];
   JRB vertex, edge;
   for(int i = 0; i < 10000; ++i) 
      dist[i] = INFINITIVE_VALUE;
   sodinh = 0;
   jrb_traverse(vertex, g.vertices)
      sodinh++;
    dist[s] = 0;
   for(i = 0; i < (sodinh - 1); ++i)
      for(u = 0; u < sodinh; ++u) {
         n = outdegree(g, u, output);
         for(j = 0; j < n; ++j) {
            v = output[j];
            w = getEdgeValue(g, u, v);
            if ( dist[v] > dist[u] + w ) {    
               dist[v] = dist[u] + w;
               pre[v] = u;
            }
         }
      }
   total = dist[t]; 
   if (total != INFINITIVE_VALUE)
   {
      visit[0] = t;
      n = 1;              
      while (t != s)
      {
            t = pre[t];
            visit[n++] = t;
      }
      for (i=n-1; i>=0; i--)
            path[n-i-1] = visit[i];
      *length = n;                
   }
   for(u = 0; u < sodinh; ++u) {
         n = outdegree(g, u, output);
         for(i = 0; i < n; ++i) {
            v = output[i];
            w = getEdgeValue(g, u, v);
            if ( dist[v] > dist[u] + w ) {    
               printf("Do thi co chu trinh am\n");
               return -1;
            }
         }
      }
   
   free(dist);
   free(pre);
   free(visit);
   return total;   
}


void print_bellman(Graph g, int s, int t)
{
  int i, length, path[10000];
  int w;
  w = (int)shortestPath_version_BellMan(g, s, t, path, &length);
  if(w ==-1){
    printf("Do thi co chu trinh am\n");
  }
  else if (w == INFINITIVE_VALUE)
  {
    printf("Khong co duong di tu %s den %s\n", getVertex(g, s), getVertex(g, t));
  }
  else
  {
    printf("Duong di %s den %s || Het %dm\n", getVertex(g, s), getVertex(g, t), w);
    for (i = 0; i < length; i++)
      printf(" => %s", getVertex(g, path[i]));
    //printf(" => %s %s", getVertex(g, path[i]),getVertex(g, path[i+1]));
    graphiz_dijkstra(g, path, length, "bellman.dot");
      printf("\nDa xuat ra file bellman.dot\n");
  }
}
