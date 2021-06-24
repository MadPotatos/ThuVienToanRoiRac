#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"prim.h"

int main(){
    printf("Hello");
    Graph_prim g2 = createGraph_prim();
    readfile_prim(g2, "DAG.txt");
    int edge1[10000];
    prim(g2, 1, edge1);
    return 0;
}