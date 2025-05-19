#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 10
int dfa[MAX][2];
int accept[MAX];
int state_count=0;

int new_state(){
       if(state_count>=MAX) {return -1;}
       dfa[state_count][0]=-1;
       dfa[state_count][1]=-1;
       accept[state_count]=0;
       return state_count++;

       }
int bulid(char *r){
     int curr=new_state();
     int len=strlen(r);

     for(int i=0;i<len;i++){
        if(i+2 <len && r[i+1]=='/' &&(r[i]=='a') && (r[i+2]=='b')){
            int next=new_state();
            dfa[curr][0]=next;
            dfa[curr][1]=next;
            accept[next]=1;
            curr=next;
            i+=2;
            return 0;
            }
        if(i+2 <len && r[i+1]=='/' &&(r[i]=='b') && (r[i+2]=='a')){
            int next=new_state();
            dfa[curr][1]=next;
            dfa[curr][0]=next;
            accept[next]=1;
            curr=next;
            i+=2;
            return 0;
            }
         if(i+2 < len && r[i+1] == '.' && (r[i] == 'a' || r[i] == 'b') && (r[i+2] == 'a' || r[i+2] == 'b')) {
            int c1 = (r[i] == 'a') ? 0 : 1;
            int c2 = (r[i+2] == 'a') ? 0 : 1;

            int mid = new_state();
            int next = new_state();

            dfa[curr][c1] = mid;
            dfa[mid][c2] = next;
            accept[next] = 1;
            curr = next;
            i += 2;
            return 0;
        }

        if(i+1<len && (r[i]=='a'||r[i]=='b') && r[i+1]=='*'){
            int c= (r[i]=='a'?0:1);
            dfa[curr][c]=curr;
            accept[curr]=1;
            i++;
        }
        if(i+1<len && (r[i]=='a'||r[i]=='b')){
                int next=new_state();
            int c= (r[i]=='a'?0:1);
            dfa[curr][c]=next;
            accept[next]=1;
        curr=next;
            i++;
            return 0;
        }
        printf("Invalid regex %c",*r);
        return -1;
     }
     }

     void printdfa(){
     for(int i=0;i<state_count;i++){
        printf("q[%d,a]-->%d\n",i,dfa[i][0]);
        printf("q[%d,b]-->%d\n",i,dfa[i][1]);
     }

      printf("\nAccepting states: ");
    for (int i = 0; i < state_count; i++) {
        if (accept[i]) {
            printf("q[%d] ", i);
        }
    }
    printf("\n");
     }

     int main(){
         char regex[50];
        printf("Enter the regex eg: a/b a* a:");
        scanf("%s",regex);

        if(bulid(regex)!=-1){
            printdfa();
        }




        }
