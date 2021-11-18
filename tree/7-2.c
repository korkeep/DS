#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef char TElement;
typedef struct BinTreeNode{
    TElement data;
    struct BinTreeNode* left;
    struct BinTreeNode* right;
} TNode;
TNode *root;
typedef TNode *Element;

Element data[MAX_QUEUE_SIZE];
int front;
int rear;

void error(char* str){
    printf("%s\n", str);
    exit(1);
}

void init_queue(){
    front = rear = 0;
}

int is_full(){
    return front == (rear + 1) % MAX_QUEUE_SIZE;
}

int is_empty(){
    return front == rear;
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

void init_tree() {root = NULL;}
int is_empty_tree() {return root == NULL;}
TNode *get_root() {return root;}

TNode *create_tree(TElement val, TNode *l, TNode *r){
    TNode *n = (TNode*)malloc(sizeof(TNode));
    n->data = val;
    n->left = l;
    n->right = r;
    return n;
}

void preorder(TNode *n){
    if(n != NULL){
        printf("[%c] ", n->data);
        preorder(n->left);
        preorder(n->right);
    }
}

void inorder(TNode *n){
    if(n != NULL){
        inorder(n->left);
        printf("[%c] ", n->data);
        inorder(n->right);
    }
}

void postorder(TNode *n){
    if(n != NULL){
        postorder(n->left);
        postorder(n->right);
        printf("[%c] ", n->data);
    }
}

void levelorder(TNode *root){
    TNode *n;
    if(root == NULL) return;
    init_queue();
    enqueue(root);
    while(!is_empty()){
        n = dequeue();
        if(n!=NULL){
            printf("[%c] ", n->data);
            enqueue(n->left);
            enqueue(n->right);
        }
    }
}

int eveluate(TNode *n){
    int op1, op2;
    if(n==NULL) return 0;
    if(n->left == NULL && n->right == NULL) return n->data;
    else{
        op1 = eveluate(n->left);
        op2 = eveluate(n->right);
        switch(n->data){
            case '+': return op1 + op2;
            case '-': return op1 - op2;
            case '/': return op1 / op2;
            case '*': return op1 * op2;
        }
        return 0;
    }
}

void main(){
    TNode *n1, *n2, *n3, *n4, *n5, *n6;

    n1 = create_tree(3, NULL, NULL);
    n2 = create_tree(2, NULL, NULL);
    n3 = create_tree('*', n1, n2);
    n4 = create_tree(5, NULL, NULL);
    n5 = create_tree(6, NULL, NULL);
    n6 = create_tree('-', n4, n4);
    root = create_tree('+', n3, n6);
    printf(" 계산 결과 = %d\n", eveluate(root));

}