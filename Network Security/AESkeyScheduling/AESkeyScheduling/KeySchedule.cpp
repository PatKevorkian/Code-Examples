#include "KeySchedule.h"
#include "AESConstants.h"
#include <iostream>
using namespace std;

void Expand(const unsigned char input[16], unsigned char output[16*11])
{
    unsigned int i;
    unsigned int j;
    unsigned char t[4];;
    for(i = 0; i < 16*11; i++) output[i] = input[i];
    for(i = 1; i < 11; i++)
    {
        j = i*16;
        
        t[0] = sbox[output[j-3]] ^ rcon[i];
        t[1] = sbox[output[j-2]];
        t[2] = sbox[output[j-1]];
        t[3] = sbox[output[j-4]];
        
        *(unsigned int*) (output + j) = *(unsigned int*)  (output + j - 16) ^ *(unsigned int*) t;
        
        *(unsigned int*) (output + j + 4) = *(unsigned int*) (output + j - 12) ^ *(unsigned int*) (output + j);
        

        *(unsigned int*) (output + j + 8) = *(unsigned int*) (output + j - 8) ^ *(unsigned int*) (output + j + 4);
        

        *(unsigned int*) (output + j + 12) = *(unsigned int*) (output + j - 4) ^ *(unsigned int*) (output + j + 8);

    }
}
