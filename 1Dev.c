#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


#define MAX_LINES 10000


void bubble_sort(int list[], int n){
    int i, j, temp;
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-1-i; j++){
            if (list[j] > list[j+1]){
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}


int distances(int list1[], int list2[], int n){
    int i, sum = 0;
    for (i = 0; i < n; i++){
        sum += abs(list1[i] - list2[i]);
    }
    return sum;
}

long similarity_score(int search, int list[], int n){
    int i;
    long score = 0;
    for (i = 0; i < n; i++){
        if (list[i] == search){
            score++;
        }
        else if (list[i] > search){
            break;
        }
    }
    return score*search;
}



int main(){
    FILE *file;
    int list1[MAX_LINES], list2[MAX_LINES];

    int count = 0;

    file = fopen("input1Dec.txt", "r");
    if (file == NULL){
        printf("Error: File not found\n");
        exit(1);
    }

    while (!feof(file) && count < MAX_LINES){
        if(fscanf(file, "%d %d", &list1[count], &list2[count]) == 2){
            printf("%d %d\n", list1[count], list2[count]);
            count++;
        }
    }

    fclose(file);

    bubble_sort(list1, count);
    bubble_sort(list2, count);

    printf("Distance: %d\n", distances(list1, list2, count));
    
    long sum = 0;
    for(int i = 0; i < count; i++){
        sum += similarity_score(list1[i], list2, count);
    }

    printf("Similarity score: %ld\n", sum);
}





