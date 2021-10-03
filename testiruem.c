#include <stdio.h>
#include<stdlib.h>

void strToInt(int a,char* b){
    
    int counter = -1;
    while(a>=1)
    {
        counter++;
        *b = a%10+'0';
        
        b++;
        a = a/10;
    }
    
    
    
    
    
    b = '\0';
    b--;
    printf("%c - \n",*b);
    b--;
    //
    //b = b-counter+1;
    //return b;
    
}

int main()
{
    int sab = 134;
    char* scoreText; scoreText = (char*)malloc(12);
    *scoreText = 7;
     strToInt(sab,scoreText);
    printf("%c",*(scoreText+1));

    return 0;
}   
