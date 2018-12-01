#ifndef Orders_LinkedQueue_h
#define Orders_LinkedQueue_h
#include <iostream>
#include <string>
using namespace std;

//Def of node

template <class Type>
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};

template <class Type>
class linkedQueueType
{
    
public:
    
    //overload assignment opperator
    
        const linkedQueueType<Type>& operator=
        (const linkedQueueType<Type>&);
    
    //fuction to see if queue is empty
    
        bool EmptyQ() const;
    
    //initialize Q
    
        void initializeQ();
    
    //returns first element on q
    
        Type frontQ();
    
    //returns last element in q
    
        Type backQ();
    
    //pushes element onto q
    
        void Push(const Type& queueElement);
    
    //remove element on q (pop)
    
       void Pop();
    
    //defult construstor
    
        linkedQueueType();
    
    //copy constructor
    
        linkedQueueType(const linkedQueueType<Type>& otherQueue);
    
    //destructor
    
        ~linkedQueueType();
    

private:
    
    //pointer to front of q
    
        nodeType<Type> *queueFront;
    
    //pointer to back of q
    
        nodeType<Type> *queueRear;
};

//deffinitions of the functions of the class linkedQueueType

//def of Emptyq

    template <class Type>
    bool linkedQueueType<Type>::EmptyQ() const
    {
        return (queueFront ==NULL);
    }

//def of initializeQ

    template <class Type>
    void linkedQueueType<Type>::initializeQ()
    {
        nodeType<Type> *temp;
        
        while(queueFront!=NULL)
        {
            temp=queueFront;
            queueFront=queueFront->link;
            delete temp;
        }
        queueRear=NULL;
    }

//def for push

    template <class Type>
    void linkedQueueType<Type>::Push(const  Type& newElement)
    {
        nodeType<Type> *newNode;
        
        //create the node
        
            newNode=new nodeType<Type>;
        
        //store the info
        
            newNode->info=newElement;
        
        //initialize the link feild to null
        
            newNode->link=NULL;
        
        //if the queue is empty
        
            if(queueFront==NULL)
            {
                queueFront=newNode;
                queueRear=newNode;
            }
        //add newNode at the end
            else
            {
                queueRear->link=newNode;
                queueRear=queueRear->link;
            }
    }

//deff of frontQ

    template<class Type>
    Type linkedQueueType<Type>::frontQ()
    {
        if(queueFront!=NULL);
        return queueFront->info;
    }

//deff of backQ

    template<class Type>
    Type linkedQueueType<Type>::backQ()
    {
        assert(queueRear!=NULL);
        return queueRear->info;
    }

//deff of pop

    template<class Type>
    void linkedQueueType<Type>::Pop()
    {
        nodeType<Type> *temp;
        if(!EmptyQ())
        {
         //make temp point to the first node
            
            temp=queueFront;
            
        //advance queueFront
            
            queueFront=queueFront->link;
            
        //delete the first node
            
            delete temp;
            
        //if after pop the queue is empty
            
            if(queueFront==NULL)
            {
            //set queueRear to null
                
                queueRear=NULL;
            }
        }
        else
            cout<<"Cannot remove, the order queue is already empty.\n";
    }

//definition of default construstor

    template<class Type>
    linkedQueueType<Type>::linkedQueueType()
    {
    //set front to null
        
        queueFront=NULL;
        
    //set rear to null
        
        queueRear=NULL;
        
    }

#endif
