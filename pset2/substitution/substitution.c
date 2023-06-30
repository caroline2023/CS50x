#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool valid(string cipher); //checks if the cipher is valid or not
string substitution(string text, string cipher); //takes in two arguments, the text and the cipher

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        if (valid(argv[1])) //checking to make sure the first thing is actually a letter
        {
            string text = get_string("plaintext: ");
            string ans = substitution(text, argv[1]);
            printf("ciphertext: %s\n", ans);
            return 0;
        }
        else
        {
            printf("Usage: ./substitution key\n");//not cooperating
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

bool valid(string cipher)
{
    bool x = true;
    if (strlen(cipher) == 26)
    {
        for (int i = 0; i < 26; i++)
        {
            if ('A' > toupper(cipher[i]) || toupper(cipher[i]) > 'Z') //check to make sure they're actually letters
            {
                x = false;
                break;
            }
            for (int j = i + 1; j < 26; j++)
            {
                if (toupper(cipher[i]) == toupper(cipher[j])) //make sure no repeats
                {
                    x = false;
                    break;
                }
            }
        }
    }
    else
    {
        x = false;
    }
    return x;
}

string substitution(string text, string cipher)
{
    int n = strlen(text); 
    int x = 0;
    string txt = text; //i dont wanna change the original
    for (int i = 0; i < n; i++)
    {
        if ('A' <= text[i] && text[i] <= 'Z')//two cases, upper and lower
        {
            x = text[i] - 'A';//to find the index in the cipher
            txt[i] = toupper(cipher[x]); 
        }
        else if ('a' <= text[i] && text[i] <= 'z')
        {
            x = text[i] - 'a';
            txt[i] = tolower(cipher[x]);
        }
    }
    return txt;
}