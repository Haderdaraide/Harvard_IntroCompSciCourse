#include <stdio.h>
#include <stdlib.h>

int main()
{
    int testNum = 1110000;
    unsigned pushedTestNum = (testNum >> 4) & testNum;
    unsigned hexaNumber = 0xef;
    int jpgTestNumber = 125;
    
    if (hexaNumber == 239)
    {
        printf("The hexaNumber is the same!\n");
    }
    
    if (testNum >> 1 == 1110)
    {
        printf("The shift works!\n");
    }
    else
    {
        printf("The shift didn't work =(\n");
    }
    
    printf("this is the pushed testNum: %i\n", pushedTestNum);
    printf("this is the original testNum: %i\n", testNum);
    printf("this is the hexaNumber: %i\n", hexaNumber);
    testNum++;
    printf("this is it incremented by 1: %i\n", testNum);
    printf("this is the jpgTestNum: %03d.jpg\n", jpgTestNumber);
    printf("this is the jpgTestNum without the padded 0s: %d.jpg\n", jpgTestNumber);
    return 0;
}