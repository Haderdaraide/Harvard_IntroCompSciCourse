#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int upperCaseShift(int shiftedValue);

int lowerCaseShift(int shiftedValue);



int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You need to input no more or less then one int. Please try again\n");
        return 1;
    }
    
    int shiftKey; 
    shiftKey = atoi(argv[1]); 
    while (shiftKey > 26)
    {
        shiftKey = shiftKey - 26;
    }
    string originalText = GetString();
    
    for (int characterNum = 0, textLength = strlen(originalText); characterNum < textLength;)
    {
        char theCharacter = originalText[characterNum];
        int ASCIIValue = theCharacter;
        int shiftedValue = ASCIIValue + shiftKey;
        if (isalpha(theCharacter))
        {
            if (isupper(theCharacter))
            {
                int updatedShiftedValue = upperCaseShift(shiftedValue);
                printf("%c", updatedShiftedValue);
            }
            else if(islower(theCharacter))
            {
                int updatedShiftedValue = lowerCaseShift(shiftedValue);
                printf("%c", updatedShiftedValue);
            }
        }
        else
        {
            printf("%c", theCharacter);
        }
        if (characterNum + 1 == textLength)
        {
            printf("\n");
        }
        characterNum++;
    }
    
    return 0;
}


int upperCaseShift(int shiftedValue)
{
    int UpperAlphabetStart = 65;
    int UpperAlphabetEnd = 90;
    
    if (shiftedValue > UpperAlphabetEnd)
    {
        shiftedValue = shiftedValue - UpperAlphabetEnd - 1;
        shiftedValue = shiftedValue + UpperAlphabetStart;
        return shiftedValue;
    }
    else
    {
        return shiftedValue;
    }
    
}

int lowerCaseShift(int shiftedValue)
{
    int LowerAlphabetStart = 97;
    int LowerAlphabetEnd = 122;

    if (shiftedValue > LowerAlphabetEnd)
    {
        shiftedValue = shiftedValue - LowerAlphabetEnd - 1;
        shiftedValue = shiftedValue + LowerAlphabetStart;
        return shiftedValue;
    }
    else
    {
        return shiftedValue;
    }
    
}