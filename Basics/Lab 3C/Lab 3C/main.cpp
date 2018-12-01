//*******************************************************************
//*  Programmer: Patrick kevorkian                                  *
//*  CSC 126 – xxxx                Instructor: Frederick E. Johnson *
//*  Date:  22 Feb 2013                                             *
//*                            Lab 3C                               *
//*                                                                 *
//*  Write a program that has the user enter a number and then      *
//*  displays a comment to the screen indicating whether the value  *
//*  is EVEN or ODD.                                                *
//*                                                                 *
//*  EXAMPLE:  If the user entered 300 then the output would be     *
//*                                      300 is an even #           *
//*                                                                 *
//*         or If the user entered 41 then the output would be      *
//*                                      41 is an odd #             *
//*                                                                 *
//*******************************************************************


#include <iostream>
using namespace std;
int main()
{

//Declaration of variables
    
    int num, remain;
    
//User input
    
    cout<<"Enter a number to see if it's even or odd: ";
    cin>>num;
    
//Calculations
    
    remain=num%2;
    
//Conditions
    
    if(remain==0)
        cout<<"Your number ("<<num<<") is an Even #."; //Output 
    else
        cout<<"Your number ("<<num<<") is an Odd #."; //Output
    

return 0;
}

