#include "coloring.h"

int matrix[10000][10000];
int visited[10000],check_pos[10000];
char color[15][15] = {"red", "green", "blue","yellow","orange","purple","gray","pink","brown", "white"};

void tomau(int *dinh, int *mau, int sodinh,int socanh)
{

    for(int i = 0; i < sodinh; i++)
    {
        int jk =0;
        int x = 0;
        int *mau_giong = (int *)calloc(15, sizeof(int));
        for(int j = 0; j < sodinh; j++)
        {
            //printf("%d \n",i);
            if(matrix[i][j] == 1 && j != i)
            {
                mau_giong[x++] = mau[j];
                //printf("%d \n",mau[j]);
            }
        }
        for(int k = 1; k <= 10; k++)
        {
            int y = 1;
            for(int l = 0; l < x; l++)
            {
                if(matrix[k][l]==-10000){
                    check_pos[k]==0;
                }else if(k == mau_giong[l])
                {
                    y = 0;
                    break;
                }
            }
            if(y == 1)
            {
                mau[i] = k;
                break;
            }
        }
    }
}
void xuatfile(int *dinh, int *mau,int sodinh, int socanh,char* filename)
{
    FILE *fp = fopen("dothitomau.dot", "wb");
    FILE *fp1 = fopen(filename, "r");
    int x,y;
    if(fp == NULL)
    {
        printf("Error file\n");
        exit(1);
    }
    fprintf(fp, "graph dothi{\n");
    for (int i = 0; i < sodinh; i++)
    {
        fprintf(fp, "%d [fillcolor=%s, style=filled];\n", i + 1, color[mau[i] - 1]);
    }
    fscanf(fp1, "%d %d\n", &x, &y);
    for (int i = 0; i < socanh; i++)
    {
        fscanf(fp1, "%d %d\n", &x, &y);
        fprintf(fp, "%d -- %d;\n", x, y);
    }
    fprintf(fp, "}\n");

    fclose(fp);
    fclose(fp1);
}
void coloring_graph(char *filename){
    int *dinh =(int *) malloc(sizeof(int)*10000);
    int *mau =(int *) malloc(sizeof(int)*10000);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error file!\n");
        exit(1);
    }
    int sodinh,socanh;
    fscanf(fp, "%d %d", &sodinh, &socanh);


    for (int i = 0; i < sodinh; i++)
    {
        for (int j = 0; j < sodinh; j++)
        {
            matrix[i][j] = 0;
        }
        mau[i] = 0;
    }
    int x, y;
    while (fscanf(fp, "%d %d", &x, &y) != EOF)
    {
        matrix[x - 1][y - 1] = 1;
        matrix[y - 1][x - 1] = 1;
    }
    int n = matrix[5][5];
    for (int i = 1; i < n; i++)
    {
        visited[i] = 0;
        check_pos[i] = i;
    }

    fclose(fp);
    tomau(dinh,mau,sodinh,socanh);
    xuatfile(dinh,mau,sodinh,socanh,filename);
    printf("Da xuat file tomaudothi.dot\n");
}

