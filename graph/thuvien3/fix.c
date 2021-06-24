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
  printf("\nDa xuat ra file dijkstra.dot\n");
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
      }else{
        
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


double dijkstra_v(Graph g, int s, int t, int* path, int* length)
{
   double *d = malloc(10000 * sizeof(double)), min, w, total; //khoang cach tu diem dau
    for(int i = 0; i < 10000; i++)
    {
        d[i] = INFINITIVE_VALUE;
    }
    d[s] = 0;
    int *diemtruoc = (int *)malloc(10000 * sizeof(int));
    int *check = (int *)calloc(10000, sizeof(int)); //visited
    Dllist queue = new_dllist(), node, ptr;
    dll_append(queue, new_jval_i(s));
    int u, v;
    int n;
    int output[1000];
    JRB tmp, tmp1, tmp2;
    while( !dll_empty(queue) )
    {
        min = INFINITIVE_VALUE;   
      dll_traverse(ptr, queue)
      {
          u = jval_i(ptr->val);              
          if (min > d[u])
          {
             min = d[u];
             node = ptr;
          }                 
      }
      u = jval_i(node->val);
      dll_delete_node(node);

      if (u == t) break;

        n = outdegree(g, u, output);
        tmp = jrb_find_int(g.edges, u);
        if(check[u] == 0)
        {
            for(int i = 0; i < n; i++)
            {
               v = output[i];
               w = getEdgeValue(g, u, v);
                dll_append(queue, new_jval_i(output[i]));
                if(d[output[i]] == 1000)
                {
                    d[v] = w + d[u];
                    diemtruoc[v] = u;
                }
                else if(w + d[u] < d[v])
                {
                    d[v] = w + d[u];
                    diemtruoc[v] = u;
                }

            }
        }
        check[u] = 1;
    }
    total = d[t];
    if(total != INFINITIVE_VALUE) {
    int arr[100];
    int x = 0;
    int m = t;
    while(m != s)
    {
        arr[x++] = m;
        m = diemtruoc[m];
    }
    arr[x++] = s;
    *length = 0;
    for(int i = x - 1; i >= 0; i--)
    {
        path[(*length)++] = arr[i];
        //printf("%s ", getVertex(g, arr[i]));
    }
    }
    return total;
}

void print_dijkstrav(Graph g, int s, int t){
    int i, length, path[10000];
    int w;
    w =(int)dijkstra_v(g, s, t, path, &length);
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
double bellmanford(Graph g, int s, int t, int* path, int* length) {
   double* distance = malloc(sizeof(double) * 10000);
   for(int i = 0; i < 10000; ++i) 
      distance[i] = INFINITIVE_VALUE;
   int* predecessor = malloc(sizeof(int) * 20000), *tmp = predecessor + 10000;
   memset(predecessor, 0, sizeof(int) * 20000);
   double total;
   int out[100];
   int i, j;
   int u, v, w;
   int v_num, n;
   JRB vertex, edge;

   //for(i = 0; i < 1000; i++)
   //   distance[i] = oo;
   distance[s] = 0;

   v_num = 0;
   jrb_traverse(vertex, g.vertices)
      v_num++;

   for(i = 0; i < (v_num - 1); ++i)
      for(u = 0; u < v_num; ++u) {
         n = outdegree(g, u, out);
         for(j = 0; j < n; ++j) {
            v = out[j];
            w = getEdgeValue(g, u, v);
            if ( distance[v] > distance[u] + w ) {    
               distance[v] = distance[u] + w;
               predecessor[v] = u;
            }
         }
      }

   for(u = 0; u < v_num; ++u) {
         n = outdegree(g, u, out);
         for(j = 0; j < n; ++j) {
            v = out[j];
            w = getEdgeValue(g, u, v);
            if ( distance[v] > distance[u] + w ) {    
               printf("Graph contains a negative-weight cycle.\n");
               *length = -1;
               return -1;
            }
         }
      }
   total = distance[t]; 
   if (total != INFINITIVE_VALUE)
   {
      tmp[0] = t;
      n = 1;              
      while (t != s)
      {
            t = predecessor[t];
            tmp[n++] = t;
      }
      for (i=n-1; i>=0; i--)
            path[n-i-1] = tmp[i];
      *length = n;                
   }
   free(distance);
   free(predecessor);
   return total;   
}
