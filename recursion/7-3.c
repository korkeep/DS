#include <stdio.h>

#define MAZE_SIZE 6
char map[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'}
};

int xExit=5, yExit=4, done=0;

int is_valid(int x, int y){
    if(x < 0 || y < 0 || x >= MAZE_SIZE || y >= MAZE_SIZE){
        return 0;
    }
    else {
        return (map[y][x] == '0' || map[y][x] == 'x');
    }
}

// Recursive로 구현
void recursive(int x, int y) {
    if(done) return;
    printf("(%d, %d)", x, y);
    if(x==xExit && y==yExit){
        done = 1;
        return;
    }
    map[y][x] = '.';    // visited
    if(is_valid(x-1, y)) recursive(x-1, y); // 우 (우선순위 4)
    if(is_valid(x+1, y)) recursive(x+1, y); // 좌 (우선순위 3)
    if(is_valid(x, y-1)) recursive(x, y-1); // 하 (우선순위 2)
    if(is_valid(x, y+1)) recursive(x, y+1); // 상 (우선순위 1)
}

void main(){
    recursive(0, 1);
    if(done) printf("\n ==> 출구가 탐지되었습니다.\n");
    else printf("\n ==> 출구를 찾지 못했습니다.\n");
}