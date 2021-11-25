// Binary Search

int binary_search(int list[], int key, int low, int high){
    int mid;
    if(low<=high){
        mid = (low+high)/2;
        if(key==list[mid]) return mid;
        else if(key<list[mid]) return binary_search(list, key, low, mid-1);
        else return binary_search(list, key, mid+1, high);
    }
    return -1;
}