#include <iostream>
#include "DoublyLinkedListH.h"
using namespace std;
int main()
{
    
    node<int> x;

    doublyLinkedList<int> list;
    
    cout<<"input item";
    cin>>x.num;
    list.insertNode(x.num);
    list.print();
    return 0;
}
