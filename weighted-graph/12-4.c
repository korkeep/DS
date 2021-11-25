// Dijkstra

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
int dist[MAX_VTX];          // 정점까지의 거리
int path[MAX_VTX];          // 경유하는 정점
int found[MAX_VTX];         // 방문한 정점

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

// 진행 단계별 출력
void print_step(int step){
    int i;
    printf(" Step%2d:", step);
    for(i=0; i<vsize; i++){
        if(dist[i] == INF) printf("  INF");
        else printf("%5d", dist[i]);
    }
    printf("\n");
}

// 최종 경로 출력
void print_shortest_path(int start, int end){
    printf("[최단경로: %c---%c] %c", vdata[end], vdata[start], vdata[end]);
    while(path[end] != start){
        printf("-%c", vdata[path[end]]);
        end = path[end];
    }
    printf("-%c\n", vdata[path[end]]);
}

int choose_vertex(){
    int i, min=INF, minpos=-1;
    for(i=0; i<vsize; i++){
        if(dist[i]<min && !found[i]){
            min = dist[i];
            minpos = i;
        }
    }
    return minpos;
}

// Dijkstra의 최단경로
void Dijkstra(int start){
    int i, u, w;
    for(i=0; i<vsize; i++){
        dist[i] = adj[start][i];
        path[i] = start;
        found[i] = 0;
    }
    found[start] = 1;
    dist[start] = 0;

    for(i=0; i<vsize; i++){
        print_step(i+1);
        u = choose_vertex();
        found[u] = 1;

        for(w=0; w<vsize; w++){
            if(found[w] == 0){
                if(dist[u]+adj[u][w] < dist[w]){
                    dist[w] = dist[u]+adj[u][w];
                    path[w] = u;
                }
            }
        }
    }
}

void main(){
    int i;

    load_wgraph("wgraph.txt");
    printf("Dijkstra 알고리즘을 이용한 최소 거리 구하기\n");
    Dijkstra(0);

    for(i=1; i<vsize; i++)
        print_shortest_path(0, i);
}