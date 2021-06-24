#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"mst.h"
#include"graph.h"

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
  FILE *fp = fopen("mst.dot", "w");
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
  printf("\nDa xuat file mst.dot\n");
  fclose(fp);

}
int checking(Graph  g,int *edge,int n,int u,int v){
  int x ,y;
  for(int i=0;i<n;i++){
    x = edge[i]/10;
    y = edge[i]%10;
    if(x ==u&&y==v) return 1;
    if(x ==v&&y==u) return 1;
  }
  return 0;
}
int checking2(Graph  g,int *edge,int n,int u){
  int x ,y;
  for(int i=0;i<n;i++){
    x = edge[i]/10;
    y = edge[i]%10;
    if(x ==u||y==u) return 1;
  }
  return 0;
}
void graphiz_mst(Graph  g,int *edge,int nz){
  FILE *fp = fopen("mst.dot", "wb");
  fprintf(fp, "graph{\n");
  JRB tmp,tmp1;
  int visited[10000] = {};
  int dist,x,y, n, i, u, v, output[10000];
  jrb_traverse(tmp1, g.vertices)
  {
    u= tmp1->key.i;
    if(checking2(g,edge,nz,u)){
      fprintf(fp, "%s [fillcolor=red, style=filled, style = bold, color=red ,fontcolor=red];\n", getVertex(g,u) );
    }else 
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
                if(checking(g,edge,nz,u,v)){
                  fprintf(fp,"%s -- %s [weight = %d,label = %d, style = bold, color=red];\n",getVertex(g,x),getVertex(g,y),dist,dist);
                }else
                  fprintf(fp,"%s -- %s [weight = %d,label = %d];\n",getVertex(g,x),getVertex(g,y),dist,dist);

              
              }
              
            }
          
        }
      }
    }

  }

  fprintf(fp,"}");
  fclose(fp);
}
