#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include"graph.h"
#include "jrb.h"
#include "dllist.h"
Graph createGraph()
{
  Graph g;
  g.edges = make_jrb();
  g.vertices = make_jrb();
  return g;
}

void addVertex(Graph g, int id, char *name)
{
  JRB node = jrb_find_int(g.vertices, id);
  if (node == NULL) // only add new vertex
    jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}

char *getVertex(Graph g, int id)
{
  JRB node = jrb_find_int(g.vertices, id);
  if (node == NULL)
    return NULL;
  else
    return jval_s(node->val);
}

void addEdge(Graph graph, int v1, int v2, double weight)
{
  JRB node, tree;
  if (getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE)
  {
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
    {
      tree = make_jrb();
      jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    }
    else
    {
      tree = (JRB)jval_v(node->val);
    }
    jrb_insert_int(tree, v2, new_jval_d(weight));
  }
}
double getEdgeValue(Graph graph, int v1, int v2)
{
  JRB node, tree;
  node = jrb_find_int(graph.edges, v1);
  if (node == NULL)
    return INFINITIVE_VALUE;
  tree = (JRB)jval_v(node->val);
  node = jrb_find_int(tree, v2);
  if (node == NULL)
    return INFINITIVE_VALUE;
  else
    return jval_d(node->val);
}


int indegree(Graph graph, int v, int *output)
{
  JRB tree, node;
  int total = 0;
  jrb_traverse(node, graph.edges)
  {
    tree = (JRB)jval_v(node->val);
    if (jrb_find_int(tree, v))
    {
      output[total] = jval_i(node->key);
      total++;
    }
  }
  return total;
}

int outdegree(Graph graph, int v, int *output)
{
  JRB tree, node;
  int total;
  node = jrb_find_int(graph.edges, v);
  if (node == NULL)
    return 0;
  tree = (JRB)jval_v(node->val);
  total = 0;
  jrb_traverse(node, tree)
  {
    output[total] = jval_i(node->key);
    total++;
  }
  return total;
}

double shortestPath(Graph g, int s, int t, int *path, int *length)
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
int hasEdge(Graph graph, int v1, int v2)
{
  JRB node, tree;
  node = jrb_find_int(graph.edges, v1);
  if (node == NULL)
    return 0;
  else
  {
    tree = (JRB)jval_v(node->val);
    jrb_traverse(node, tree) if (v2 == jval_i(node->key)) return 1;
  }
  return 0;
}
int getAdjacentVertices(JRB graph, int v, int *output)
{
  JRB node, tree;
  int total;
  node = jrb_find_int(graph, v);
  if (node == NULL)
    return 0;
  else
  {
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree)
        output[total++] = jval_i(node->key);
    return total;
  }
}

void dropGraph(Graph graph)
{
  JRB node, tree;
  jrb_traverse(node, graph.edges)
  {
    tree = (JRB)jval_v(node->val);
    jrb_free_tree(tree);
  }
  jrb_free_tree(graph.edges);
  jrb_free_tree(graph.vertices);
}

//doc file
Graph readfile_gr(char *filename){
    Graph g =createGraph();
    FILE *fp =fopen(filename,"r");
    if(fp == NULL ){
        printf("Error file");
        exit(0);
    } 
    int i,m,n;
    fscanf(fp,"%d %d\n",&n,&m);
    int o;
    char p[20];
    for(i = 0;i<n;i++){
        fscanf(fp,"%d %s\n",&o,p);
        addVertex(g,o,p);
    }
    int x,y;
    double z;
    for(i=0;i<m;i++){
        fscanf(fp,"%d %d %lf",&x,&y,&z);
        addEdge(g,y,x,z);
    }
    fclose(fp);
    return g;
}
Graph readfile_g(char *filename){
    Graph g =createGraph();
    FILE *fp =fopen(filename,"r");
    if(fp == NULL ){
        printf("Error file");
        exit(0);
    } 
    int i,m,n;
    fscanf(fp,"%d %d\n",&n,&m);
    int o;
    char p[20];
    for(i = 0;i<n;i++){
        fscanf(fp,"%d %s\n",&o,p);
        addVertex(g,o,p);
        //addVertex(g,i," ");
    }
    int x,y;
    double z;
    for(i=0;i<m;i++){
        fscanf(fp,"%d %d %lf",&x,&y,&z);
        addEdge(g,x,y,z);
    }
    fclose(fp);
    return g;
}
Graph readfile(char *filename){
    Graph g =createGraph();
    FILE *fp =fopen(filename,"r");
    if(fp == NULL ){
        printf("Error file");
        exit(0);
    } 
    int i,m,n;
    int o;
    char p[20];
    fscanf(fp,"%d %d\n",&n,&m);
    for(i = 0;i<n;i++){
        fscanf(fp,"%d %s\n",&o,p);
        addVertex(g,o,p);
        //addVertex(g,i," ");
    }
    int x,y;
    double z;
    for(i=0;i<m;i++){
        fscanf(fp,"%d %d %lf",&x,&y,&z);
        addEdge(g,x,y,z);
        addEdge(g,y,x,z);
    }
    fclose(fp);
    return g;
}
// Do thi vo huong
void graphiz_vh(Graph g){
  FILE *fp = fopen("graph_vh.dot", "wb");
  fprintf(fp, "graph{\n");
  JRB tmp,tmp1;
  int visited[10000] = {};
  int dist,x,y, n, i, u, v, output[10000];
  jrb_traverse(tmp1, g.vertices)
  {
    u= tmp1->key.i;
    fprintf(fp, "%s [fillcolor=white, style=filled];\n", getVertex(g,u) );
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
              //fprintf(fp,"%d -- %d [];\n",u,v);
              if(u !=v){
                x =u;
                y =v;
                dist=(int)getEdgeValue(g,x,y);
                fprintf(fp,"%s -- %s [weight = %d] [label = %d];\n",getVertex(g,x),getVertex(g,y),dist,dist);
              }
              
            }
          
        }
      }
    }
  }
  fprintf(fp,"}");
  printf("\nDa xuat file graphiz_vh.dot\n");
  fclose(fp);
}
//Do thi co huong
void graphiz_ch(Graph g){
  FILE *fp = fopen("graph_ch.dot", "wb");
  fprintf(fp, "digraph{\n");
  JRB tmp,tmp1;
  int visited[10000] = {};
  int dist,x,y, n, i, u, v, output[10000];
  jrb_traverse(tmp1, g.vertices)
  {
    u= tmp1->key.i;
    fprintf(fp, "%s [fillcolor=white, style=filled];\n", getVertex(g,u) );
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
            //if(visited[u]==0||visited[v]==0)
              //fprintf(fp,"%d -- %d [];\n",u,v);
              if(u !=v){
                x =u;
                y =v;
                dist=(int)getEdgeValue(g,x,y);
                fprintf(fp,"%s -> %s [weight = %d] [label = %d];\n",getVertex(g,x),getVertex(g,y),dist,dist);
              }
              
            }
          
        }
      }
    }
  }
  fprintf(fp,"}");
  printf("\nDa xuat file graphiz_ch.dot\n");
  fclose(fp);
}



//lien thong
int lienthongdothivohuong(Graph graph)
{
    int visited[10000] = {};
    int n, output[10000], i, u, v;
    Dllist node, queue;
    JRB tmp;
    queue = new_dllist();
    int nlienthong=0;
    jrb_traverse(tmp,graph.vertices){
        u=tmp->key.i;
        if(!visited[u])
        {
            nlienthong++;
            dll_append(queue,new_jval_i(u));
            while(!dll_empty(queue))
            {
                node =dll_last(queue);
                v=jval_i(node->val);
                dll_delete_node(node);
                if(!visited[v]){
                    visited[v]=1;
                    n=outdegree(graph,v,output);
                    for(i=0;i<n;i++){
                        v=output[i];
                        if(!visited[v]) dll_append(queue,new_jval_i(v));
                    }
                    
                }
            }
        }
    }
    return nlienthong;
}
//c1
int min(int a, int b)
{
    return a < b ? a : b;
}
int low[10000];
int num[10000]; 
int cnt = -1;
int numSCC = 0;

void Tarjan(Graph graph, int vertex, Dllist stack)
{
    num[vertex] = cnt++;
    //printf("%d\n",num[vertex] );
    low[vertex] = cnt;
    Dllist node;
    int n, output[10000], i, u, v;
    dll_append(stack, new_jval_i(vertex));
    n = outdegree(graph, vertex, output);
    for (i = 0; i < n; i++)
    {
        v = output[i];
        if (num[v]==-1)
        {
            Tarjan(graph, v, stack);
            low[vertex] = min(low[vertex], low[v]);
        }
        else 
            low[vertex] = min(low[vertex], num[v]);
    }
    if (low[vertex] == num[vertex])
    {
        numSCC++;
        do{
            node = dll_last(stack);
            u = jval_i(node->val);
            dll_delete_node(node);
            low[u] = num[vertex];
        }while(u!=vertex);  
    }
}

int lienthongmanh(Graph g)
{
    memset(low, 0, sizeof(low));
    memset(num, -1, sizeof(num));
    Dllist stack;
    stack = new_dllist();
    JRB tmp;
    int  u;
    numSCC = 0;
    jrb_traverse(tmp, g.vertices)
    {   
        u = tmp->key.i;
        if (num[u]==-1)
        {
            Tarjan(g, u, stack);
        }
    }
    return numSCC;
}

void solienthongmanh(Graph g){
    
    printf("Tong so thanh phan lien thong manh : %d\n", lienthongmanh(g));
}







