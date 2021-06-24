void docfile(Graph g, char *filename){
    FILE *fp = fopen(filename,"r");
    if(fp==NULL){
        printf("Errot file\n");
        exit(1);
    }
    int n,m;
    fscanf(fp,"%d %d\n",&n,&m);
    int v;
    char dinh[20];
    for(int i=0;i<n;i++){
        fscanf(fp,"%d %s\n",&v,dinh);
        printf("%d %d\n",i,dinh);
        addVertex(g,i,dinh);
    }
    int x,y;
    double z;
    for(int i=0;i<m;i++){
        fscanf(fp,"%d %d %lf",&x,&y,&z);
        addEdge(g,x,y,z);
        addEdge(g,y,x,z);
        printf("%d %d %lf\n",x,y,getEdgeValue(g,x,y));
    }
    fclose(fp);
}
