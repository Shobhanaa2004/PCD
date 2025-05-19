%{
#include <stdio.h>
int line_count = 0, word_count = 0;
%}

%%

\n      { line_count++; }  // Increment line count on every newline
[ \t]+  { /* Ignore spaces and tabs */ }
[a-zA-Z0-9_]+ { word_count++; } // Count words
.       { /* Ignore other characters */ }

%%

int yywrap() {
    return 1;  // Return 1 to indicate end of input
}

int main() {
    yylex();
    printf("Number of lines: %d\n", line_count);
    printf("Number of words: %d\n", word_count);
    return 0;
}


input file
