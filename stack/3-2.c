#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STACK_SIZE 100

typedef struct Student{
    int id;
    char name[32];
    char dept[32]; 
} Student;
typedef Student Element;
Element data[MAX_STACK_SIZE];
int top;

void error(char str[]){
    printf("%s\n", str);
    exit(1);
}

void init_stack(){
    top = -1;
}

bool is_empty(){
    return top == -1;
}

bool is_full(){
    return top == MAX_STACK_SIZE - 1;
}

int size(){
    return top + 1;
}

void push(Element e){
    if(is_full()){
        error("스택 포화 에러");
    }
    data[++top] = e;
}

Element pop(){
    if(is_empty()){
        error("스택 공백 에러");
    }
    return data[top--];
}

Element peek(){
    if(is_empty()){
        error("스택 공백 에러");
    }
    return data[top];
}

void print_stack(char msg[]){
    int i;
    printf("%s = ", msg);
    for(i=0; i<size(); i++){
        printf("\n\t%-15d %-10s %-20s", data[i].id, data[i].name, data[i].dept);
    }
    printf("\n");
}

Student get_student(int id, char name[], char dept[]){
    Student s;
    s.id = id;
    strcpy(s.name, name);
    strcpy(s.dept, dept);
    return s;
}

void main(){
    int i;
    init_stack();
    
    push(get_student(2016123123, "영희", "컴퓨터공학과"));
    push(get_student(2016123124, "철수", "시각디자인과"));
    push(get_student(2016123125, "바둑이", "글로벌애완학부"));
    push(get_student(2016123126, "꼴뚜기", "해양과학생물학부"));
    print_stack("스택 4명 push");
    pop();
    pop();
    print_stack("스택 2명 pop");
}
