// Indexed Sequential
#include <stdio.h>
#define LIST_SIZE 9
#define INDEX_SIZE 3

typedef struct Index{
    int key;
    int index;
} Index;

int sequential_serach(int list[], int key, int low, int high){
    int i;
    for(i=low; i<=high; i++){
        if(list[i]==key) return i;
    }
    return -1;
}

int indexed_search(int list[], int nList, Index *tbl, int nTbl, int key){
    int i;
    if(key<list[0] || key>list[nList-1]) return -1; // Key 값이 리스트 범위 밖
    for(i=0; i<nTbl-1; i++){                        // Index 테이블 조사
        if(tbl[i].key<=key && tbl[i+1].key>key){
            return sequential_serach(list, key, tbl[i].index, tbl[i+1].index);
        }
    }
    return sequential_serach(list, key, tbl[nTbl-1].index, nList);
}

void main(){
    int list[LIST_SIZE] = {3, 9, 15, 22, 31, 55, 67, 88, 91};
    Index index[INDEX_SIZE] = {{3, 0}, {15, 3}, {67, 6}};

    int number, ret;
    printf("탐색할 숫자를 입력하세요: ");
    scanf("%d", &number);
    ret = indexed_search(list, LIST_SIZE, index, INDEX_SIZE, number);
    if(ret>=0) printf("탐색 성공: 숫자(%d) 위치(%d)\n", number, ret);
    else printf("탐색 실패: 숫자(%d)", number);
}