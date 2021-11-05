#include <stdio.h>
#include <stdlib.h>

typedef int Element;
typedef struct LinkedNode{
    Element data;               // 데이터 영역
    struct LinkedNode* link;    // 다음 노드를 가리키는 포인터
} Node;
Node *top = NULL;               // 연결 리스트의 헤드 포인터

void error(char *str){
    fprintf(stderr, "%s\n", str);
    exit(1);
}

int is_empty(){
    return top == NULL;
}

void init_stack(){
    top = NULL;
}

int size(){
    Node *p;
    int count = 0;
    for(p=top; p!=NULL; p=p->link){
        count++;
    }
    return count;
}

void push(Element e){
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = e;        //data를 e로 초기화
    p->link = top;      //stack이므로 제일 앞에 추가
    top = p;            //top을 p로 변경해줌
}

Element pop(){
    Node *p;
    Element e;
    if(is_empty()){
        error("스택 공백 에러");
    }
    p = top;            //현재 top 내용을 복사해옴
    top = p->link;      //top의 다음 이어지는 내용을 top으로 설정
    e = p->data;        //현재 top 내용의 data를 e로 가져옴
    free(p);            //p로 복사된 내용을 할당 해제
    return e;
}

Element peek(){
    if(is_empty()){
        error("스택 공백 에러");
    }
    return top->data;
}

void destroy_stack(){
    while(is_empty() == 0){
        pop();
    }
}

void print_stack(char *msg){
    Node *p;
    printf("%s[%2d]= ", msg, size());
    for(p=top; p!=NULL; p=p->link){
        printf("%2d ", p->data);
    }
    printf("\n");
}

void main(){
    int i;
    init_stack();
    
    for(i=1; i<10; i++)
        push(i);
    print_stack("연결된 스택 push 9회");
    
    printf("\t pop() --> %d\n", pop());
    printf("\t pop() --> %d\n", pop());
    printf("\t pop() --> %d\n", pop());
    print_stack("연결된 스택 pop 3회");
    
    destroy_stack();
    print_stack("연결된 스택 destroy");
}