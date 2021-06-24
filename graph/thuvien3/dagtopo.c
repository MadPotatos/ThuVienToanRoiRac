#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"dagtopo.h"
//DAG va Topologicalsort
#include"graph.h"
//DAG va topo
int DAG(Graph graph)
{
  int visited[1000];
  int n, output[100], i, u, v, start;
  Dllist node, stack;
  JRB tmp;

  jrb_traverse(tmp, graph.vertices)
  {
    memset(visited, 0, sizeof(visited));

    start = tmp->key.i;
    stack = new_dllist();
    dll_append(stack, new_jval_i(start));
    //printf("+%d\n",start);
    while (!dll_empty(stack))
    {
      node = dll_last(stack);
      u = jval_i(node->val);
      dll_delete_node(node);
      //printf("-%d\n");
      if (!visited[u])
      {
        visited[u] = 1;
        n = outdegree(graph, u, output);
        for (i = 0; i < n; i++)
        { 
          v = output[i];
          //printf("%d ",v);          
          if (v == start) 
            return 0;
          if (!visited[v])
            dll_append(stack, new_jval_i(v));
        }
        //printf("\n");
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
