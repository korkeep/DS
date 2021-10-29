#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_QUEUE_SIZE 100

typedef int Element;
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

bool is_empty(){
    return front == rear;
}

bool is_full(){
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

void print_queue(char msg[]){
    int i, maxi = rear;
    if(front >= rear){
        maxi += MAX_QUEUE_SIZE;
    }
    printf("%s[%2d]= ", msg, size());
    for(i=front+1; i<=maxi; i++){
        printf("%2d ", data[i%MAX_QUEUE_SIZE]);
    }
    printf("\n");
}

void main(){
    int i;

    init_queue();
    for(i=1; i<10; i++){
        enqueue(i);
    }
    print_queue("선형큐 enqueue 9회");
    
    printf("\tdequeue() --> %d\n", dequeue());
    printf("\tdequeue() --> %d\n", dequeue());
    printf("\tdequeue() --> %d\n", dequeue());
    print_queue("선형큐 dequeue 3회");
}