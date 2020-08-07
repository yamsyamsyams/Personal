/* 
 * File:   main.c
 * Author: hoangjam
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 

#define MAX_LEN 30

#define RMN(str) str[strcspn(str,"\n")]=0
#define FLUSH stdin=freopen(NULL,"r",stdin)

unsigned long fn(int);
void removeChars(char*, char*);

int main() {
    char str[MAX_LEN] = "";
    char tmp[MAX_LEN];

    // PART 1.//
    printf("Series: ");
    unsigned long x = 0;
    int index = 0;
    for (int i = 0; i < MAX_LEN; i++) {
        x = fn(i);
        printf("%lu ", x);
        if (isdigit(x) || isalpha(x)) {
            str[index] = x;
            index++;
        }
    }

    // PART 2.
    printf("\nString: ");
    //    for (int i = 0; i < MAX_LEN; i++) {
    printf("%s", str);
    //    }
    FLUSH;
    RMN(str);

    //PART 3.
    printf("\nPlease enter characters you want to remove: ");
    fgets(tmp, MAX_LEN, stdin);
    printf("New String: ");
    removeChars(str, tmp);
    printf("%s\n", str);

    return 0;
}

unsigned long fn(int n) {
    if (n < 3) {
        return 60;
    } else {
        return (2 * n) + (fn(n - 1) % 60);
    }
}

void removeChars(char* _str, char* _tmp) {
    size_t i = 0, j = 0;

    while (_str[j]) {
        bool b = true;
        size_t k = 0;

        while (_tmp[k] || _str[j] == k) {
            if (_str[j] == _tmp[k]) {
                b = false;
            }
            k++;
        }
        if (b) {
            if (i != j) {
                _str[i] = _str[j];
            }
            i++;
        }
        j++;
    }
    _str[i] = 0;
}