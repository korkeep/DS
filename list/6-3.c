#include <stdio.h>
#include <stdlib.h>

typedef int Element;
typedef struct DLinkedNode{
    Element data;
    struct DLinkedNode *prev;
    struct DLinkedNode *next;
} Node;
Node org;       // 헤드 노드 (포인터가 아님)

void init_list(){
    org.next = NULL;
}

int is_empty(){
    return org.next == NULL;
}

Node *get_entry(int pos){
    Node *n = &org;
    int i = -1;     // 헤드부터 시작하기 때문
    for(i=-1; i<pos; i++){
        if(n==NULL) break;
        n = n->next;
    }
    return n;
}

int size(){
    Node *p;
    int count = 0;
    for(p=org.next; p!=NULL; p=p->next){
        count++;
    }
    return count;
}

Node *find(Element e){
    Node *p;
    for(p=org.next; p!=NULL; p=p->next){
        if(p->data == e){
            return p;
        }
    }
    return NULL;
}

void replace(int pos, Element e){
    Node *node = get_entry(pos);
    if(node != NULL){
        node->data = e;
    }
}

void insert(int pos, Element e){
    Node *new_node, *old_node;

    old_node = get_entry(pos-1);
    if(old_node != NULL){
        new_node = (Node*)malloc(sizeof(Node));
        // 새로운 노드의 Pointer 설정
        new_node->data = e;
        new_node->prev = old_node;
        new_node->next = old_node->next;
        // 새로운 노드 다음 노드의 Pointer 설정
        if(old_node->next != NULL){
            old_node->next->prev = new_node;
        }
        //새로운 노드 이전 노드의 Pointer 설정
        old_node->next = new_node;
    }
}

void delete(int pos){
    Node *old_node = get_entry(pos);
    // 삭제되는 노드 이전 노드의 Pointer 설정
    if(old_node->prev != NULL){
        old_node->prev->next = old_node->next;
    }
    // 삭제되는 노드 다음 노드의 Pointer 설정
    if(old_node->next != NULL){
        old_node->next->prev = old_node->prev;
    }
}

void clear_list(){
    while(is_empty() == 0){
        delete(0);
    }
}

void print_list(char *msg){
    Node *p;
    printf("%s[%2d]: ", msg, size());
    for(p=org.next; p!=NULL; p=p->next){
        printf("%2d ", p->data);
    }
    printf("\n");
}

void main(){
    init_list();
    insert(0, 10);
    insert(0, 20);
    insert(1, 30);
    insert(size(), 40);
    insert(2, 50);
    print_list("이중연결리스트로 구현한 List(삽입x5)");

    replace(2, 90);
    print_list("이중연결리스트로 구현한 List(교체x1)");

    delete(2);
    delete(size() - 1);
    delete(0);
    print_list("이중연결리스트로 구현한 List(삭제x3)");

    clear_list();
    print_list("이중연결리스트로 구현한 List(정리후)");
}