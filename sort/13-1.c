// Selection, Insertion, Bubble
#include <stdio.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

void printArray(int arr[], int n, char *str){
    int i;
    printf("%s = ", str);
    for(i=0; i<n; i++)
        printf("%3d", arr[i]);
    printf("\n");
}

void printStep(int arr[], int n, int val){
    int i;
    printf("  Step %2d = ", val);
    for(i=0; i<n; i++)
        printf("%3d", arr[i]);
    printf("\n");
}

// 선택 정렬
void selection_sort(int list[], int n){
    int i, j, tmp;
    for(i=0; i<n-1; i++){
        for(j=i+1; j<n; j++){
            if(list[j]<list[i])
                SWAP(list[i], list[j], tmp);
        }
        printStep(list, n, i+1);
    }
}

// 삽입 정렬
void insertion_sort(int list[], int n){
    int i, j, key;
    for(i=1; i<n; i++){
        key = list[i];
        for(j=i-1; j>=0 && list[j]>key; j--){
            list[j+1] = list[j];
        }
        list[j+1] = key;
        printStep(list, n, i);
    }
}

// 버블 정렬
void bubble_sort(int list[], int n){
    int i, j, flag, tmp;
    for(i=n-1; i>0; i--){
        flag = 0;
        for(j=0; j<i; j++){
            if(list[j]>list[j+1]){
                SWAP(list[j], list[j+1], tmp);
                flag = 1;
            }
        }
        if(!flag) break;
        printStep(list, n, n-i);
    }
}

void main(){
    int list[9] = {5, 3, 8, 4, 9, 1, 6, 2, 7};
    printArray(list, 9, "Original ");
    // selection_sort(list, 9);
    // printArray(list, 9, "Selection ");
    // insertion_sort(list, 9);
    // printArray(list, 9, "Insertion ");
    bubble_sort(list, 9);
    printArray(list, 9, "Bubble ");
}