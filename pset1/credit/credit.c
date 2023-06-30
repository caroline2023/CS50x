#include <cs50.h>
#include <stdio.h>

bool checksum(long n);

int main(void)
{
    long num = get_long("Number: ");
    if (checksum(num))
    {
        if (4000000000000 <= num && num < 5000000000000) //check to make sure theyre in the right ranges
        {
            printf("VISA\n");
        }
        
        else if (340000000000000 <= num && num < 350000000000000)
        {
            printf("AMEX\n");
        }
        
        else if (370000000000000 <= num && num < 380000000000000)
        {
            printf("AMEX\n");
        }
        
        else if (4000000000000000 <= num && num < 5000000000000000)
        {
            printf("VISA\n");
        }
        
        else if (5100000000000000 <= num && num < 5600000000000000) //too bad no power function
        {
            printf("MASTERCARD\n"); //ok i dont think there was a problem with the ordering of intervals 
            //all the problems were in the checksum function lol
        }
        
        else 
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

bool checksum(long n)
{
    long x = 0;
    for (long i = 10; i < 10 * n + 1; i *= 100) //has to be long int or else zero division bc it gets too big
    {
        x += (n % i) / (i / 10); //for the odd places
    }
    
    for (long j = 100; j < 10 * n + 1; j *= 100) //for the even places
    {
        //x += 2 * (n % j) / (j / 10);
        x += (2 * ((n % j) / (j / 10))) % 10; //first digit
        x += (2 * ((n % j) / (j / 10))) / 10; //second digit
        /*so if i wanted to do both on one line i should do parentheses over it because += some expression
        then + another would've gone weird*/
    }
    if (x % 10 == 0) //this is straightforward
    {
        return true;
    }
    else
    {
        return false;
    }
}