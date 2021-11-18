#include <stdio.h>

int factorial(int n){
    printf("factorial(%d)\n", n);
    if(n==1){
        return 1;
    }
    else{
        return (n * factorial(n-1));
    }
}

void main(){
    factorial(3);
}