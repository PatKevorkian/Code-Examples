#include <iostream>
#include <string>
using namespace std;
int fib(int);

int main()
{
    
//Variables
    
    int num1, **board,**p, rows=0, columns=0;

//Inform user of function
    
    cout<<"Enter the number of Fibonacci Sequences you want to see: ";
    
//User input
    
    cin>>num1;
    while(num1<0)
    {
        cout<<"Not a valid number, please choose another:\n";
        cin>>num1;
    }
//create dynamic 2D array
    
    //Create the rows of board
    
        board=new int* [rows];
    
    //create the columns of board
    
        for(int row=0;row<rows;row++)
            board[row]=new int[columns];
    
    
//filling array
    
    for(int row=0;row<rows;row++)
    {
        for(int col=0;col<columns;col++)
            board[row][col]=fib(col);
    }
    
    

    cout<<p[0][0];
    
//program exit
    
    cout<<endl;
    system("pause");
    return 0;
}

//Fib function

int fib(int num)
{
    if (num < 2)
        return num;
    else
        return fib(num-1) + fib(num-2);
}