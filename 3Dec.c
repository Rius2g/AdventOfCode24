#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int mul(int x, int y){
    return x*y;
}

int main(){
    FILE *fp;
    //search for sequence, mul(x,y) 
   long result = 0;
   bool enabled = true;
   int x, y;

   fp = fopen("3DecInput.txt", "r");
   if (fp == NULL){
       printf("File not found\n");
       exit(1);
   }

      char c;
    while ((c = fgetc(fp)) != EOF) {
        // Check for do()
        if (c == 'd') {
            char next = fgetc(fp);
            if (next == 'o') {
                next = fgetc(fp);
                if (next == 'n') {  // don't()
                    if (fgetc(fp) == '\'' && fgetc(fp) == 't' && 
                        fgetc(fp) == '(' && fgetc(fp) == ')') {
                        enabled = false;
                    }
                }
                else if (next == '(' && fgetc(fp) == ')') {  // do()
                    enabled = true;
                }
            }
            continue;
        }

        // Must find exact "mul("
        if (c != 'm') continue;
        if (fgetc(fp) != 'u') continue;
        if (fgetc(fp) != 'l') continue;
        if (fgetc(fp) != '(') continue;

        // Read X
        int x = 0, chars_read = 0;
        while ((c = fgetc(fp)) >= '0' && c <= '9') {
            chars_read++;
            if (chars_read > 3) break;  // Too many digits
            x = x * 10 + (c - '0');
        }
        if (chars_read == 0 || chars_read > 3 || c != ',') continue;

        // Read Y
        int y = 0;
        chars_read = 0;
        while ((c = fgetc(fp)) >= '0' && c <= '9') {
            chars_read++;
            if (chars_read > 3) break;  // Too many digits
            y = y * 10 + (c - '0');
        }
        if (chars_read == 0 || chars_read > 3 || c != ')') continue;

        // Only add if enabled
        if (!enabled) {
            continue;
        }

        // Valid multiplication found
        result += mul(x, y);
    }
   

   printf("Result: %ld\n", result);

   fclose(fp);
}
