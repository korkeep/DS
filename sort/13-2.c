// Merge
#include <stdio.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
#define MAX_SIZE 1024

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

static void merge(int list[], int left, int mid, int right){
    int i, j, k, l;
    k = left;
    static int sorted[MAX_SIZE];
    // 분할 정렬된 list의 병합
    for(i=left, j=mid+1; i<=mid && j<=right; ){
        sorted[k++] = (list[i]<=list[j]) ? list[i++] : list[j++];
    }
    // 한쪽에 남아 있는 레코드의 일괄 복사
    if(i>mid){
        for(l=j; l<=right; l++, k++){
            sorted[k] = list[l];
        }
    }
    else{
        for(l=i; l<=mid; l++, k++){
            sorted[k] = list[l];
        }
    }
    // sorted를 list로 다시 복사
    for(l=left; l<=right; l++){
        list[l] = sorted[l];
    } 
}

void merge_sort(int list[], int left, int right){
    if(left<right){
        int mid = (left+right)/2;
        merge_sort(list, left, mid);
        merge_sort(list, mid+1, right);
        merge(list, left, mid, right);
    }
}

void main(){
    int list[9] = {5, 3, 8, 4, 9, 1, 6, 2, 7};
    printArray(list, 9, "Original ");
    merge_sort(list, 0, 8);
    printArray(list, 9, "Merge ");
}