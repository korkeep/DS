// Quick
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

int partition(int list[], int left, int right){
    int tmp;
    int low = left+1;
    int high = right;
    int pivot = list[left];             // pivot 설정
    while(low<high){                    // low와 high가 역전되지 않는 한 반복
        for( ; low<=right && list[low] < pivot; low++);
        for( ; high>=left && list[high] > pivot; high--);
        if(low < high)                  // 선택된 두 레코드 교환
            SWAP(list[low], list[high], tmp);
    }
    SWAP(list[left], list[high], tmp);  // high과 pivot 항목 교환
    return high;
}

void quick_sort(int list[], int left, int right){
    int q;
    if(left<right){
        q = partition(list, left, right);
        quick_sort(list, left, q-1);
        quick_sort(list, q+1, right);
    }
}

void main(){
    int list[9] = {5, 3, 8, 4, 9, 1, 6, 2, 7};
    printArray(list, 9, "Original ");
    quick_sort(list, 0, 8);
    printArray(list, 9, "Quick ");
}