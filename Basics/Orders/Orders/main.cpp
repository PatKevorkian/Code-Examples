#include <iostream>
#include <string>
#include "LinkedQueue.h"
using namespace std;

////Structure for customer info
//
//struct Order
//
//{
//    string TableNum;
//    string order;
//    string name;
//    string PayType;
//    string CCnum;
//    string ExDate;
//    string CVC;
//    float Total;
//};
//
//
////Global Var
//Order Info;
int main()
{
    
    linkedQueueType<int> queue;
    queue.initializeQ();
    int x=4;
    int y=5;
    
////Set default bill to $0"
//    
//    Info.Total=0.00;
//    
////cin test
//    
//    cout<<"Enter info:";
//    cin>>Info.TableNum;
//    cin>>Info.order;
//    cin>>Info.name;
//    cin>>Info.PayType;
//    cin>>Info.CCnum;
//    cin>>Info.CVC;
//    cin>>Info.Total;
    
//push structure onto queue
    
    queue.Push(x);
    queue.Push(y);
    
//cout test
    
    while(!queue.EmptyQ())
    {
        cout<<queue.frontQ();
        queue.Pop();
    }
    
    system("pause");
    return 0;
}


