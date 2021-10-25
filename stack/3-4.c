// postfix 구현 문제

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_STACK_SIZE 100

typedef double Element;
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

double calc_postfix(char expr[]){
    char c;
    int i=0;
    double val1, val2, val3;

    init_stack();
    while(expr[i] != '\0'){
        c = expr[i++];
        if(c>='0' && c<='9'){
            val1 = c-'0';
            push(val1);
        }
        else if(c=='+' || c=='-' || c=='*' || c=='/'){
            val3 = pop();
            val2 = pop();
            switch(c){
                case'+': push(val2 + val3); break;
                case'-': push(val2 - val3); break;
                case'*': push(val2 * val3); break;
                case'/': push(val2 / val3); break;
            }
        }
    }
    return pop();
}

void main(){
    char expr[2][80] = {"8 2 / 3 - 3 2 * +", "1 2 / 4 * 1 4 / *"};
    printf("수식: %s = %lf\n", expr[0], calc_postfix(expr[0]));
    printf("수식: %s = %lf\n", expr[1], calc_postfix(expr[1]));
}