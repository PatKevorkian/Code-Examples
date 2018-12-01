#include <iostream>
#include <fstream>
using namespace std;
int main()
{
//Declare Vairables
    
    int i=0, j=0;
    char arry1[1], arry2[1];
    ifstream datain;
    
//Prompt user
    
    cout<<"The sum of the two hexidecimal numbers in the file will be calculated: \n\n";
    
//Open file
    
    datain.open("Hex.txt");
    if(!datain)
    {
        cout<<"File not found";
        return 1;
    }
    
    
    
    return 0;
}

