#include <iostream>
#include "KeySchedule.h"
using namespace std;

int main()
{
    //2B 7E 15 16 28 AE D2 A6 AB F7 15 88 09 CF 4F 3C in decimal is used as the test vector
    unsigned char testvector[16] = {43, 126, 21, 22, 40, 174, 210, 166, 171, 247, 21, 136, 9, 207, 79, 60};
    //expanded key
    unsigned char expanded[176];
    Expand(testvector, expanded);
    int kCount = 0;
    
    //cout <<"Size of: "<< sizeof(unsigned int) << endl;
    cout << std::hex << endl;
    cout<<"Round keys: "<<endl;
    
        for(int i = 0; i < 176; i++)
        {
            if (i%4 == 0 )
                cout<<"  ";
            if (i%16 == 0)
            {
                cout<<endl<<"k ["<<kCount<<"] =  ";
                kCount++;
            }
           
            cout << (unsigned int)expanded[i] << " ";
           
        }
   
    cout <<endl<<endl;
}


