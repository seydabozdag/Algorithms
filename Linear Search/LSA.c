#include<stdio.h>  

int linearSearch(int a[], int n, int val) {  

    for (int i = 0; i < n; i++) { 

        if (a[i] == val) {
            return i+1;
        }
    }  
    return -1;  

}  

int main() {  

    int a[] = {48, 34, 35, 18, 30, 15, 72};   
    int val = 30;
    int n = sizeof(a) / sizeof(a[0]); 
    int res = linearSearch(a, n, val);   

    printf("The elements of the array are: ");  

    for(int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if(i != n - 1) {
            printf(" ");
        }  
    }

    if(res == -1) {
        printf("\nElement is not in the array");  

    }else  
        printf("\nElement at %d. index of the array", res); 

    return 0;  

}  