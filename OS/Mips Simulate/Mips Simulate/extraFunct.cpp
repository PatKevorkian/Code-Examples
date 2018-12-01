
#include "extraFunct.h"

//convers char array to a decimal number
int ToDecimal (char bit[], int length)
{
    int decimal = 0;
    for (int i=0; i<length; i++)
    {
        if (bit[i]== '1')
            decimal += (int)pow((float)2,length-1-i);
    }
    return decimal;
};

//calculates the complement of a binary string in a char array
void Complement(char binaryString[])
{
    char zero = '0';
    char one ='1';
    int numBits=16;
    
    //iterates through all the characters
    for(int i = 0; i < numBits; i++) //iterates through all the characters
    {
        // changes value if character == '1'
        if( binaryString[i] == one)
        {
            binaryString[i]= zero;
        }
        
        else
        {
            // changes value is character doesn't == '1' assuming user only input '0's and '1's
            binaryString[i]= one;
        }
        

    }
    return;
}
