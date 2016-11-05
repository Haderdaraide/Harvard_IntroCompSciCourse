#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("How long do you shower on average?: \n");
    int ShowerLength = GetInt();
    int BottlesOfWaterPerMin = 12;
    int NumOfBottlesUsedForShower = ShowerLength * BottlesOfWaterPerMin;
    printf("minutes: %i\nbottles: %i\n", ShowerLength, NumOfBottlesUsedForShower);
    
}
