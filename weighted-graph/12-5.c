// Floyd

#include <stdio.h>
#include <stdlib.h> 
#define MAX_VTX 256
#define INF 9999

void error(char* str){
    printf("%s\n", str);
    exit(1);
}

typedef char VtxData;       // 정점에 저장할 데이터의 자료형
int adj[MAX_VTX][MAX_VTX];  // 인접 행렬
int vsize;                  // 정점의 개수
VtxData vdata[MAX_VTX];     // 정점에 저장할 데이터
int spath[MAX_VTX][MAX_VTX];// 최단경로거리

int is_empty_graph() {return vsize==0;}
int is_full_graph() {return vsize>=MAX_VTX;}

void init_graph(){
    int i, j;
    vsize=0;
    for(i=0; i<MAX_VTX; i++)
        for(j=0; j<MAX_VTX; j++)
            adj[i][j] = 0;
}

void insert_vertex(VtxData name){
    if(is_full_graph())
        error("Error: 그래프 정점의 개수 초과\n");
    else
        vdata[vsize++] = name;
}

// Directed Graph
void insert_edge(int u, int v, int val){
    adj[u][v] = val;
}

// Undirected Graph
void insert_edge2(int u, int v, int val){
    adj[u][v] = adj[v][u] = val;
}

void load_wgraph(char *filename){
    int i, j, val, n;
    char str[80];
    FILE *fp = fopen(filename, "r");
    if(fp != NULL){
        init_graph();
        fscanf(fp, "%d", &n);
        for(i=0; i<n; i++){
            fscanf(fp, "%s", str);
            insert_vertex(str[0]);
            for(j=0; j<n; j++){
                fscanf(fp, "%d", &val);
                if(i != j && val == 0){
                    insert_edge(i, j, INF);
                }
                else{
                    insert_edge(i, j, val);
                }
            }
        }
        fclose(fp);
    }
}

void print_wgraph(char *msg){
    int i, j, val;
    printf("%s", msg);
    printf("%d\n", vsize);
    for(i=0; i<vsize; i++){
        printf("%c ", vdata[i]);
        for(j=0; j<vsize; j++){
            val = adj[i][j];
            if(i==j) printf("  0 ");
            else if(val>=INF) printf("  - ");
            else printf("%3d ", val);
        }
        printf("\n");
    }
}

void print_floyd(){
    int i, j;
    printf("====================================\n");
    for(i=0; i<vsize; i++){
        for(j=0; j<vsize; j++){
            if(spath[i][j]==INF) printf(" INF ");
            else printf("%4d ", spath[i][j]);
        }
        printf("\n");
    }
}

void Floyd(){
    int i, j, k;
    for(i=0; i<vsize; i++){
        for(j=0; j<vsize; j++){
            spath[i][j] = adj[i][j];
        }
    }

    for(k=0; k<vsize; k++){
        for(i=0; i<vsize; i++){
            for(j=0; j<vsize; j++){
                if(spath[i][j] > spath[i][k]+spath[k][j])
                    spath[i][j] = spath[i][k]+spath[k][j];
            }
        }
        print_floyd();
    }
}

void main(){
    load_wgraph("wgraph.txt");
    print_wgraph("최단거리(wgraph.txt)\n");

    printf("Floyd 알고리즘을 이용한 최단 거리 구하기\n");
    Floyd();
}