#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student{
    int id;         // 학번
    char name[32];  // 이름
    char dept[32];  // 소속학과
} Student;

typedef Student Element;
typedef struct LinkedNode{
    Element data;               // 데이터 영역
    struct LinkedNode* link;    // 다음 노드를 가리키는 포인터
} Node;
Node *front = NULL;             // 연결 리스트의 front 포인터
Node *rear = NULL;              // 연결 리스트의 rear 포인터

void error(char *str){
    fprintf(stderr, "%s\n", str);
    exit(1);
}

int is_empty(){
    return front == NULL;
}

void init_queue(){
    front = rear = NULL;
}

int size(){
    Node *p;
    int count = 0;
    for(p=front; p!=NULL; p=p->link){
        count++;
    }
    return count;
}

void enqueue(Element e){
    Node *p = (Node*)malloc(sizeof(Node));  // Node 동적 할당
    p->data = e;            // 데이터 필드 초기화
    p->link = NULL;         // 링크 필드 초기화
    if(is_empty()){
        front = rear = p;   // 공백인 경우 삽입 연산
    }
    else{
        rear->link = p;     // 공백이 아닌 경우 뒷단에서 새 항목 추가
        rear = p;           // 마지막 항목을 rear로 가리키기
    }
}

Element dequeue(){
    Node *p;
    Element e;
    if(is_empty()){
        error("큐 공백 에러");
    }
    p = front;              // 현재 가장 앞단에 있는 항목 복사
    front = front->link;    // 두 번째 항목을 front로 가리키기
    if(front==NULL){
        rear = NULL;        // 삭제하고 보니 마지막 항목이었던 경우 front, rear 둘 다 NULL로 초기화
    }
    e = p->data;            // p의 항목 복사
    free(p);                // p를 동적 해제
    return e;
}

Element peek(){
    if(is_empty()){
        error("큐 공백 에러");
    }
    return front->data;
}

void destroy_queue(){
    while(is_empty() == 0){
        dequeue();
    }
}

void print_queue(char *msg){
    Node *p;
    printf("%s[%2d]= ", msg, size());
    for(p=front; p!=NULL; p=p->link){
        printf("\n\t%-15d %-10s %-20s", p->data.id, p->data.name, p->data.dept);
    }
    printf("\n");
}

Student get_student(int id, char *name, char *dept){
    Student s;
    s.id = id;
    strcpy(s.name, name);
    strcpy(s.dept, dept);
    return s;
}

void main(){
    init_queue();
    enqueue(get_student(2016123123, "영희", "컴퓨터공학과"));
    enqueue(get_student(2016123124, "철수", "시각디자인과"));
    enqueue(get_student(2016123125, "바둑이", "글로벌애완학부"));
    enqueue(get_student(2016123126, "꼴뚜기", "해양과학생물학부"));
    print_queue("연결된 학생 큐(4명 삽입)");
    dequeue();
    print_queue("연결된 학생 큐(1명 삭제)");
    destroy_queue();
}