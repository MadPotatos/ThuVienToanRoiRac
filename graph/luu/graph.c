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
void graphiz_dijkstra(Graph g, int *path, int n ){
  FILE *fp =fopen("dijstra.dot","wb");
  if(fp == NULL) printf("Error\n");
  fprintf(fp, "graph{\n");
  JRB tmp;
  int dist,u, v, i, output[10000];
  int visited[10000]={};
  jrb_traverse(tmp,g.vertices){
    u = tmp->key.i;
    fprintf(fp, "%s [fillcolor=white, style=filled];\n",getVertex(g,u));
  }
  int x,y;
  for(int i = 0; i<n-1;i++){
      x= path[i];
      y= path[i+1];
      dist=(int)getEdgeValue(g,x,y);
      fprintf(fp,"%s --> %s [weight = %d] [label = %d];\n",getVertex(g,x),getVertex(g,y),dist,dist);
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
    
    w = dijkstra(g, s, t, path, &length);
    if (w == INFINITIVE_VALUE)
    {
         printf("Khong co duong di tu %s den %s\n", getVertex(g, s), getVertex(g, t));
    }else
    {
         printf("Duong di %s den %s || Het %dm\n", getVertex(g, s), getVertex(g, t), w);
         for (i=0; i<length-1; i++)
             printf(" => %s", getVertex(g, path[i]));
             //printf(" => %s %s", getVertex(g, path[i]),getVertex(g, path[i+1]));
          graphiz_dijkstra(g,path,length);
    }

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
//lien thong manh
int low[10000];
int num[10000]; 
int cnt = -1;
int numSCC = 0; 
int MIN(int a, int b)
{
    return a < b ? a : b;
}
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
            low[vertex] = MIN(low[vertex], low[v]);
        }
        else 
            low[vertex] = MIN(low[vertex], num[v]);
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



//tim cay bao trum nho nhat
//krukal
//disjoint sets:
//int markset(int x);
//int find(int x);
//int unionz(int x, int y);
int find(int x,int *cha){
  // cach 1
  /*
  while(x!=cha[x]){
    x=cha[x];
  }
  return x;
  */
  // cach 2
  if(x!=cha[x])
    cha[x]=find(cha[x],cha);
  return cha[x];
}
void unionz(int x, int y,int *rank,int *cha){
  x=find(x,cha);
  y=find(y,cha);
  if(x==y) return;
  if(rank[x]==rank[y]) rank[x]++;
  if(rank[x]<rank[y]) cha[x]=y;
  else cha[y]=x;
}

int Kruskal(Graph graph, int *out){
  //markset
  // sap xep theo trong so
  JRB tmp,tmp1;
  int i,visit[10000];
  for( i=0;i<10000;i++){
    visit[i]=0;
  }
  int h,j,k,n,u,v,output[10000];
  int min=10000;
  n=0;
  jrb_traverse(tmp,graph.vertices){
    n++;
  }
  int dist[100000][3]={};
  int z=0;
   Dllist queue, node;
  queue = new_dllist();
  jrb_traverse(tmp, graph.vertices)
  {
    u = tmp->key.i;
    if (!visit[u])
    {
      dll_append(queue, new_jval_i(u));
      while (!dll_empty(queue))
      {
        node = dll_first(queue);
        h = jval_i(node->val);
        dll_delete_node(node);
        if (!visit[h])
        {
          visit[h] = 1;
          k = outdegree(graph, h, output);
          for (i = 0; i < k; i++)
          {
            v = output[i];
            //if (!visit[v])
             //visit[v]=1;
              dll_append(queue, new_jval_i(v));
              if(visit[h]==0||visit[v]==0){
                dist[z][0]=h;
                dist[z][1]=v;
                dist[z][2]=(int)getEdgeValue(graph,h,v);
                z++;
              }
              
          }
        }
      }
    }
  }
  int x,y;
  int kc[20000],value;
  for(i=0;i<z;i++){
    kc[i]=i;
  }
  for(i =0;i<z;i++){
    for(j= i+1;j<z;j++){
      if(dist[i][2]>dist[j][2]){
        value=dist[i][2];
        dist[i][2]=dist[j][2];
        dist[j][2]=value;
        value=kc[i];
        kc[i]=kc[j];
        kc[j]=value;
      }
    }
  }
  // tim cay bao trum nho nhat
  int rank[20000],cha[20000];
  for(int i=0;i<20000;i++){
    cha[i]=i;
    rank[i]=0;
  }
  int kk=0;
  int rx,ry;
  for( i = 0;i<z;i++){
    x=dist[kc[i]][0];
    y=dist[kc[i]][1];
    rx=find(x,cha);
    ry=find(y,cha);
    if(rx!=ry){
      out[kk++]=x*10+y;
      unionz(x,y,rank,cha);
    }
  }
  double MST=0;
    printf("Edge MST:\n");
    for(int i = 0;i <kk;i++){
      
        x=out[i]/10;
        y=out[i]%10;
        printf("%s%s ",getVertex(graph,x),getVertex(graph,y));
        MST = MST + getEdgeValue(graph,x,y);
    }
    printf("\nLength MST: %d\n",(int)MST);
    graphiz_kru(graph,out,kk);
  return kk;
}
void graphiz_kru(Graph g,int *edge,int n){
  FILE *fp = fopen("kruskal.dot", "w");
  if (fp == NULL)
  {
    printf("Error");
    exit(0);
  }
  fprintf(fp, "graph dothi{\n");
  JRB tmp;
  int u;
  jrb_traverse(tmp, g.vertices)
  {
    u=tmp->key.i;
    fprintf(fp, "%s [fillcolor=white, style=filled];\n",getVertex(g,u));
  }
  int x,y,dist;
  for(int i=0;i<n;i++){
        x=edge[i]/10;
        y=edge[i]%10;
        dist =(int)getEdgeValue(g,x,y);
        fprintf(fp, "%s -- %s [weight = %d] [label = %d];\n",getVertex(g,x),getVertex(g,y),dist,dist);
  }
  fprintf(fp, "}");
  fclose(fp);

}

int prim(Graph g, int s, int *edge)
{
    
    Dllist queue, node;
    queue = new_dllist();
    dll_append(queue, new_jval_i(s));
    int dist[10000], pre[10000], check[10000];
    for (int i = 0; i < 10000; i++)
    {
        dist[i] = 10000;
        pre[i] = -1;
    }
    dist[s] = 0;
    int u, v, n, k, min, nn;
    int output[10000], xx[10000];
    JRB tmp, tmp1, tmp2, tmp4;
    nn = 0;
    xx[nn++] = s;
    while (!dll_empty(queue))
    {
        node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);
        n = outdegree(g, u, output);
        tmp = jrb_find_int(g.edges, u);
        if (check[u] == 0)
        {
            for (int i = 0; i < n; i++)
            {
                tmp1 = (JRB)tmp->val.v;
                tmp2 = jrb_find_int(tmp1, output[i]);
                if (dist[output[i]] == 10000)
                {
                    dist[output[i]] = tmp2->val.i;
                    pre[output[i]] = u;
                }
                else if (tmp2->val.i < dist[output[i]])
                {
                    int check = 1;
                    for (int j = 0; j < nn; j++)
                    {
                        if (output[i] == xx[j])
                        {
                            check = 0;
                            break;
                        }
                    }
                    if (check == 1)
                    {
                        dist[output[i]] = tmp2->val.i;
                        pre[output[i]] = u;
                    }
                }
            }
            int zz = 0;
            jrb_traverse(tmp4, g.vertices)
            {
                int check = 1;
                for (int i = 0; i < nn; i++)
                {
                    if (tmp4->key.i == xx[i])
                    {
                        check = 0;
                        break;
                    }
                }
                if (check == 1)
                {
                    if (zz == 0)
                    {
                        min = tmp4->key.i;
                        zz++;
                    }
                    else
                    {
                        if (dist[min] > dist[tmp4->key.i])
                            min = tmp4->key.i;
                    }
                }
            }
            dll_append(queue,new_jval_i(min));
            xx[nn++] = min;
         }
         check[u] = 1;
    }
    k = 0;
    int x,y;
    jrb_traverse(tmp, g.vertices)
    {
        if(pre[tmp->key.i] != -1)
        {
            x = tmp->key.i;
            y = pre[tmp->key.i];
            edge[k++]=10*x+y;
        }
    }
    double MST=0;
    printf("Edge MST:\n");
    for(int i = 0;i <k;i++){
      
        x=edge[i]/10;
        y=edge[i]%10;
        printf("%s%s ",getVertex(g,x),getVertex(g,y));
        MST = MST + getEdgeValue(g,x,y);
    }
    printf("\nLength MST: %d\n",(int)MST);
    return k;

}

//DAG va topo
int DAG(Graph graph)
{
  int visited[1000];
  int n, output[100], i, u, v, start;
  Dllist node, stack;
  JRB vertex;

  jrb_traverse(vertex, graph.vertices)
  {
    memset(visited, 0, sizeof(visited));

    start = jval_i(vertex->key);
    stack = new_dllist();
    dll_append(stack, new_jval_i(start));

    while (!dll_empty(stack))
    {
      node = dll_last(stack);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u])
      {
        visited[u] = 1;
        n = outdegree(graph, u, output);
        for (i = 0; i < n; i++)
        {
          v = output[i];
          if (v == start) // cycle detected
            return 0;
          if (!visited[v])
            dll_append(stack, new_jval_i(v));
        }
      }
    }
  }
  return 1; // no cycle
}

int topologicalsort(Graph g, int *output)
{
  int u, v, k, n, i;
  int degree[10000] = {};
  int out[10000];
  n = 0;
  Dllist queue, node;
  queue = new_dllist();
  JRB tmp;
  jrb_traverse(tmp, g.vertices)
  {
    u = tmp->key.i;
    degree[u] = indegree(g, u, out);
    if (degree[u] == 0)
      dll_append(queue, new_jval_i(u));
  }
  while(!dll_empty(queue)){
    node=dll_first(queue);
    u=jval_i(node->val);
    dll_delete_node(node);
    output[n++]=u;
    k=outdegree(g,u,out);
    for(i = 0;i<k;i++){
      v=out[i];
      degree[v]--;
      if(degree[v]==0)
        dll_append(queue,new_jval_i(v));
    }
  }
  return n;
}

//prufer
void pruffercode(Graph g){
    FILE *fp = fopen("prufer.txt","r");
    if(fp==NULL){
       printf("error file\n");
        exit(1); 
    }
    int n;
    fscanf(fp,"%d", &n);
    int **matrix = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i < n + 1; i++)
    {
        matrix[i] = (int *)calloc(2, sizeof(int));
    }
    int a, b;
    for (int i = 0; i < n; i++)
    {
        fscanf(fp,"%d %d", &matrix[i][0], &matrix[i][1]);
    }
    
    int *deg = (int *)calloc(sizeof(int),(n+5));
    int *check = (int *)calloc(sizeof(int),(n+5));
    for (int i = 0; i < n; i++)
    {
        deg[matrix[i][0]]++;
        deg[matrix[i][1]]++;
    }
    int min, v, i, j;
    for (i = 0; i < n - 1; i++)
    {
        min = 1000000;
        for (j = 0; j < n; j++)
        {
            if (check[j]) continue;
            if (deg[matrix[j][0]] == 1 && matrix[j][0] != 0)
            {
                if (min > matrix[j][0])
                {
                    min = matrix[j][0];
                    v = j;
                }
            }
            if (deg[matrix[j][1]] == 1 && matrix[j][1] != 0)
            {
                if (min > matrix[j][1])
                {
                    min = matrix[j][1];
                    v = j;
                }
            }
        }
        check[v] = 1;
        deg[matrix[v][0]]--;
        deg[matrix[v][1]]--;
        if (deg[matrix[v][0]] == 0)
            printf("%d ", matrix[v][1]);
        else
            printf("%d ", matrix[v][0]);
        }

  

}



