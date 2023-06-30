#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Enter your name: "); //asks for user input
    printf("hello, %s.\n", name); //string formatting
}