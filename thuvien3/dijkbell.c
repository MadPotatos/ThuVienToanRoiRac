#include"dijkbell.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"graph.h"
int checkdij1(Graph g, int *path, int n,int u){
  for(int i=0;i<n;i++){
    if(u==path[i]) return 1;
  }
  return 0;
}
int checkdij2(Graph g, int *path, int n,int u,int v){
  int x,y;
  for(int i=0;i<n-1;i++){
    x= path[i];
    y=path[i+1];
    if(x==u&&y==v) return 1;
    if(x==v&&y==u) return 1;
  }
  return 0;
}
void graphiz_dijkstra(Graph g, int *path, int nz,char *filename ){
  FILE *fp =fopen(filename,"wb");
  if(fp == NULL) printf("Error\n");
  fprintf(fp, "digraph{\n");
  JRB tmp;
  int dist,n,u, v, i, output[10000];
  int visited[10000]={};
  jrb_traverse(tmp,g.vertices){
    u = tmp->key.i;
    if(checkdij1(g,path,nz,u)){
      fprintf(fp, "%s [fillcolor=red, style=filled, style = bold, color=red, fontcolor=red];\n",getVertex(g,u));
    }else
    fprintf(fp, "%s [fillcolor=white, style=filled];\n",getVertex(g,u));
  }
  int x,y;
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
            if(visited[u]==0||visited[v]==0)
              //fprintf(fp,"%d -- %d [];\n",u,v);
              if(u !=v){
                x =u;
                y =v;
                dist=(int)getEdgeValue(g,x,y);
                if(checkdij2(g,path,nz,u,v)){
                  fprintf(fp,"%s -> %s [weight = %d,label = %d, style = bold, color=red];\n",getVertex(g,x),getVertex(g,y),dist,dist);
                }else
                  fprintf(fp,"%s -> %s [weight = %d,label = %d];\n",getVertex(g,x),getVertex(g,y),dist,dist);

              
              }
              
            }
          
        }
      }
    }

  }




  fprintf(fp,"}");
  fclose(fp); 
}
double dijkstra(Graph g, int s, int t,int *path,int *length)
{
  double distance[1000], min, w, total;
  int previous[1000], tmp[1000];
  int n, output[100], i, u, v, start;
  Dllist ptr, queue, node;

  for (i = 0; i < 1000; i++)
    distance[i] = INFINITIVE_VALUE;
  distance[s] = 0;
  previous[s] = s;

  queue = new_dllist();
  dll_append(queue, new_jval_i(s));

  while (!dll_empty(queue))
  {
    // get u from the priority queue
    min = INFINITIVE_VALUE;
    dll_traverse(ptr, queue)
    {
      u = jval_i(ptr->val);
      if (min > distance[u])
      {
        min = distance[u];
        node = ptr;
      }
    }
    dll_delete_node(node);

    if (u == t)
      break; // stop at t

    n = outdegree(g, u, output);
    for (i = 0; i < n; i++)
    {
      v = output[i];
      w = getEdgeValue(g, u, v);
      if (distance[v] > distance[u] + w)
      {
        distance[v] = distance[u] + w;
        previous[v] = u;
      }
      dll_append(queue, new_jval_i(v));
    }
  }
  total = distance[t];
  if (total != INFINITIVE_VALUE)
  {
    tmp[0] = t;
    n = 1;
    while (t != s)
    {
      t = previous[t];
      tmp[n++] = t;
    }
    for (i = n - 1; i >= 0; i--)
      path[n - i - 1] = tmp[i];
    *length = n;
  }
  
  return total;
}

void print_dijkstra(Graph g, int s, int t){
    int i, length, path[10000];
    int w;
    w =(int)dijkstra(g, s, t, path, &length);
    if (w == INFINITIVE_VALUE)
    {
         printf("Khong co duong di tu %s den %s\n", getVertex(g, s), getVertex(g, t));
    }else
    {
         printf("Duong di %s den %s || Het %dm\n", getVertex(g, s), getVertex(g, t), w);
         for (i=0; i<length; i++)
             printf(" => %s", getVertex(g, path[i]));
             //printf(" => %s %s", getVertex(g, path[i]),getVertex(g, path[i+1]));
          graphiz_dijkstra(g,path,length,"dijkstra.dot");
    }

}

int save_pos[1000];
double shortestPath_version_BellMan(Graph g, int s, int t, int *path, int *length)
{
    double distance[1000], min, w, total;
    int previous[1000], tmp[1000];
    int n, output[100], i, u, v, start;
    Dllist ptr, queue, node;

    for (i = 0; i < 1000; i++)
        distance[i] = INFINITIVE_VALUE;
    distance[s] = 0;
    previous[s] = s;

    queue = new_dllist();
    dll_append(queue, new_jval_i(s));

    while (!dll_empty(queue))
    {
        // get u from the priority queue
        min = INFINITIVE_VALUE;
        dll_traverse(ptr, queue)
        {
            u = jval_i(ptr->val);
            if (min > distance[u])
            {
                min = distance[u];
                node = ptr;
            }
        }
        dll_delete_node(node);

        if (u == t)
            break; // stop at t

        n = outdegree(g, u, output);
        for (i = 0; i < n; i++)
        {
            v = output[i];
            w = getEdgeValue(g, u, v);

            if (distance[v] > distance[u] + w&&save_pos[v]!=1)
            {
                distance[v] = distance[u] + w;
                previous[v] = u;
            }
            dll_append(queue, new_jval_i(v));
            if(w<0)save_pos[v] = 1;
        }
    }
    total = distance[t];
    if (total != INFINITIVE_VALUE)
    {
        tmp[0] = t;
        n = 1;
        while (t != s)
        {
            t = previous[t];
            tmp[n++] = t;
        }
        for (i = n - 1; i >= 0; i--)
            path[n - i - 1] = tmp[i];
        *length = n;
    }
    return total;
}

void print_bellman(Graph g, int s, int t){
    int i, length, path[10000];
    int w;
    w =(int)shortestPath_version_BellMan(g, s, t, path, &length);
    if (w == INFINITIVE_VALUE)
    {
         printf("Khong co duong di tu %s den %s\n", getVertex(g, s), getVertex(g, t));
    }else
    {
         printf("Duong di %s den %s || Het %dm\n", getVertex(g, s), getVertex(g, t), w);
         for (i=0; i<length; i++)
             printf(" => %s", getVertex(g, path[i]));
             //printf(" => %s %s", getVertex(g, path[i]),getVertex(g, path[i+1]));
          graphiz_dijkstra(g,path,length,"bellman.dot");
    }

}
