#include <iostream>
using namespace std;
int main()
{
    //*******************************************************************
    //*  Programmer: Patrick Kevorkian                                  *
    //*  CSC 126 – xxxx                Instructor: Frederick E. Johnson *
    //*  Date: 19 Feb 2013                                              *
    //*                            Lab 2C                               *
    //*                                                                 *
    //*  Write a C++ program that has the user enter two numbers and    *
    //*  then calculates the first number divided by the second AND     *
    //*                  the second number divided by the first.        *
    //*                                                                 *
    //*  The answer for each is displayed as both a decimal and as a    *
    //*  mixed number (fractional form).                                *
    //*                                                                 *
    //*  EXAMPLE: If the user entered 21 and 5 then the output would be *
    //*                                                                 *
    //*                         21/5 = 4.2 = 4 1/5                      *
    //*                                                                 *
    //*                         5/21 = 0.238095 = 0 5/21                *
    //*                                                                 *
    //*******************************************************************
    
    
        //input
        
        double a,b,c,d;
        int e,f,g,h;
        
        cout<<"Please enter two numbers:";
        cin>>a;
        cout<<"And:";
        cin>>b;
        cout<<endl;
    
        //calculations
        
        c=a/b;
        d=b/a;
        e=a/b;
        f=int(a)%int(b);
        g=b/a;
        h=int(b)%int(a);
        
        //output
        
        cout<<"First number divided by the second:\n\n";
        cout<<"     "<<a<<"/"<<b<<" = "<<c<<" = "<<e<<" "<<f<<"/"<<b<<endl<<endl;
        
        cout<<"Second number divided by the first:\n\n";
        cout<<"     "<<b<<"/"<<a<<" = "<<d<<" = "<<g<<" "<<h<<"/"<<a<<endl<<endl;
        return 0;
    }

