#include <iostream>
#include <string>
using namespace std;
int fib(int);

int main()
{
    
//Variables
    
    string choice;
    int *sequence1, *sequence2, *sequence3;
    int number1, number2, number3;

//Inform user of function
    
    cout<<"Enter how many numbers in the Fibonacci Sequence you want to see (You will be able to save up to 3 sequences at once.): ";

//User input
    
        cin>>number1;
    while(number1<0){
        cout<<"Number not valid, please choose another:\n";
        cin>>number1;
    }
    
    sequence1 = new int [number1];
    
    for(int i=0;i<number1;i++)
    {
        cout<<fib(i)<<" ";
        sequence1[i]=fib(i);
    }
    
    cout<<"\nDo you want to create a new Fibonaci Sequence? (Yes/No): ";
    cin>>choice;
    if(choice=="Yes")
    {
        sequence2 = new int [number1];
        cout<<"\tAnother Sequence may now be created.";
    }
    else
    {
        delete []sequence1;
        return 0;
    }
    cout<<"\nDo you want to display all previous Sequences? (Yes/No): ";
    cin>>choice;
    if(choice=="Yes")
    {
        for(int i=0; i<number1;i++)
        {
            cout<<sequence1[i]<<" ";
        }
    }
    
    cout<<"\nEnter how many numbers in the Fibonacci Sequence you want to see: ";
    cin>>number2;
    while(number2<0)
    {
        cout<<"Number not valid, please choose another:\n";
        cin>>number2;
    }
    for(int i=0;i<number2;i++)
    {
        cout<<fib(i)<<" ";
        sequence2[i]=fib(i);
    }
    
    cout<<"\nDo you want to create a new Fibonaci Sequence? (Yes/No): ";
    cin>>choice;
    if(choice=="Yes")
    {
        sequence3 = new int [number2];
        cout<<"\tAnother Sequence has been created!";
    }
    else
    {
        delete []sequence1;
        delete []sequence2;
        return 0;
    }
    cout<<"\nDo you want to display all previous Sequences? (Yes/No): ";
    cin>>choice;
    if(choice=="Yes")
    {
        for(int i=0; i<number1;i++)
        {
            cout<<sequence1[i]<<" ";
        }
        cout<<endl;
        for(int i=0; i<number2;i++)
        {
            cout<<sequence2[i]<<" ";
        }
    }
    
    cout<<"\nEnter how many numbers in the Fibonacci Sequence you want to see: ";
    cin>>number3;
    while(number3<0)
    {
        cout<<"Number not valid, please choose another:\n";
        cin>>number3;
    }
    for(int i=0;i<number3;i++)
    {
        cout<<fib(i)<<" ";
        sequence3[i]=fib(i);
    }
    
    cout<<"\nMax amount of sequences have been saved.\n";
    
    
 //Final Output
    
    cout<<"\nDo you want to display all previous Sequences? (Yes/No): ";
    cin>>choice;
    if(choice=="Yes")
    {
        for(int i=0; i<number1;i++)
        {
            cout<<sequence1[i]<<" ";
        }
        cout<<endl;
        for(int i=0; i<number2;i++)
        {
            cout<<sequence2[i]<<" ";
        }
        cout<<endl;
        for(int i=0; i<number3;i++)
        {
            cout<<sequence3[i]<<" ";
        }
    }

//Deleteing dynamic memeory
    
    delete []sequence1;
    delete []sequence2;
    delete []sequence3;

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