// Prim

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
int selected[MAX_VTX];      // 정점의 선택 여부
int dist[MAX_VTX];          // 정점까지의 거리

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

int getMinVertex(){
    int v, minv=0, mindist=INF;
    for(v=0; v<vsize; v++){
        if(!selected[v] && dist[v]<mindist){
            mindist = dist[v];
            minv = v;
        }
    }
    return minv;
}

// Prim의 MST 연산 프로그램
void Prim(){
    int i, u, v;
    for(i=0; i<vsize; i++){
        dist[i] = INF;
        selected[i] = 0;
    }
    dist[0] = 0;

    for(i=0; i<vsize; i++){
        // MST와의 거리가 최소인 정점 설정
        u = getMinVertex();
        selected[u] = 1;
        if(dist[u] == INF) return;
        printf("%c ", vdata[u]);
        // 인접 정점들에 대한 Dist 값 갱신
        for(v=0; v<vsize; v++){
            if(adj[u][v] != INF)
                if(!selected[v] && adj[u][v] < dist[v])
                    dist[v] = adj[u][v];
        }
    }
    printf("\n");
}

void main(){
    load_wgraph("wgraph.txt");
    printf("Prim 알고리즘을 이용한 MST 구하기\n");
    Prim();
}