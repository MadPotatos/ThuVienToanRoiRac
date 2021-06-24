#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"dfsbfs.h"
#include"graph.h"
//dfs bfs
void DFS(Graph g)
{
  int visited[10000] = {};
  int n, i, u, v, output[10000];
  Dllist stack, node;
  JRB tmp;
  stack = new_dllist();
  jrb_traverse(tmp, g.vertices)
  {
    u = tmp->key.i;
    if (!visited[u])
    {
      dll_append(stack, new_jval_i(u));
      while (!dll_empty(stack))
      {
        node = dll_last(stack);
        v = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[v])
        {
          printf("%d ", v);
          visited[v] = 1;
          n = outdegree(g, v, output);
          for (i = 0; i < n; i++)
          {
            v = output[i];
            if (!visited[v])
              dll_append(stack, new_jval_i(v));
          }
        }
      }
    }
  }
}
//BFS bat dau tu dinh nho nhat
void BFS(Graph g)
{
  int visited[10000] = {};
  int n, i, u, v, output[10000];
  Dllist queue, node;
  JRB tmp;
  queue = new_dllist();
  jrb_traverse(tmp, g.vertices)
  {
    u = tmp->key.i;
    if (!visited[u])
    {
      dll_append(queue, new_jval_i(u));
      while (!dll_empty(queue))
      {
        node = dll_first(queue);
        v = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[v])
        {
          printf("%d ", v);
          visited[v] = 1;
          n = outdegree(g, v, output);
          for (i = 0; i < n; i++)
          {
            v = output[i];
            if (!visited[v])
              dll_append(queue, new_jval_i(v));
          }
        }
      }
    }
  }
}
void graphiz_graph(Graph g){
  FILE *fp =fopen("dothi.dot","wb");
  if(fp == NULL) printf("Error\n");
  fprintf(fp, "graph{\n");
  JRB tmp;
  int dist,n, u, v, i, output[10000];
  int visited[10000]={};
  jrb_traverse(tmp,g.vertices){
    u = tmp->key.i;
    fprintf(fp, "%d [fillcolor=white, style=filled];\n", u);
  }
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
            if(visited[u]==0||visited[v]==0)
              dist= (int)getEdgeValue(g,u,v);
              fprintf(fp,"%s -- %s [weight = %d] [label = %d];\n",getVertex(g,u),getVertex(g,v),dist,dist);
          }
          
        }
      }
    }
  }
  fprintf(fp,"}");
  fclose(fp);
}

//Tinh kc tu 1 dinh den tat ca cac dinh con lai 
int *BFSc7(Graph g, int s)
{
  int visited[10000] = {};
  int n, i, u, v, output[10000], dist[10000];
  for (i = 0; i < 10000; i++)
  {
    dist[i] = 100000;
  }
  dist[s] = 0;

  Dllist queue, node;
  JRB tmp;
  queue = new_dllist();
  dll_append(queue, new_jval_i(s));
  while (!dll_empty(queue))
  {
    node = dll_first(queue);
    u = jval_i(node->val);
    dll_delete_node(node);
    n = outdegree(g, u, output);
    for (i = 0; i < n; i++)
    {
      v = output[i];
      if (dist[v] == 100000)
      {
        dll_append(queue, new_jval_i(v));
        dist[v]=dist[u]+1;
      }
    }
  }
  JRB tmp3;
  printf("Dinh    Khoang cach so voi s\n");
  jrb_traverse(tmp3,g.vertices){
    u=tmp3->key.i;
  printf("  %d           %d\n",u, dist[u]);
  } 
}


