/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 #include <stdbool.h>

typedef uint8_t BYTE;
char fileName[8];

int main()
{
    
    FILE* intpr = fopen("card.raw", "rb");
    FILE* outpr;
    
    BYTE buffer[512];
    int jpgsFound = 0;
    bool jpgIsReadyToWrite = false;
    
    if (intpr == NULL)
    {
        printf("could not open file\n");
        return 1;
    }
    
    while (true)
    {

        fread(&buffer, sizeof(BYTE), 512, intpr);
        
        if (feof(intpr))
        {
            break;
        }
        
        if((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            if (jpgsFound == 0)
            {
                sprintf(fileName, "%03d.jpg", jpgsFound);
                outpr = fopen(fileName, "w");
                jpgIsReadyToWrite = true;
                jpgsFound++;
            }
            else
            {
                fclose(outpr);
                sprintf(fileName, "%03d.jpg", jpgsFound);
                outpr = fopen(fileName, "w");
                jpgsFound++;
            }
            
        }
        
        if (jpgIsReadyToWrite == true)
        {
            fwrite(&buffer, sizeof(BYTE), 512, outpr);
        }
    }
    
    fclose(intpr);
    fclose(outpr);
        
    return 0;
    
}
