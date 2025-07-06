#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000

typedef struct {
    char items[MAX];
    int top;
} CharStack;

typedef struct {
    int items[MAX];
    int top;
} IntStack;

void pushChar(CharStack *s, char val) {
    s->items[++(s->top)] = val;
}
char popChar(CharStack *s) {
    return s->items[(s->top)--];
}

void pushInt(IntStack *s, int val) {
    s->items[++(s->top)] = val;
}
int popInt(IntStack *s) {
    return s->items[(s->top)--];
}

void decode(char *input) {
    CharStack strStack = {.top = -1};
    IntStack numStack = {.top = -1};
    char temp[MAX], result[MAX] = "";
    int i = 0;

    while (input[i]) {
        if (isdigit(input[i])) {
            int num = 0;
            while (isdigit(input[i])) {
                num = num * 10 + (input[i++] - '0');
            }
            pushInt(&numStack, num);
        } else if (input[i] == '[') {
            pushChar(&strStack, input[i++]);
        } else if (isalpha(input[i])) {
            pushChar(&strStack, input[i++]);
        } else if (input[i] == ']') {
            int j = 0;
            while (strStack.top != -1 && strStack.items[strStack.top] != '[') {
                temp[j++] = popChar(&strStack);
            }
            temp[j] = '\0';
            popChar(&strStack);

            char segment[MAX] = "";
            for (int k = j - 1; k >= 0; k--) {
                strncat(segment, &temp[k], 1);
            }

            int repeat = popInt(&numStack);
            char expanded[MAX] = "";
            for (int r = 0; r < repeat; r++) {
                strcat(expanded, segment);
                strcat(expanded, " ");
            }

            for (int k = 0; expanded[k]; k++) {
                pushChar(&strStack, expanded[k]);
            }
            i++;
        } else {
            i++;
        }
    }

    int k = 0;
    while (strStack.top != -1) {
        result[k++] = popChar(&strStack);
    }
    result[k] = '\0';

    for (int m = k - 1; m >= 0; m--) {
        printf("%c", result[m]);
    }
    printf("\n");
}

int main() {
    char input[MAX];
    printf("Enter pattern: ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0';
    decode(input);
    return 0;
}