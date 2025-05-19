#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Needed for strlen()

int main()
{
    char stack[50], ip[50], opt[10][10][1], ter[10];
    int i, j, k, n, top = -1, row = -1, col = -1;

    // Initialize stack and input
    for (i = 0; i < 50; i++) {
        stack[i] = '\0';
        ip[i] = '\0';
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            opt[i][j][0] = '\0';
        }
    }

    // Get terminals
    printf("Enter the number of terminals: ");
    scanf("%d", &n);

    printf("Enter the terminals (single characters):\n");
    for (i = 0; i < n; i++) {
        scanf(" %c", &ter[i]);  // Space before %c to skip whitespace
    }

    // Get precedence table
    printf("Enter the values for operator precedence table:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Enter precedence between %c and %c: ", ter[i], ter[j]);
            scanf(" %c", &opt[i][j][0]);
        }
    }

    // Display operator precedence table
    printf("\nOperator Precedence Table:\n\t");
    for (i = 0; i < n; i++)
        printf("%c\t", ter[i]);
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%c\t", ter[i]);
        for (j = 0; j < n; j++) {
            printf("%c\t", opt[i][j][0]);
        }
        printf("\n");
    }

    // Input string
    printf("Enter the input string (append $ at end): ");
    scanf("%s", ip);

    // Initialize stack
    stack[++top] = '$';
    i = 0;

    printf("\nStack\t\tInput\t\tAction\n");

    while (1) {
        // Print stack
        for (k = 0; k <= top; k++)
            printf("%c", stack[k]);
        printf("\t\t");

        // Print remaining input
        for (k = i; k < strlen(ip); k++)
            printf("%c", ip[k]);
        printf("\t\t");

        // Accept
        if (stack[top] == '$' && ip[i] == '$') {
            printf("String accepted\n");
            break;
        }

        // Find row and col in table
        col = row = -1;
        for (k = 0; k < n; k++) {
            if (stack[top] == ter[k])
                col = k;
            if (ip[i] == ter[k])
                row = k;
        }

        if (row == -1 || col == -1) {
            printf("Invalid symbol\n");
            break;
        }

        if (opt[col][row][0] == '<' || opt[col][row][0] == '=') {
            stack[++top] = opt[col][row][0];  // push precedence marker
            stack[++top] = ip[i];             // push current input
            printf("Shift %c\n", ip[i]);
            i++;
        } else if (opt[col][row][0] == '>') {
            while (stack[top] != '<' && top > 0)
                top--;
            if (stack[top] == '<')
                top--;
            printf("Reduce\n");
        } else {
            printf("String not accepted\n");
            break;
        }
    }

    return 0;
}
