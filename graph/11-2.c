#include <stdio.h>
#include <stdlib.h> 
#define MAX_VTX 256

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
    adj[u] = n;
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

void main(){
    load_graph("graph.txt");
    print_graph("그래프(인접리스트)\n");
}