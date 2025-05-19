#include <stdio.h>
#include <string.h>

#define SUCCESS 1
#define FAILED 0

// Function declarations
int E(), Edash(), T(), Tdash(), F();

// Global variables
const char *cursor;
char input[64];

// Entry point
int main() {
    printf("Enter the string: ");
    scanf("%s", input);
    cursor = input;

    printf("\nInput Actions:\n\n");

    // Start parsing from E
    if (E() && *cursor == '\0') {
        printf("\nString is successfully parsed.\n");
        return 0;
    } else {
        printf("\nError in parsing the string.\n");
        return 1;
    }
}

// E → T E'
int E() {
    printf("%-16s E -> T E'\n", cursor);
    if (T()) {
        if (Edash())
            return SUCCESS;
    }
    return FAILED;
}

// E' → + T E' | ε
int Edash() {
    if (*cursor == '+') {
        printf("%-16s E' -> + T E'\n", cursor);
        cursor++;
        if (T()) {
            if (Edash())
                return SUCCESS;
        }
        return FAILED;
    } else {
        printf("%-16s E' -> ε\n", cursor);
        return SUCCESS;
    }
}

// T → F T'
int T() {
    printf("%-16s T -> F T'\n", cursor);
    if (F()) {
        if (Tdash())
            return SUCCESS;
    }
    return FAILED;
}

// T' → * F T' | ε
int Tdash() {
    if (*cursor == '*') {
        printf("%-16s T' -> * F T'\n", cursor);
        cursor++;
        if (F()) {
            if (Tdash())
                return SUCCESS;
        }
        return FAILED;
    } else {
        printf("%-16s T' -> ε\n", cursor);
        return SUCCESS;
    }
}

// F → (E) | i
int F() {
    if (*cursor == '(') {
        printf("%-16s F -> ( E )\n", cursor);
        cursor++;
        if (E()) {
            if (*cursor == ')') {
                cursor++;
                return SUCCESS;
            }
        }
        return FAILED;
    } else if (*cursor == 'i') {
        printf("%-16s F -> i\n", cursor);
        cursor++;
        return SUCCESS;
    } else {
        return FAILED;
    }
}
