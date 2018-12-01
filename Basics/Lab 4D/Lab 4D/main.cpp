
//*******************************************************************
//*  Programmer: Patrick Kevorkian *
//*  CSC 126 – xxxx                Instructor: Frederick E. Johnson *
//*  Date:  5 Mar 2013                                              *
//*                            Lab 4D                               *
//*                                                                 *
//*  Write a C++ program that allows a person to keep entering      *
//*  numbers.  When the user enters the value 999, three averages   *
//*  of the numbers (not including 999) will be displayed to the    *
//*  nearest tenth.  The averages will be the REGULAR AVERAGE,      *
//*  AVERAGE WITH LOWEST DROPPED and AVERAGE WHERE HIGHEST COUNTS   *
//*  TWICE.  (Please label all output accordingly).                 *
//*                                                                 *
//*  EXAMPLE:  If the user entered the #’s: 90,78,82,and 999        *
//*            the output would be                                  *
//*               AVERAGE = 250/3 = 83.3                            *
//*               AVERAGE WITH LOWEST DROPPED = 172/2 = 86.0        *
//*               AVERAGE WHERE HIGHEST COUNTS TWICE = 340/4 = 85.0 *
//*                                                                 *
//*       OR  If the user entered the #’s: 90,88,100,99 and 999     *
//*            the output would be                                  *
//*               AVERAGE = 377/4 = 94.3                            *
//*               AVERAGE WITH LOWEST DROPPED = 289/3 = 96.3        *
//*               AVERAGE WHERE HIGHEST COUNTS TWICE = 477/5 = 95.4 *
//*                                                                 *
//*******************************************************************

#include <iostream>
#include <iomanip> 
using namespace std;
int main()
{
    
//Declaration of Variables
    
    int num, sum, amt, big, smal,sumb,suml;
    double ave, avel, aveh;
    
//Priming Input
    
    cout<<"Enter test grade to recieve: Average, average with lowest dropped, and average with higest grade counting twice (Enter 999 to stop) \n\n  First test: ";
    cin>>num;
    
//Initilize Accumulators
    
    sum=0;
    amt=0;
    big=0;
    smal=0;
    
//Loop to get other grades
    
    do
     {   //Top of do while
         
         sum+=num;
         amt++;
         
    //High and Low number detrminates 
         
         if(num>big)
             big=num;
         if(num<)
             smal=num;
         
    //Pumping input
         
         cout<<"Another Test: ";
         cin>>num;
         
     }   //Bottom of do while
    
    while(num!=999);
    
//Calculations
    
    sumb=sum+big;
    suml=sum-smal;
    ave=sum/amt;
    aveh=(sumb)/(amt+1);
    avel=(suml)/(amt-1);
    
//Output
    
    cout<<fixed<<showpoint;
    cout<<setprecision(1);
    cout<<"\n\n\tAverage: "<<sum<<"/"<<amt<<"= "<<ave;
    cout<<"\n\tAverage with lowest dropped: "<<suml<<"/"<<amt-1<<"= "<<avel;
    cout<<"\n\tAverage with highest counting twice: "<<sumb<<"/"<<amt+1<<"= "<<aveh;
    
    
        return 0;
}