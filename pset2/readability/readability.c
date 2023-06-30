#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int W(string text); //number of words which were gonna need
float L(string text);
float S(string text);

int main(void)
{
    string text = get_string("Text: ");
    int index = round(0.0588 * L(text) - 0.296 * S(text) - 15.8); //the coleman liau formula
    if (0 < index && index < 16) //deciding on what to print here 
    {
        printf("Grade %i\n", index); 
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n"); //these two are different so i'll just put them in different things
    }
    else 
    {
        printf("Before Grade 1\n");
    }
}

int W(string text)
{
    int n = strlen(text);
    int w = 1; //starts with 1 bc there isn't a space at the end
    for (int i = 0; i < n; i++)
    {
        if (text[i] == ' ')
        {
            w++; //adds one every time we get to the start of the next word
        }
    }
    return w;
}

float L(string text)
{
    int n = strlen(text); //since it doesn't seem like a global variable im assuming we have to redefine it every time
    int l = 0;
    for (int i = 0; i < n; i++)
    {
        if ('A' <= text[i] && text[i] <= 'Z')
        {
            l++;
        }
        else if ('a' <= text[i] && text[i] <= 'z')
        {
            l++;
        }
    }
    return 100 * (float) l / W(text); //letters per 100 words
}

float S(string text)
{
    int n = strlen(text);
    int s = 0; //starts with zero bc theres always something at the end
    for (int i = 0; i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')//can you use three of these? not sure yet we'll see
        {
            s++;
        }
    }
    return 100 * (float) s / W(text); //sentecnes per 100 words
}