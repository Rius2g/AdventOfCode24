#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LINE 1000

int* readLine(char* line, int* size) {
    int* numbers = (int*)malloc(sizeof(int)*MAX_LINE);
    *size = 0;
    char* token = strtok(line, " \n");
    while(token != NULL) {
        numbers[*size] = atoi(token);
        (*size)++;
        token = strtok(NULL, " \n");
    }
    numbers = realloc(numbers, sizeof(int)*(*size));
    return numbers;
}

// Check if sequence is valid after removing skip_index
int isValidAfterRemoval(int* numbers, int size, int skip_index) {
    // Create new array without the skipped number
    int newSize = size - 1;
    int* newSeq = malloc(sizeof(int) * newSize);
    int pos = 0;
    
    for(int i = 0; i < size; i++) {
        if(i != skip_index) {
            newSeq[pos++] = numbers[i];
        }
    }
    
    // Check if sequence is valid
    if(newSize < 2) {
        free(newSeq);
        return 0;
    }
    
    int should_increase = (newSeq[1] > newSeq[0]);
    
    for(int i = 1; i < newSize; i++) {
        int diff = newSeq[i] - newSeq[i-1];
        if(abs(diff) < 1 || abs(diff) > 3) {
            free(newSeq);
            return 0;
        }
        if(should_increase && diff <= 0) {
            free(newSeq);
            return 0;
        }
        if(!should_increase && diff >= 0) {
            free(newSeq);
            return 0;
        }
    }
    
    free(newSeq);
    return 1;
}

int safe(int* numbers, int size) {
    // First check if perfect as-is
    if(isValidAfterRemoval(numbers, size, -1)) return 1;
    
    // Try removing each number
    for(int i = 0; i < size; i++) {
        if(isValidAfterRemoval(numbers, size, i)) return 1;
    }
    
    return 0;
}

int main() {
    FILE *fptr;
    char line[MAX_LINE];
    int safeLines = 0;
    
    fptr = fopen("2DecInput.txt", "r");
    if(fptr == NULL) {
        printf("File not found\n");
        return 1;
    }
    
    while(fgets(line, MAX_LINE, fptr) != NULL) {
        int size;
        int* numbers = readLine(line, &size);
        safeLines += safe(numbers, size);
        free(numbers);
    }
    
    fclose(fptr);
    printf("Safe lines: %d\n", safeLines);
}
