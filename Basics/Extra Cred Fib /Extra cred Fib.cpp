#include <iostream>
#include <string>
using namespace std;
int fib(int);

int main(){
    
//Variables
    
    int *Ary1, num, i=0;
    
//Inform user of function
    
    cout<<"Enter the number the Fibonacci Sequence you want to see: ";

//User input
    
    cin>>num;
    while(num<0){
        cout<<"That is not a valid number!\n";
        cin>>num;
    }

//Create dynamic storage
    
    Ary1 = new int [num];
    
//Store sequence in array
    
    for(i=0;i<num;i++)
        Ary1[i]=fib(i);
    
//Output
    
    for(i=0;i<num;i++)
        cout<<Ary1[i] <<" ";
        cout <<endl;
    

    system("pause");
    return 0;
}

//Fib calculation function

int fib(int number){
    if (number < 2)
        return number;
    else
        return fib(number-1) + fib(number-2);
}