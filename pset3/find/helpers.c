/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

#include <stdio.h>


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int highPoint = n;
    int lowPoint = 0;
    bool pointFound = true;
    while (pointFound)
    {
        int midPoint = (lowPoint + highPoint)/2;
        
        if (value == values[midPoint])
        {
            break;
        }
        else if(value < values[midPoint])
        {
            highPoint = midPoint - 1;
        }
        else if(value > values[midPoint])
        {
            lowPoint = midPoint + 1;
        }
        if (highPoint - lowPoint < 0)
        {
            pointFound = false;
            break;
        }
    }
    return pointFound;
}


//     // TODO: implement a searching algorithm
//     for (int valCheck = 0; valCheck < n;)
//     {
//         if (values[valCheck] == value)
//         {
//             return true;
//         }
//         valCheck++;
//     }
    
//     return false;
// }

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int currentIndex = 0; currentIndex < n; currentIndex++)
    {
        int valAtIndex = values[currentIndex];
        int currentValue = values[currentIndex];
        int smallestValue = valAtIndex;
        int indexWithSmallestValue = values[currentIndex];
        for (int nextIndex = currentIndex + 1; nextIndex < n; nextIndex++)
        {
            int valAtNextIndex = values[nextIndex];
            if (smallestValue > valAtNextIndex)
            {
                smallestValue = valAtNextIndex;
                indexWithSmallestValue = nextIndex;
            }
        }
        if (valAtIndex != smallestValue)
        {
            values[currentIndex] = smallestValue;
            values[indexWithSmallestValue] = currentValue;
        }
        
    }
    return;
}
