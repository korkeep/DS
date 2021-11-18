#include <stdio.h>

void hanoi_tower(int n, char from, char tmp, char to){
    if(n==1){
        printf("원판 1을 %c에서 %c로 옮긴다\n", from, to);
    }
    else{
        hanoi_tower(n-1, from, to, tmp);    // 맨 아래의 원판을 제외한 나머지 원판을 tmp로 옮긴다
        printf("원판 %d을 %c에서 %c로 옮긴다\n", n, from, to);
        hanoi_tower(n-1, tmp, from, to);    // tmp의 원판을 to로 옮긴다
    }
}

void main() {
    hanoi_tower(4, 'A', 'B', 'C');
}