#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(void)
{
    // printf("What is your name?: ");
    string name = GetString();

    for (int stringChar = 0; stringChar < strlen(name); stringChar++)
    {
        int theCharacter = name[stringChar];
        if (stringChar == 0)
        {
            theCharacter = toupper(theCharacter);
            printf("%c", theCharacter);
        }
        else if ( isspace(theCharacter) )
        {
            theCharacter = toupper(name[stringChar+1]);
            printf("%c", theCharacter);
        }
        else if(stringChar + 1 == strlen(name))
        {
            printf("\n");
        }
    }
}