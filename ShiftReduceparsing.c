#include <stdio.h>
#include <string.h>

#define MAX 64

char stack[MAX], input[MAX];
int top = -1, ip = 0;

void printStackInput(const char *action) {
    printf("%-20s%-20s%-20s\n", stack, input + ip, action);
}

int tryReduction() {
    // Apply reductions in reverse grammar hierarchy
    // F -> (E)
    if (top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')') {
        stack[top - 2] = 'F';
        top -= 2;
        printStackInput("Reduce F->(E)");
        return 1;
    }
    // F -> i
    if (top >= 0 && stack[top] == 'i') {
        stack[top] = 'F';
        printStackInput("Reduce F->i");
        return 1;
    }
    // T -> T * F
    if (top >= 2 && stack[top - 2] == 'T' && stack[top - 1] == '*' && stack[top] == 'F') {
        stack[top - 2] = 'T';
        top -= 2;
        printStackInput("Reduce T->T*F");
        return 1;
    }
    // T -> F
    if (top >= 0 && stack[top] == 'F') {
        stack[top] = 'T';
        printStackInput("Reduce T->F");
        return 1;
    }
    // E -> E + T
    if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'T') {
        stack[top - 2] = 'E';
        top -= 2;
        printStackInput("Reduce E->E+T");
        return 1;
    }
    // E -> T
    if (top >= 0 && stack[top] == 'T') {
        stack[top] = 'E';
        printStackInput("Reduce E->T");
        return 1;
    }
    return 0;
}

int main() {
    printf("Enter the input string (ending with $): ");
    scanf("%s", input);
    strcat(input, "$");

    printf("\n%-20s%-20s%-20s\n", "Stack", "Input", "Action");

    while (1) {
        stack[++top] = input[ip++];
        stack[top + 1] = '\0';
        printStackInput("Shift");

        // Keep reducing as much as possible
        while (tryReduction());

        if (stack[0] == 'E' && stack[1] == '$' && input[ip] == '\0') {
            printStackInput("Accept");
            break;
        }

        if (input[ip] == '\0' && !tryReduction()) {
            printStackInput("Reject");
            break;
        }
    
}

    return 0;
}
