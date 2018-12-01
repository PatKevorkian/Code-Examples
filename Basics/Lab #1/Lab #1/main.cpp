//Houskeeping

#include <iostream>
using namespace std;
int main()
{
//Declare Vairables
    
    int i=0,j=0,arry[5][6];

//Prompt user
    
    cout<<"Enter 30 numbers into 2D array by column and see there output by row \n\n Numbers: ";
    
//Input
    
    for(j=0;j<6;j++)
    {
    for(i=0;i<5;i++)
        cin>>arry[i][j];
    }
    
//Show output:
    
    for(i=0;i<6;i++)
    {
        cout<<"\n";
        for(j=0;j<5;j++)
            cout<<arry[i][j]<<" ";
    }
    
    
    system("PAUSE");
    return 0;
}

