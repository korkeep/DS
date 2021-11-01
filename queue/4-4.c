#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_QUEUE_SIZE 100

typedef struct{
    int x;
    int y;
} Location;
typedef Location Element;

Element data[MAX_QUEUE_SIZE];
int front;
int rear;

void error(char* str){
    printf("%s\n", str);
    exit(1);
}

void init_deque(){
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

void add_rear(Element val){
    if(is_full()){
        error("덱 포화 에러");
    }
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = val;
}

Element delete_front(){
    if(is_empty()){
        error("덱 공백 에러");
    }
    front = (front + 1) % MAX_QUEUE_SIZE;
    return data[front];
}

Element get_front(){
    if(is_empty()){
        error("덱 공백 에러");
    }
    return data[front];
}

void add_front(Element val){
    if(is_full()){
        error("덱 포화 에러");
    }
    data[front] = val;
    front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

Element delete_rear(){
    int prev = rear;
    if(is_empty()){
        error("덱 공백 에러");
    }
    rear = (rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return data[prev];
}

Element get_rear(){
    if(is_empty()){
        error("덱 공백 에러");
    }
    return data[front];
}

#define MAZE_SIZE 6
char map[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'}
};

Location getLocation(int x, int y){
    Location p;
    p.x = x;
    p.y = y;
    return p;
}

int is_valid(int x, int y){
    if(x < 0 || y < 0 || x >= MAZE_SIZE || y >= MAZE_SIZE){
        return 0;
    }
    else {
        return (map[y][x] == '0' || map[y][x] == 'x');
    }
}

// Stack으로 구현 (LIFO)
int DFS() {
    int x, y;
    Location here;

    init_deque();
    add_rear(getLocation(0, 1));    // 'e'로 시작하는 지점
    printf("DFS: ");
    while(is_empty() == 0){
        here = delete_rear();   // LIFO
        printf("(%2d, %2d)", here.x, here.y);
        x = here.x;
        y = here.y;
        if(map[y][x] == 'x'){
            return 1;
        }
        else{
            map[y][x] = '.';    // visited
            if(is_valid(x-1, y)) add_rear(getLocation(x-1, y)); // 우 (우선순위 4)
            if(is_valid(x+1, y)) add_rear(getLocation(x+1, y)); // 좌 (우선순위 3)
            if(is_valid(x, y-1)) add_rear(getLocation(x, y-1)); // 하 (우선순위 2)
            if(is_valid(x, y+1)) add_rear(getLocation(x, y+1)); // 상 (우선순위 1)
        }
    }
    return 0;
}

// Queue로 구현 (FIFO)
int BFS() {
    int x, y;
    Location here;

    init_deque();
    add_rear(getLocation(0, 1));    // 'e'로 시작하는 지점
    printf("BFS: ");
    while(is_empty() == 0){
        here = delete_front();  // FIFO
        printf("(%2d, %2d)", here.x, here.y);
        x = here.x;
        y = here.y;
        if(map[y][x] == 'x'){
            return 1;
        }
        else{
            map[y][x] = '.';    // visited
            if(is_valid(x-1, y)) add_rear(getLocation(x-1, y)); // 우 (우선순위 4)
            if(is_valid(x+1, y)) add_rear(getLocation(x+1, y)); // 좌 (우선순위 3)
            if(is_valid(x, y-1)) add_rear(getLocation(x, y-1)); // 하 (우선순위 2)
            if(is_valid(x, y+1)) add_rear(getLocation(x, y+1)); // 상 (우선순위 1)
        }
    }
    return 0;
}

void main(){
    // 삼항 연산자 사용 (조건) ? A : B
    //printf("->%s\n", DFS() ? "성공" : "실패");
    printf("->%s\n", BFS() ? "성공" : "실패");
}