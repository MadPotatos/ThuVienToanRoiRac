#include "prim.h"

Graph_prim createGraph_prim()
{
    Graph_prim g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}
void addVertex_prim(Graph_prim g, int id, char *name)
{
    JRB tmp = jrb_find_int(g.vertices, id);
    if (tmp == NULL)
    {
        jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
    }
    else
    {
        strcpy(tmp->val.s, name);
    }
}
char *getVertex_prim(Graph_prim g, int id)
{
    JRB tmp = jrb_find_int(g.vertices, id);
    return tmp->val.s;
}
void addEdge_prim(Graph_prim g, int v1, int v2, int dist)
{
    JRB tree = make_jrb();
    JRB tmp = jrb_find_int(g.edges, v1);
    if (tmp == NULL)
    {
        jrb_insert_int(g.edges, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(dist));
    }
    else
    {
        tmp = (JRB)tmp->val.v;
        JRB tmp1 = jrb_find_int(tmp, v2);
        if (tmp1 == NULL)
            jrb_insert_int(tmp, v2, new_jval_i(dist));
    }
}
int hasEdge_prim(Graph_prim g, int v1, int v2)
{
    JRB tmp = jrb_find_int(g.edges, v1);
    if (tmp == NULL)
    {
        return 0;
    }
    else
    {
        tmp = (JRB)tmp->val.v;
        JRB tmp1 = jrb_find_int(tmp, v2);
        if (tmp1 != NULL)
            return 1;
        return 0;
    }
}
int indegree_prim(Graph_prim g, int v, int *output)
{
    JRB tmp;
    JRB tmp1;
    JRB tmp2;
    int count = 0;
    int a;
    jrb_traverse(tmp, g.edges)
    {

        if (tmp->key.i != v)
        {
            a = tmp->key.i;
            tmp2 = (JRB)tmp->val.v;
            tmp1 = jrb_find_int(tmp2, v);
            if (tmp1 != NULL)
            {
                output[count++] = a;
            }
        }
    }
    return count;
}
int outdegree_prim(Graph_prim g, int v, int *output)
{
    JRB tmp = jrb_find_int(g.edges, v);
    int count = 0;
    JRB tmp1;
    if (tmp != NULL)
    {
        tmp = (JRB)tmp->val.v;
        jrb_traverse(tmp1, tmp)
        {
            output[count++] = tmp1->key.i;
        }
    }
    return count;
}
int getEdgeValue_prim(Graph_prim graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return 1000000;
    tree = (JRB)jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node == NULL)
        return 1000000;
    else
        return jval_i(node->val);
}
void dropGraph_prim(Graph_prim graph)
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

int prim(Graph_prim g, int s, int *edge)
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
        n = outdegree_prim(g, u, output);
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
            dll_append(queue, new_jval_i(min));
            xx[nn++] = min;
        }
        check[u] = 1;
    }
    k = 0;
    int x, y;
    jrb_traverse(tmp, g.vertices)
    {
        if (pre[tmp->key.i] != -1)
        {
            x = tmp->key.i;
            y = pre[tmp->key.i];
            edge[k++] = 10 * x + y;
        }
    }
    int MST = 0;
    printf("Edge MST:\n");
    for (int i = 0; i < k; i++)
    {
        x = edge[i] / 10;
        y = edge[i] % 10;
        //printf("%d -- %d \n",x,y);
        printf("%s%s ", getVertex_prim(g, x), getVertex_prim(g, y));
        MST = MST + getEdgeValue_prim(g, x, y);
    }

    printf("\nLength MST: %d\n", MST);
    return k;
}
void readfile_prim(Graph_prim g, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Errot file\n");
        exit(1);
    }
    int n, m;
    fscanf(fp, "%d %d\n", &n, &m);
    int v;
    char dinh[20];
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d %s\n", &v, dinh);
        //printf("%d %s\n", i, dinh);
        addVertex_prim(g, i, dinh);
    }
    int x, y;
    double z;
    for (int i = 0; i < m; i++)
    {
        fscanf(fp, "%d %d %lf", &x, &y, &z);
        addEdge_prim(g, x, y, z);
        addEdge_prim(g, y, x, z);
        //printf("%d %d %lf\n", x, y, z);
    }
    fclose(fp);
}
/*
int main()
{
    printf("Hello");
    Graph g2 = createGraph_prim();
    readfile_prim(g2, "DAG.txt");
    int edge1[10000];
    prim(g2, 1, edge1);
    return 0;
}
*/
