#include <stdio.h>
#include <stdlib.h> 
#define MAX_VTX 256
#define MAX_QUEUE_SIZE 100

void error(char* str){
    printf("%s\n", str);
    exit(1);
}

typedef struct GraphNode{
    int id;                     // 정점의 id
    struct GraphNode* link;     // 다음 노드의 포인터
} GNode;

typedef char VtxData;           // 정점에 저장할 데이터의 자료형
GNode *adj[MAX_VTX];            // 정점의 인접 리스트
int vsize;                      // 정점의 개수
VtxData vdata[MAX_VTX];         // 정점에 저장할 데이터 배열
int visited[MAX_VTX];           // 정점의 방문 여부

int is_empty_graph() {return vsize==0;}
int is_full_graph() {return vsize>=MAX_VTX;}

void init_graph(){
    int i;
    vsize=0;
    for(i=0; i<MAX_VTX; i++)
        adj[i] = NULL;
}

void reset_graph(){
    int i;
    GNode *n;
    for(i=0; i<vsize; i++){
        while(adj[i] != NULL){
            n = adj[i];
            adj[i] = n->link;
            free(n);
        }
    }
    vsize = 0;
}

void insert_vertex(VtxData name){
    if(is_full_graph())
        error("Error: 그래프 정점의 개수 초과\n");
    else
        vdata[vsize++] = name;
}

void insert_edge(int u, int v){
    GNode *n = (GNode*)malloc(sizeof(GNode));
    n->link = adj[u];
    n->id = v;
    adj[u] = n;     // 노드의 삽입이 연결 리스트의 전단에서 이루어짐
}

void print_graph(char *msg){
    int i;
    GNode *v;
    printf("%s", msg);
    printf("%d\n", vsize);
    for(i=0; i<vsize; i++){
        printf("%c ", vdata[i]);
        for(v=adj[i]; v!=NULL; v=v->link){
            printf(" %c", vdata[v->id]);
        }
        printf("\n");
    }
}

void load_graph(char *filename){
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
                if(val != 0){
                    insert_edge(i, j);
                }
            }
        }
        fclose(fp);
    }
}

void reset_visited(){
    int i;
    for(i=0; i<vsize; i++)
        visited[i] = 0;
}

void DFS(int v){
    GNode *p;
    visited[v] = 1;
    printf("%c ", vdata[v]);
    for(p=adj[v]; p!=NULL; p=p->link)
        if(visited[p->id]==0)
            DFS(p->id);
}

typedef int Element;
Element data[MAX_QUEUE_SIZE];
int front;
int rear;

void init_queue(){
    front = rear = 0;
}

int is_empty(){
    return front == rear;
}

int is_full(){
    return front == (rear + 1) % MAX_QUEUE_SIZE;
}

int size(){
    return (rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

void enqueue(Element val){
    if(is_full()){
        error("큐 포화 에러");
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = val;
}

Element dequeue(){
    if(is_empty()){
        error("큐 공백 에러");
    }
    front = (front + 1) % MAX_QUEUE_SIZE;
    return data[front];
}

Element peek(){
    if(is_empty()){
        error("큐 공백 에러");
    }
    return data[front];
}

void BFS(int v){
    GNode *p;
    visited[v] = 1;

    printf("%c ", vdata[v]);
    init_queue();
    enqueue(v);
    while(!is_empty()){
        v = dequeue();
        for(p=adj[v]; p!=NULL; p=p->link){
            if(!visited[p->id]){
                visited[p->id] = 1;
                printf("%c ", vdata[p->id]);
                enqueue(p->id);
            }
        }
    }
}

void main(){
    // DFS
    // load_graph("graph2.txt");
    // reset_visited();
    // printf("DFS ==> ");
    // DFS(0);
    // printf("\n");

    // BFS
    load_graph("graph2.txt");
    reset_visited();
    printf("BFS ==> ");
    BFS(0);
    printf("\n");
}