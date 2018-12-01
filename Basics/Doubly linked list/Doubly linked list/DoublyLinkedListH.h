#ifndef Doubly_linked_list_DoublyLinkedListH_h
#define Doubly_linked_list_DoublyLinkedListH_h

#include <iostream>
using namespace std;

//Definition of the node

    template<class Type>
    struct node
    {
        Type num;
        node<Type> *next;
        node<Type> *back;
    
    };

//Functions

    template<class Type>
    class doublyLinkedList
    {
    
    public:
    
    //initalize the list
    
        void initalize();
    
    //determine if the list is empty
    
        bool isEmpty();
    
    //delete the list
    
        void exterminate();
    
    //print the list
    
        void print();
    
    //length of the list
    
        int length();
    
    //front of the list
    
        Type front();
    
    //back of the list
    
        Type back();
    
    //bubble sort (low to high)
    
        void iSort();
    
    //insert a node into the list
        
        void insertNode(Type& insertNum);
    
    //delete a node from the list
    
        void deleteNode();
    
    //constructor
    
        doublyLinkedList();
    
    //deconstructor
    
        ~doublyLinkedList();
    
    
    private:
        
    //variable for a count of the list
    
        int count;
    
    //pointer to first node
    
        node<Type> *first;
    
    //pointer to last node
    
        node<Type> *last;
};



//Function deffinitions

    //Default constructor

        template<class Type>
        doublyLinkedList<Type>::doublyLinkedList()
        {
            first=NULL;
            last=NULL;
            count=0;
        }

    //isEmpty def

        template<class Type>
        bool doublyLinkedList<Type>::isEmpty()
        {
            return (first==NULL);
        }

    //exterminate the list deff

        template<class Type>
        void doublyLinkedList<Type>::exterminate()
        {
            //pointer to delete the node
    
                node<Type> *temp;
    
            //loop deleteing all the nodes
    
                while (first!=NULL)
                {
                    temp=first;
                    first=first->next;
                    delete temp;
                }
    
            //set last to null and count to 0
    
                last=NULL;
                count=0;
        }

    //initilize the list deff

        template<class Type>
        void doublyLinkedList<Type>::initalize()
        {
            exterminate();
        }

    //length of list def

        template<class Type>
        int doublyLinkedList<Type>::length()
        {
            return count;
        }

    //Print list def

        template<class Type>
        void doublyLinkedList<Type>::print()
        {
            //pointer to traverse the list
    
                node<Type> *current;
    
            //set current to point to the first node
    
                current=first;
    
            //loop to output list
    
                while(current!=NULL)
                {
                    cout<<current->num<<" ";
                    current=current->next;
                }
        }

    //front of the list def

        template<class Type>
        Type doublyLinkedList<Type>::front()
        {
            assert(first!=NULL);
            return first->num;
        }

    //back of the list def

        template<class Type>
        Type doublyLinkedList<Type>::back()
        {
            assert(last!=NULL);
            return last->num;
        }

    //insert def

        template<class Type>
        void doublyLinkedList<Type>::insertNode(Type& insertNum)
        {
            //pointer to traverse the list
    
                node<Type> *current;
            
            //pointer just before current
            
                node<Type> *trailCurrent;
            
            //pointer to create a new node
    
                node<Type> *newNode;
    
            //create the new node
    
                newNode=new node<Type>;
    
            //store the new item in the node
    
                newNode->num=insertNum;
    
            //set back and next to null
    
                newNode->next=NULL;
                newNode->back=NULL;
            
            //variable for user choice
            
                int choice;
            
            //variable for user element selection
            
            int elmnt;
    
            //check to see if the list is empty
    
                if(first==NULL)
                {
                    cout<<"The list is empty, the new item will be first and last on the list.";
                    
                    //if the list is empty, the new item will be first on the list
                    
                        first=newNode;
                        last=newNode;
                        count++;
                }
                else
                {
                    //Informing user of insert options
                    
                        cout<<"Where would you like to put your item on the list? \n (1) First \n (2) Last (3) An element of your choosing \n (4) Go back ";
                        cin>>choice;
                    
                    //user choices
                    
                        switch(choice)
                        {
                        case 1:
                                first->back=newNode;
                                newNode->next=first;
                                first=newNode;
                                count++;
                                break;
                            
                        case 2:
                            {
                                if(current!=NULL)
                                {
                                    trailCurrent->next=newNode;
                                    newNode->back=trailCurrent;
                                    newNode->next=current;
                                    current->back=newNode;
                                }
                                else
                                {
                                    trailCurrent->next=newNode;
                                    newNode->back=trailCurrent;
                                    last=newNode;
                                }
                                break;
                                
                                count++;
                            }
                        case 3:
                                cout<<"What element would you like to insert your item in?";
                                cin>>elmnt;
                                for(int i=0;i<elmnt;i++)
                                {
                                    current=current->next;
                                }
                                trailCurrent->next=newNode;
                                newNode->back=trailCurrent;
                                newNode->next=current;
                                current->back=newNode;
                                current=newNode;
                                break;
                                
                        case 4:
                                return;
                                
                        }
                        
                    
                }
        }

#endif
