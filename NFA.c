#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define EPSILON 'ε'

typedef struct State {
    int id;
    struct Transition *transition;
} State;

typedef struct Transition {
    char symbol;
    State* to;
    struct Transition *next;
} Transition;

typedef struct {
    State* accept;
    State* start;
} NFA;

int stateCount = 0;

State* newState() {
    State* s = (State*)malloc(sizeof(State));
    s->id = stateCount++;
    s->transition = NULL;
    return s;
}

void addTransition(State* from, char symbol, State* to) {
    Transition* t = (Transition*)malloc(sizeof(Transition));
    t->symbol = symbol;
    t->to = to;
    t->next = from->transition;
    from->transition = t;
}

NFA basicNFA(char c) {
    State* start = newState();
    State* end = newState();
    addTransition(start, c, end);
    NFA result = {end, start};
    return result;
}

NFA concat(NFA a, NFA b) {
    addTransition(a.accept, EPSILON, b.start);
    NFA result = {b.accept, a.start};  // fix: correct start and accept
    return result;
}

NFA unionNFA(NFA a, NFA b) {
    State* start = newState();
    State* end = newState();
    addTransition(start, EPSILON, a.start);
    addTransition(start, EPSILON, b.start);
    addTransition(a.accept, EPSILON, end);
    addTransition(b.accept, EPSILON, end);
    NFA result = {end, start};
    return result;
}

NFA star(NFA a) {
    State* start = newState();
    State* end = newState();
    addTransition(start, EPSILON, a.start);
    addTransition(a.accept, EPSILON, end);
    addTransition(a.accept, EPSILON, a.start);
    addTransition(start, EPSILON, end);
    NFA result = {end, start};
    return result;
}

void displayNFA(NFA nfa) {
    printf("\nTransition Table:");
    printf("\n+-------------------------------------------+");
    printf("\n| From       | Symbol         | To          |");
    printf("\n+-------------------------------------------+");

    int visited[MAX] = {0};
    State* queue[MAX];
    int front = 0, rear = 0;
    queue[rear++] = nfa.start;
    visited[nfa.start->id] = 1;

    while (front < rear) {
        State* current = queue[front++];
        for (Transition* t = current->transition; t != NULL; t = t->next) {
            printf("\n| q%-10d| %-14c| q%-10d|", current->id, t->symbol, t->to->id);

            if (!visited[t->to->id]) {
                visited[t->to->id] = 1;
                queue[rear++] = t->to;
            }
        }
    }

    printf("\n+-------------------------------------------+\n");
    printf("Start State: q%d\n", nfa.start->id);
    printf("Accept State: q%d\n", nfa.accept->id);
}

int main() {
    char regex[MAX];
    printf("Enter a regular expression without parentheses: ");
    scanf("%s", regex);

    NFA stack[MAX];
    int top = -1;

    for (int i = 0; i < strlen(regex); i++) {
        char c = regex[i];

        if (c == '.') {
            NFA b = stack[top--];
            NFA a = stack[top--];
            stack[++top] = concat(a, b);
        } else if (c == '*') {
            NFA a = stack[top--];
            stack[++top] = star(a);
        } else if (c == '|') {
            NFA b = stack[top--];
            NFA a = stack[top--];
            stack[++top] = unionNFA(a, b);
        } else {
            stack[++top] = basicNFA(c);
        }
    }

    NFA final = stack[top];
    displayNFA(final);
    return 0;
}
