#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int TElement;
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
        printf("[%d] ", n->data);
        preorder(n->left);
        preorder(n->right);
    }
}

void inorder(TNode *n){
    if(n != NULL){
        inorder(n->left);
        printf("[%d] ", n->data);
        inorder(n->right);
    }
}

void postorder(TNode *n){
    if(n != NULL){
        postorder(n->left);
        postorder(n->right);
        printf("[%d] ", n->data);
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
            printf("[%d] ", n->data);
            enqueue(n->left);
            enqueue(n->right);
        }
    }
}

int count_node(TNode *n){
    if(n == NULL) return 0;
    return 1 + count_node(n->left) + count_node(n->right);
}

int count_leaf(TNode *n){
    if(n==NULL) return 0;
    if(n->left == NULL && n->right == NULL) return 1;
    else return count_leaf(n->left) + count_leaf(n->right);
}

int count_height(TNode *n){
    int hLeft, hRight;
    if(n == NULL) return 0;
    hLeft = count_height(n->left);
    hRight = count_height(n->right);
    return (hLeft > hRight) ? hLeft+1 : hRight + 1;
}

// Binary Search Tree 탐색
TNode *search (TNode *n, int key){
    if(n==NULL) return NULL;
    if(key==n->data) return n;
    if(key<n->data) return search(n->left, key);
    return search(n->right, key);
}

void search_BST(int key){
    TNode *n = search(root, key);
    if(n!=NULL)
        printf("[탐색 연산]: [%d] = 0x%x\n", n->data, n);
    else
        printf("[탐색 연산]: No %d\n", key);
}

// Binary Search Tree 삽입
int insert(TNode *r, TNode *n){
    if(n->data == r->data) return 0;
    if(n->data < r->data){
        if(r->left == NULL) r->left = n;
        else insert(r->left, n);
    }
    else{
        if(r->right == NULL) r->right = n;
        else insert(r->right, n);
    }
    return 1;
}

void insert_BST(int key){
    TNode *n = create_tree(key, NULL, NULL);
    if(is_empty_tree())
        root = n;
    else if(insert(root, n) == 0)
        free(n);
}

// Binary Search Tree 삭제
void delete(TNode *parent, TNode *node){
    TNode *child, *succ, *succp;
    // Case1: 단말 노드의 삭제
    if(node->left==NULL && node->right==NULL){
        if(parent==NULL) root = NULL;
        else{
            if(parent->left == node) parent->left = NULL;
            else parent->right = NULL;
        }
    }
    // Case2: 자식이 하나인 노드의 삭제
    else if(node->left==NULL || node->right==NULL){
        child = (node->left != NULL) ? node->left : node->right;
        if(node == root) root = child;
        else{
            if(parent->left == node) parent->left = child;
            else parent->right = child;
        }
    }
    // Case3: 자식이 두개인 노드의 삭제
    else{
        // 오른쪽 서브트리의 가장 작은 노드
        succp = node;
        succ = node->right;
        while(succ->left != NULL){
            succp = succ;
            succ = succ->left;
        }
        // succ가 succp의 왼쪽 자식인 경우 succp의 왼쪽에 succ의 오른쪽 자식 연결
        if(succp->left == succ){
            succp->left = succ->right;
        }
        // succ가 succp의 오른쪽 자식인 경우 succp의 오른쪽에 succ의 오른쪽 자식 연결
        else{
            succp->right = succ->right;
        }
        // succ를 node로 복사하여 succ를 삭제
        node->data = succ->data;
        node = succ;
        free(node);
    }
}

void delete_BST(int key){
    TNode *parent = NULL;
    TNode *node = root;

    if (node == NULL) return;
    while(node != NULL && node->data != key){
        parent = node;
        node = (key < node->data) ? node->left : node->right;
    }
    if(node == NULL){
        printf("Error: key is not in the tree!\n");
    }
    else{
        delete(parent, node);
    }
}

void main(){
    // 삽입 연산 테스트
    printf("[삽입 연산]: 35, 18, 7, 26, 12, 3, 68, 22, 30, 99");
    init_tree();
    insert_BST(35); insert_BST(18); insert_BST(7); insert_BST(26); insert_BST(12);
    insert_BST(3); insert_BST(68); insert_BST(22); insert_BST(30); insert_BST(99);

    // 트리 정보 출력
    printf("\n   In-Order: "); inorder(root);
    printf("\n  Pre-Order: "); preorder(root);
    printf("\n Post-Order: "); postorder(root);
    printf("\nLevel-Order: "); levelorder(root);
    printf("\n");

    printf(" 노드의 개수: %d\n", count_node(root));
    printf(" 단말의 개수: %d\n", count_leaf(root));
    printf(" 트리의 높이: %d\n", count_height(root));


    // 탐색 연산 테스트
    search_BST(26);
    search_BST(25);

    // 삭제 연산 테스트
    printf("\noriginal bintree: LevelOrder: "); levelorder(root);
    delete_BST(3);
    printf("\ncase1: < 3> 삭제: LevelOrder: "); levelorder(root);
    delete_BST(68);
    printf("\ncase2: <68> 삭제: LevelOrder: "); levelorder(root);
    delete_BST(18);
    printf("\ncase3: <18> 삭제: LevelOrder: "); levelorder(root);
    delete_BST(35);
    printf("\ncase3: <35> root: LevelOrder: "); levelorder(root);
    printf("\n");

    printf(" 노드의 개수: %d\n", count_node(root));
    printf(" 단말의 개수: %d\n", count_leaf(root));
    printf(" 트리의 높이: %d\n", count_height(root));    
}