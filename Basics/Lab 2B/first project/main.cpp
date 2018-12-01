//
//  main.cpp
//  first project
//
//  Created by Pat Kevorkian on 2/14/13.
//  Copyright (c) 2013 Pat Kevorkian. All rights reserved.
//

#include<iostream>
using namespace std;

int main()
{
	int a,b,c,d,e,f,g,h,i,j,k;
    cout<<"Please enter a number:";
	cin>>a;
	cout<<"Another:";
	cin>>b;
	cout<<"Another:";
	cin>>c;
	cout<<"Another:";
	cin>>d;
	cout<<"Thank you!"<<endl<<endl;
    
    //PREFORM CALCULATIONS
    
    //Square each number entered
    e=a*a,f=b*b,g=c*c,h=d*d;
    
    //Subtract the foutrh number from the second
	i=d-b;
    
    //Mult the third num and the sum of the other 3
	j=c*(a+b+d);
    
    //Subtracts the sum of the 1st & 4th from the product of the 2nd & 3rd
	k=(b*c)-(a+d);
    
    //ANSWERS 
    cout<<"The Square of each number:"<<endl<<endl<<a<<"^2="<<e<<endl<<b<<"^2="<<f<<endl<<c<<"^2="<<g<<endl<<d<<"^2="<<h<<endl<<endl;
    cout<<"The fourth number subtracted from the Second:"<<endl<<endl<<d<<"-"<<b<<"="<<i<<endl<<endl;
    cout<<"The third number multiplied by the sum of the other three numbers:"<<endl<<endl<<c<<"("<<a<<"+"<<b<<"+"<<d<<")="<<j<<endl<<endl;
    cout<<"Subtracts the sum of the 1st & 4th from the product of the 2nd & 3rd:"<<endl<<endl<<"("<<b<<"*"<<c<<")"<<"-("<<a<<"+"<<d<<")="<<k<<endl<<endl;
    
    return 0;
}

