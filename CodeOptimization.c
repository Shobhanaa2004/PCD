#include <stdio.h>
#include <string.h>

struct op {
    char l;
    char r[20];
} op[10], pr[10];
void main() {
    int i, j, k, n, z = 0, a, q;
    char *p, *l, *tem, temp, t;
    printf("Enter the Number of Values: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("left: "); scanf(" %c", &op[i].l);
        printf("right: "); scanf(" %s", op[i].r);
    }
    printf("Intermediate Code\n");
    for (i = 0; i < n; i++) printf("%c=%s\n", op[i].l, op[i].r);
    // Dead code elimination
    for (i = 0; i < n - 1; i++) {
        temp = op[i].l;
        for (j = 0; j < n; j++)
            if (strchr(op[j].r, temp)) {
                pr[z].l = op[i].l;
                strcpy(pr[z++].r, op[i].r);
                break;
            }
    }
    pr[z].l = op[n - 1].l;
    strcpy(pr[z++].r, op[n - 1].r);
    printf("\nAfter Dead Code Elimination\n");
    for (k = 0; k < z; k++) printf("%c\t=%s\n", pr[k].l, pr[k].r);
    // Common subexpression elimination
    for (i = 0; i < z; i++) {
        tem = pr[i].r;
        for (j = i + 1; j < z; j++) {
            if (strstr(tem, pr[j].r)) {
                t = pr[j].l; pr[j].l = pr[i].l;
                for (k = 0; k < z; k++) {
                    l = strchr(pr[k].r, t);
                    if (l) { a = l - pr[k].r; pr[k].r[a] = pr[i].l; }
                }
            }
        }
    }
    printf("Eliminate Common Expression\n");
    for (i = 0; i < z; i++) printf("%c\t=%s\n", pr[i].l, pr[i].r);
    // Remove duplicates
    for (i = 0; i < z; i++)
        for (j = i + 1; j < z; j++)
            if (pr[i].l == pr[j].l && strcmp(pr[i].r, pr[j].r) == 0)
                pr[i].l = '\0';
    printf("Optimized Code\n");
    for (i = 0; i < z; i++)
        if (pr[i].l != '\0') printf("%c=%s\n", pr[i].l, pr[i].r);
}
