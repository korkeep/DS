// Kruskal

#include <stdio.h>
#include <stdlib.h> 
#define MAX_VTX 256
#define INF 9999
#define MAX_HEAP_NODE 200

void error(char* str){
    printf("%s\n", str);
    exit(1);
}

typedef struct HeapNode{
    int key;
    int v1;
    int v2;
} HNode;
HNode heap[MAX_HEAP_NODE];
int heap_size;

#define Key(i) (i.key)          //i번째 노드
#define Parent(i) (heap[i/2])   //i의 부모 노드
#define Left(i) (heap[i*2])     //i의 왼쪽 자식 노드
#define Right(i) (heap[i*2+1])  //i의 오른쪽 자식 노드

void init_heap() {heap_size=0;}
int is_empty_heap() {return heap_size==0;}
int is_full_heap() {return (heap_size == MAX_HEAP_NODE-1);}
HNode root_heap() {return heap[1];}

void insert_heap(HNode n){
    int i;
    if(is_full_heap()) return;
    i = ++heap_size;
    // Min Heap
    while(i!=1 && Key(n) < Key(Parent(i))){
        heap[i] = Parent(i);
        i /= 2;
    }
    heap[i] = n;
}

HNode delete_heap(){
    HNode hroot, last;
    int parent = 1, child = 2;
    
    if(is_empty_heap()) error("힙 트리 공백 에러");

    hroot = heap[1];
    last = heap[heap_size--];
    while(child <= heap_size){
        // Min Heap
        if(child<heap_size && Key(Left(parent))>Key(Right(parent))){
            child++;                // 현재 노드의 자식 중 더 작은 자식을 찾기
        }
        if(Key(last) <= Key(heap[child])){
            break;                  // 마지막 노드가 더 작은 자식보다 작으면 이동 완료
        }
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = last;            // 마지막 노드를 최종 위치에 저장
    return hroot;
}


typedef char VtxData;       // 정점에 저장할 데이터의 자료형
int adj[MAX_VTX][MAX_VTX];  // 인접 행렬
int vsize;                  // 정점의 개수
VtxData vdata[MAX_VTX];     // 정점에 저장할 데이터
int parent[MAX_VTX];        // 각 노드의 부모 노드 인덱스
int set_size;               // 전체 집합의 개수

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

void init_set(int nSets){
    int i;
    set_size = nSets;
    for(i=0; i<nSets; i++)
        parent[i] = -1;
}

// Directed Graph
void insert_edge(int u, int v, int val){
    adj[u][v] = val;
}

// Undirected Graph
void insert_edge2(int u, int v, int val){
    adj[u][v] = adj[v][u] = val;
}

// 원소 x가 속한 집합을 반환하는 연산
int find_set(int id){
    while(parent[id] >= 0)
        id = parent[id];
    return id;
}

// 원소 x와 y가 속해있는 집합을 합집합으로 만드는 연산
void union_set(int s1, int s2){
    parent[s1] = s2;
    set_size--;
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

// Kruskal의 MST 연산 프로그램
void Kruskal(){
    int i, j, edgeAccepted=0, uset, vset;
    HNode e;

    init_heap();
    init_set(vsize);

    for(i=0; i<vsize-1; i++){
        for(j=i+1; j<vsize; j++){
            if(adj[i][j] < INF){
                e.key = adj[i][j];
                e.v1 = i;
                e.v2 = j;
                insert_heap(e);
            }
        }
    }
    while(edgeAccepted < vsize - 1){
        e = delete_heap();
        uset = find_set(e.v1);
        vset = find_set(e.v2);
        if(uset != vset){
            printf("간선 추가: %c - %c (비용: %d)\n", vdata[e.v1], vdata[e.v2], e.key);
            union_set(uset, vset);
            edgeAccepted++;
        }
    }
}

void main(){
    load_wgraph("wgraph.txt");
    printf("Kruskal 알고리즘을 이용한 MST 구하기\n");
    Kruskal();
}