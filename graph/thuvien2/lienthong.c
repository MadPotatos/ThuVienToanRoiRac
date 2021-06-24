#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"lienthong.h"
#include"graph.h"
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


