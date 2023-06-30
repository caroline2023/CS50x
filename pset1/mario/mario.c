#include <cs50.h>
#include <stdio.h>

void mario(int n);

int main(void) 
{
    int n;
    
    do
    {
        n = get_int("Height: "); //to get a user input
    }
    while (n < 1 || n > 8); //to make sure it's in the specified range
    
    mario(n);
}

void mario(int n)
{
    for (int i = 0; i < n; i++) //each row
    {
        for (int j = 0; j < n - i - 1; j++) //blank spaces
        {
            printf(" ");
        }
        
        for (int k = 0; k < i + 1; k++) //the #s
        {
            printf("#");
        }
        
        printf("  "); 
        
        for (int k = 0; k < i + 1; k++) //the #s
        {
            printf("#");
        }
        
        printf("\n"); //next row
    }
}