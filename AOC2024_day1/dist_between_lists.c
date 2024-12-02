#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    
    int *left;
    int *right;
    int *dist;

    FILE *file;
    int row = 0;
    int tmp_left;
    int tmp_right;
    char line[15];

    file = fopen("list_day1_1.txt", "r");
        if (file == NULL) {
            printf("Error: Could not open file %s\n", "list_day1_1.txt");
            return 1;
        }

    while(fscanf(file, "%d %d", &tmp_left, &tmp_right) == 2){
        row++;
    }
    
    rewind(file);

    left = (int * )malloc(row * sizeof(int));
    if (left == NULL) {
        printf("Memory allocation error\n");
        fclose(file);
        return 1;
    }

    right = (int * )malloc(row * sizeof(int));
    if (right == NULL) {
        printf("Memory allocation error\n");
        fclose(file);
        return 1;
    }

    dist = (int * )malloc(row * sizeof(int));
    if (dist == NULL) {
        printf("Memory allocation error\n");
        fclose(file);
        return 1;
    }

    file = fopen("list_day1_1.txt", "r");
        if (file == NULL) {
            printf("Error: Could not open file %s\n", "list_day1_1.txt");
            return 1;
        }

    for (int i = 0; i < row; i++){
        fscanf(file, "%d %d", &left[i], &right[i]);
    }

    fclose(file);

    for(int i = 0; i<row;i++){
        for(int j = 0; j<row;j++){
            if(left[i]<left[j]){
                int tmp1 = left[i];
                left[i] = left[j];
                left[j] = tmp1;
            }
            if(right[i]<right[j]){
                int tmp2 = right[i];
                right[i] = right[j];
                right[j] = tmp2;
            }
        }
    }

    //printf("%d\n", row);    
    int final = 0;

    for(int i = 0; i<row; i++){
        dist[i] = abs(left[i] - right[i]);
        final += dist[i];
    }
    printf("final %d\n", final);
    
    int similarity = 0;

    for(int i = 0; i<row;i++){
        int cnt = 0;
        for(int j = 0; j<row;j++){
            if(left[i]==right[j]){
                cnt++;
            }
        }
        similarity += cnt*left[i];
    }

    printf("similarity %d", similarity);
    return 0;
}//main