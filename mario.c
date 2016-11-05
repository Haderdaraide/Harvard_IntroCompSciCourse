#include <stdio.h>
#include <cs50.h>

int GetHeight(void)
{
    int height = -1;
    while (0 > height || height > 23) {
        printf("What is the half-pyramid height? Please enter a positive number no more then 23: ");
        height = GetInt();
    }
    return height;
}

int main(void)
{
    int HeightOfPyramid = GetHeight();
    int SpacingNeeded = HeightOfPyramid - 1;
    for (int row = 1; row <= HeightOfPyramid; row++)
    {
        for (int spaces = 1; spaces <= SpacingNeeded; spaces++)
        {
            printf(" ");
            // printf("%i\n", spaces);
        }
        printf("#");
        for(int hashSigns = 0; hashSigns < row; hashSigns++)
        {
            printf("#");
        } 
        SpacingNeeded = SpacingNeeded - 1;
        printf("\n");
    }
    
    return(0);
    
}
