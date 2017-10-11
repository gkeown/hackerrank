// https://www.hackerrank.com/challenges/ctci-array-left-rotation/problem

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

void
rotateLeft(int *array, int size, int rotate_by)
{
    int i = 0, j = 0;
    int tmp = 0;

    for (i = 0; i < rotate_by; i++) {
        // rotate the array
        for (j = 0; j < size; j++) {
            // store the value at index 0
            if (j == 0) {
                tmp = array[j];
            }
            
            // shift the values in the rest of the array left by 1
            if (j < (size - 1)) {
                array[j] = array[j+1];
            } else {
                // assign the value that was at index 0 to index size-1
                array[j] = tmp;
            }
        }
    }
}

int main(){
    int n; 
    int k; 
    scanf("%d %d",&n,&k);
    int *a = malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++){
       scanf("%d",&a[i]);
    }

    rotateLeft(a, n, k);

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
        
    return 0;
}
