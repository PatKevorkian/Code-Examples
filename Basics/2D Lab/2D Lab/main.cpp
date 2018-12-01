//Housekeeping
#include <iostream>
#include <fstream>
using namespace std;
int main()
{
//Declare vairables
    
    //int NumList[10][11];
    ifstream infile;
    int i=0,j=0,cnt=0,num;
    int NumList[10][11];
   
    
//Prompt user
    
    cout<<"Search for a number in the file:\n\n Number: ";
    cin>>num;

//Open file
    
    infile.open("//Users//PatrickKevorkian//Desktop//search.txt");
    if(!infile)
    {
        cout<<"file not found!";
        return 1;
    }

//Load File into Array
    
    for(j=0;j<11;j++)
    {
        for(i=0;i<10;i++)
          infile>>NumList[i][j];
    }
    
    
    for(j=0;j<10;j++)
    {
        cout<<"\n";
        for(i=0;i<11;i++)
            cout<<NumList[i][j]<<" ";
    }
    
//Search
    
    for(j=0;j<11;j++)
    {
        for(i=0;i<10;i++)
            if(NumList[i][j]==num);
                cout<<"\n\nThe Number "<<num<<" is present in the file.";
    }
    return 0;
}

