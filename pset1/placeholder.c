#include <stdio.h>
#include <cs50.h>
#include <math.h>


int GetChange(void)
{
    float changeDue = -1.00;
    int totalChange = 0;
    while (0 > changeDue)
    {
        printf("How much change is owed?: ");
        changeDue = GetFloat();
    }
    changeDue = roundf(changeDue * 100) / 100; 
    while (changeDue >= 0.00)
    {
        if (changeDue > 1.00)
        {
            changeDue = changeDue - 1.00;
            totalChange = totalChange + 100;
        }
        else
        {
            totalChange = totalChange + changeDue * 100;
            break;
        }
    }
    return totalChange;
    
}

int main(void)
{
    int totalChange = GetChange();
    int totalNumOfCoins = 0;
    while (totalChange > 0)
    {
        if (totalChange >= 100)
        {
            totalNumOfCoins = totalNumOfCoins + 4;
            totalChange = totalChange - 100;
        }
        else if(25 <= totalChange)
        {
            totalNumOfCoins = totalNumOfCoins + 1;
            totalChange = totalChange - 25;
        }
        else if(10 <= totalChange)
        {
            totalNumOfCoins = totalNumOfCoins + 1;
            totalChange = totalChange - 10;
        }
        else if(5 <= totalChange)
        {
            totalNumOfCoins = totalNumOfCoins + 1;
            totalChange = totalChange - 5;
        }
        else if(0 < totalChange)
        {
            totalNumOfCoins = totalNumOfCoins + totalChange;
            totalChange = totalChange - totalChange;
        }
        
    }
    printf("%i\n", totalNumOfCoins);
}