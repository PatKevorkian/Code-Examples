//*******************************************************************
//*  Programmer: Patrick Kevorkian                                  *
//*  CSC 126 – xxxx                Instructor: Frederick E. Johnson *
//*  Date:  22 Feb 2013                                             *
//*                            Lab 3D                               *
//*                                                                 *
//*  Write a program that has the user enter four test scores.      *
//*  Calculate the average and the grade in the course according    *
//*  to the following schedule and based on the test average:       *
//*                       A  - 90 or above                          *
//*                       B  - 80 or above but lower than 90        *
//*                       C  - 70 or above but lower than 80        *
//*                       D  - 60 or above but lower than 70        *
//*                       F  - below 60                             *
//*                                                                 *
//*  EXAMPLE:  If the user entered 90  100  70  80                  *
//*               then the output would be:  Average: 85.0          *
//*                                            Grade: B             *
//*                                                                 *
//*         or If the user entered 82  78  68  83                   *
//*               then the output would be:  Average: 77.8          *
//*                                            Grade: C             *
//*******************************************************************

#include <iostream>
using namespace std;
int main()
{

//Declaration of Variables
    
    double t1,t2,t3,t4,ave;
    char grade;
    
//User input
    
    cout<<"Please enter 4 test grades to recieve Averge and Grade: \n\n Test 1: ";
    cin>>t1;
    cout<<" Test 2: ";
    cin>>t2;
    cout<<" Test 3: ";
    cin>>t3;
    cout<<" Test 4: ";
    cin>>t4;
    
//Calculations
    
    ave=((t1+t2+t3+t4)/4.0);

//Conditions to determine letter grade
    
    if(ave>=90)
        grade='A';
    if(ave>=80 && ave<90)
        grade='B';
    if(ave>=70 && ave<80)
        grade='C';
    if(ave>=60 && ave<70)
        grade='D';
    if(ave<60)
        grade='F';
    
//Output
    
    cout<<endl<<"Average: "<<ave<<"\n  Grade: "<<grade<<endl;
    
    return 0;
}

