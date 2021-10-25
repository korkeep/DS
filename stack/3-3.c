// 괄호 체크 문제

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STACK_SIZE 100

typedef char Element;
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

int check_matching(char expr[]){
    int i = 0, prev;
    char temp;
    init_stack();

    while(expr[i] != '\0'){
        temp = expr[i++];
        if(temp == '[' || temp == '(' || temp == '{'){
            push(temp);
        }
        else if(temp == ']' || temp == ')' || temp == '}'){
            // 스택이 비어있는 경우
            if(is_empty())
                return 2;
            prev = pop();
            // 스택의 이전에 저장된 괄호가 일치하지 않는 경우
            if((temp == ']' && prev != '[')
            || (temp == ')' && prev != '(')
            || (temp == '}' && prev != '{')){
                return 3;
            }
        }
    }
    // 끝까지 처리했는데 괄호가 남아있는 경우
    if(is_empty()==0) return 1;
    // 정상인 경우
    return 0;
}

void main(){
    char expr[4][80] = {"{A[(i+1)]=0;}", "if((i==0) && (j==0)", "A[(i+1])=0;", "A[i]=f)(;"};
    int errCode, i;

    printf("조건1: 끝까지 처리했는데 괄호가 남아있는 경우\n");
    printf("조건2: 스택이 비어있는 경우\n");
    printf("조건3: 스택의 이전에 저장된 괄호가 일치하지 않는 경우\n\n");

    for(i=0; i<4; i++){
        errCode = check_matching(expr[i]);
        if(errCode==0){
            printf("정상: %s\n", expr[i]);
        }
        else{
            printf("오류: %s (조건%d 위반)\n", expr[i], errCode);
        }
    }
}