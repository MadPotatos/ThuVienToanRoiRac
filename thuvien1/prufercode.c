#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"prufercode.h"

//prufer
void pruffercode(){
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
    printf("\n");
  

}


//fathercode
int matrix[MAX_VALUE][MAX_VALUE];
int matrix1[MAX_VALUE][MAX_VALUE];
int check;
int count_edges(int v1)
{
    int count = 0;
    for(int i= 0;i<check;++i)
        if(matrix[v1][i]==1) count++;
}
int return_edges(int v1)
{
    for(int i=0;i<check;++i)
        if(matrix[v1][i]==1) return i;
}
void addadges(int v1,int v2)
{
    if(check<v1) check = v1;
    if(check<v2) check = v2;
    matrix[v1][v2]=1;
    matrix[v2][v1]=1;
    matrix1[v1][v2]=1;
    matrix1[v2][v1]=1;
}
void drop_edges(int v1,int v2)
{
    matrix[v1][v2]=0;
    matrix[v2][v1]=0;
}

int visited[MAX_VALUE];
int check1[MAX_VALUE];
void father_vertice(int v1,int father)
{
    visited[father]=1;
    if(matrix1[father][v1]==1) {check1[v1]=father; return;}
    for(int i = 0;i<=check;++i)
        if(matrix1[father][i]==1&&visited[i]!=1)  father_vertice(v1,i);
}
void reset_visited()
{
    for(int i =0;i<MAX_VALUE;++i)
        visited[i]=0;
}
int fathercode(){
     for(int i=0;i<MAX_VALUE;++i)
        for(int j=0;j<MAX_VALUE;++j)
            {
                matrix[i][j]=0;
                matrix1[i][j]=0;
            }
    FILE *fp=fopen("prufer.txt","r");
    if(fp ==NULL){
        printf("Error file.\n");
        exit(0);
    }
    int n;
    fscanf(fp,"%d",&n);
    int x,y;
    for(int i=0;i<n;i++){
        fscanf(fp,"%d %d",&x,&y);
        addadges(x,y);
    }
    for(int i =1;i<=check;++i)
    {
        father_vertice(i,0);
        printf("%d ",check1[i]);
        reset_visited();
    }
    printf("\n");
}