#include <iostream>
#include <string>
using namespace std;
int main()
{
 
//Declare Variables
    
    int i=0;
    char lttr[5];
    double g1,g2,g3,g4,g5,add,avg1,avg2,avg3,avg4,avg5,avg[5];
    string name[5];
    
//Prompt user
    
    cout<<"Enter 5 students names and their grades to recieve an average and letter grade. \n\n       Names: ";
    
//Array created to enter student names
    
    for(i=0;i<5;i++)
    {   cin>>name[i];
        cout<<"              ";
    }
    
//Promt user to enter grades for each student
    
    cout<<"\nEnter 5 grades for each student in the order typed above.\n\n      Grades: ";
    
//User enters 5 grades for each student and add the mtogether 
      
    cout<<"\n\n          "<<name[0]<<": ";
    for(i=0;i<5;i++)
    {   cin>>add;
        cout<<"             ";
        g1=add+g1;
    }
    add=0;
    cout<<"\n\n          "<<name[1]<<": ";
    for(i=0;i<5;i++)
    {   cin>>add;
        cout<<"                 ";
        g2=add+g2;
    }
    add=0;
    cout<<"\n          "<<name[2]<<": ";
    for(i=0;i<5;i++)
    {   cin>>add;
        cout<<"                ";
        g3=add+g3;
    }
    add=0;
    cout<<"\n          "<<name[3]<<": ";
    for(i=0;i<5;i++)
    {   cin>>add;
        cout<<"               ";
        g4=add+g4;
    }
    add=0;
    cout<<"\n          "<<name[4]<<": ";
    for(i=0;i<5;i++)
    {   cin>>add;
        cout<<"                ";
        g5=add+g5;
    }

//Calculate average
    
    avg1=g1/5;
    avg2=g2/5;
    avg3=g3/5;
    avg4=g4/5;
    avg5=g5/5;
    
//Put average of each student into an array
    
    
    avg[0]=avg1;
    avg[1]=avg2;
    avg[2]=avg3;
    avg[3]=avg4;
    avg[4]=avg5;
    
//Determine Letter grade for average
    
    
return 0;
    
}
