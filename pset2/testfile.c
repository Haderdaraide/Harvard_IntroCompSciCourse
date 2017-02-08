#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// int main(void)
// {
//     // printf("this is a test\n");
//     // char character = ' ';
//     // printf("%d\n", isspace(character));
//     // int ASCIIvalue = 'a';
//     // int shiftedValue = ASCIIvalue + 1;
//     // // int newLetter = ("%d", shiftedValue);
//     // char newLetter = ("%c", shiftedValue);
//     // printf("%c is the new letter and it's value is %d\n", shiftedValue, shiftedValue);
//     // printf("the new letter is: %c", newLetter);
//     string theTestWord = "h2llo\n";
//     int newTestWord;
//     newTestWord = atoi(theTestWord);
//     printf("%d\n", newTestWord);
//     int testCharacter = theTestWord[1];
//     int testerCharacter = isdigit(testCharacter);
//     printf("%d\n", testerCharacter);
    
// }

int upperCaseShift(int shiftedValue);

int lowerCaseShift(int shiftedValue);

int argvChecker(string testString);

int caesar(char theCharacter, int shiftedValue));

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
    int LowerAlphabetEnd = 122;
    int UpperAlphabetEnd = 90;
    
    for (int charIndex = 0, originalTextLength = strlen(originalText); charIndex < originalTextLength;)
    {
        if (keyWordIndex > keyWordLen)
        {
            keyWordIndex = 0;
        }
        char theCharacter = originalText[charIndex];
        char theKeyCharacter = keyWord[keyWordIndex];
        int keyCharASCIIValue = keyWord[keyWordIndex];
        int CharASCIIValue = theCharacter;
        
        if (isupper(theKeyCharacter))
        {
            int shiftedValue = UpperAlphabetEnd % keyCharASCIIValue;
            shiftedValue = shiftedValue + CharASCIIValue;
        }
        if (islower(theKeyCharacter))
        {
            int shiftedValue = LowerAlphabetEnd % keyCharASCIIValue;
            shiftedValue = shiftedValue + CharASCIIValue;
        }
        if (isalpha(theCharacter))
        {
            keyWordIndex++;
        }

        int updatedShiftedValue = caesar(theCharacter, shiftedValue);
        printf("%c", updatedShiftedValue);
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