#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main()
{
    // int testArray[5];
    // int sizeOfArray = sizeof(testArray);
    // printf("the size of the array is: %i\n", sizeOfArray);
    // if (sizeOfArray > 0)
    // {
    //     printf("it's bigger then 0");
    // }
    // else
    // {
    //     printf("it's not bigger then 0");
    // }
    // for (int i = 0; i > sizeof(testArray); i++)
    // {
    //     testArray[i] = 1;
    //     printf("%i", testArray[i]);
    // }
    // printf("the size of the array is: %i\n", sizeOfArray);
    // return 0;
    
    int board[3][3];
    
    for (int Row = 0; Row < 3; Row++)
    {
        for (int Column = 0; Column < 3; Column++)
        {
            printf("%i\t", board[Row][Column]);
        }
    }
    
    return 0;
}