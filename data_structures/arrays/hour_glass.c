/* https://www.hackerrank.com/challenges/2d-array/problem */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * TEST CODE
 *
 * //  int arr[6][6] = {
 *       {1, 1, 2, 1, 3, 2},
 *       {2, 1, 2, 0, 0, 2},
 *       {0, 1, 0, 1, 2, 0},
 *       {1, 0, 2, 0, 2, 2},
 *       {1, 0, 2, 3, 0, 0},
 *       {1, 1, 0, 0, 0, 3}};
 * 
 *   for (i = 0; i < 6; i++) {
 *       for (j = 0; j < 6; j++) {
 *           printf("%d ", arr[i][j]);
 *       }
 *       printf("\n");
 *   }
 *    for (m = 0; m < 3; m++) {
 *        for (n = 0; n < 3; n++) {
 *
 *          printf("%d ", max_hour_glass[m][n]);
 *       }
 *       printf("\n");
 *   }
 */

/*
 * (1) Input the 6x6 arrayi.
 * (2) Scan horizontally.
 * (3) Check that an hour glass can be computed within the limits of the array boundaries.
 * (4) Store a temporary 3x3 array with the maximum value found.
 */
int
main(int argc, char *argv[])
{
    int i, j, x, y, m, n;
    int arr[6][6];
    int max_total = 0;
    int max_hour_glass[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};

    for(int arr_i = 0; arr_i < 6; arr_i++){
        for(int arr_j = 0; arr_j < 6; arr_j++){

            scanf("%d",&arr[arr_i][arr_j]);
        }
    }

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            /* check the booundaries first */
            if ((i+2 >= 6) || (j-1 < 0) || (j+1 >= 6)) {
                /* outside outer boundary */
                // printf("continue. i = %d, j = %d\n", i, j);
                continue;
            }

            int temp_total = 0;
            int temp_hour_glass[3][3] = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}};

            /* calculate hour glass at current index */
            for (x = i, m = 0; x <= i+2, m < 3; x++, m++) {
                for (y = j-1, n = 0; y <= j+1, n < 3; y++, n++) {
                    /* skip the left and right digits in the middle row */
                    if ((x == i+1) && (y != j)) {
                        continue;
                    }

                    temp_total += arr[x][y];
                    temp_hour_glass[m][n] = arr[x][y];
                }
            }


            /* store the maximum values for later printing */
            if (temp_total > max_total) {
                max_total = temp_total;
                memcpy(max_hour_glass, temp_hour_glass, sizeof(int) * (3*3));
            }
            printf("[%d][%d] total = %d\n", i, j, temp_total);
        }
    }

    printf("%d\n", max_total);

    return (0);
}
