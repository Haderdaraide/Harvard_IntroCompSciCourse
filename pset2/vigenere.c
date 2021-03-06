#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int upperCaseShift(int shiftedValue);

int lowerCaseShift(int shiftedValue);

int argvChecker(string testString);

int caesar(char theCharacter, int shiftedValue);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You must input a string for the command prompt (only 1 string!)\n");
        return 1;
    }
    int numChecker;
    numChecker = argvChecker(argv[1]);
    if (numChecker != 0)
    {
        printf("You must provide a string with only letters\n");
        return 1;
    }
    
    string originalText = GetString();
    string keyWord = argv[1];
    int keyWordLen = strlen(keyWord);
    int keyWordIndex = 0;
    int LowerAlphabetStart = 97;
    int UpperAlphabetStart = 65;
    
    for (int charIndex = 0, originalTextLength = strlen(originalText); charIndex < originalTextLength;)
    {
        // if (keyWordIndex > keyWordLen)
        // {
        //     keyWordIndex = 0;
        // }
        char theCharacter = originalText[charIndex];
        char theKeyCharacter = keyWord[keyWordIndex];
        int keyCharASCIIValue = keyWord[keyWordIndex];
        int CharASCIIValue = theCharacter;
        int shiftedValue = 0;
        
        if (isupper(theKeyCharacter))
        {
            shiftedValue = keyCharASCIIValue % UpperAlphabetStart;
            shiftedValue = shiftedValue + CharASCIIValue;
        }
        if (islower(theKeyCharacter))
        {
            shiftedValue = keyCharASCIIValue % LowerAlphabetStart;
            shiftedValue = shiftedValue + CharASCIIValue;
        }

        int updatedShiftedValue = caesar(theCharacter, shiftedValue);
        printf("%c", updatedShiftedValue);
        if (isalpha(theCharacter))
        {
            keyWordIndex++;
        }
        if (keyWordIndex == keyWordLen)
        {
            keyWordIndex = 0;
        }
        if (charIndex + 1 == originalTextLength)
        {
            printf("\n");
        }
        charIndex++;
    }
}

int caesar(char theCharacter, int shiftedValue)
{
    if (isalpha(theCharacter))
    {
        if (isupper(theCharacter))
        {
            int updatedShiftedValue = upperCaseShift(shiftedValue);
            return updatedShiftedValue;
        }
        else if(islower(theCharacter))
        {
            int updatedShiftedValue = lowerCaseShift(shiftedValue);
            return updatedShiftedValue;
        }
    }
    else
    {
        return theCharacter;
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

int argvChecker(string testString)
{
    for (int numChecker = 0, strLength = strlen(testString); numChecker < strLength; numChecker++)
    {
        int testChar = testString[numChecker];
        int testingTestChar = isalpha(testChar);
        if (testingTestChar <= 0)
        {
            return 1;
        }
        
    }
    return 0;
}