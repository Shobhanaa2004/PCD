#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main()
{
    int i=0,j=0,x=0,n;
    void *add[15],*p;
    char b[15],d[15],c,ch;

    printf("Enter an expression:");
    while((c= getchar())!='\$'){
        b[i]=c;
        i++;
    }
    n=i-1;
    i=0;
    printf("Given Expression:");
    while(i<=n){
        printf("%c",b[j]);
        i++;
    }

    printf("Symbol Table:");
    printf("\nSymbol\t\tAddress\t\tType\n");


    while(j<=n){
        c=b[j];

        if(isalpha((unsigned char)c)){
            p=malloc(sizeof(char));
            add[x]=p;
            d[x]=c;
            printf("\n%c\t%p\tIdentifier",c,p);
            x++;
            j++;
        }
        else{
            ch=c;
            if(ch=='+'||ch=='*'||ch=='-'||ch=='/'){
                p=malloc(sizeof(char));
                add[x]=p;
                d[x]=ch;
                printf("\n%c\t%p\t\Operator",ch,p);
            x++;
            j++;
            }
            else{
                j++;
            }
        }
    }
    return 0;

}
