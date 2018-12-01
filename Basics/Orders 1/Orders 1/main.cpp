#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

//Structure for customer info

struct Order

{
    string TableNum;
    string order;
    string name;
    string PayType;
    string CCnum;
    string ExDate;
    string CVC;
    float Total;
    Order *ptr;
};
//Global Var
char person;
Order Info;
void Ui();
int main()
{
    
    //Call Ui
    
    Ui();
    
    //Set default bill to $0"
    
    Info.Total=0.00;
    
    //Class used as a queue
    
    class Queue
    
    {
    public:
        
   Queue* BuildList()
        {
            
        }
    private:
        
        Queue *first, *newNode, *last;
        
    };
    
    system("pause");
    return 0;
}

//UI
void Ui()
{
    cout<<"Are you: (A), a Customer or (B), a Chef? \n     (Type anything else to exit) \n>";
    cin>>person;
    
    switch (person)
    {
            
        case 'A':
        {
            cout<<"\nPlese enter your Order/Payment information: \n Table #: ";
            cin>>Info.TableNum;
            cout<<"Item/ Order: ";
            cin>>Info.order;
            cout<<"Name: ";
            cin>>Info.name;
            cout<<"Enter payment type (Cash/Credit): ";
            cin>>Info.PayType;
            if(Info.PayType=="Credit")
            {
                cout<<"Enter Credit Card Number: ";
                cin>>Info.CCnum;
                cout<<"Enter expiration date: ";
                cin>>Info.ExDate;
                cout<<"Enter Secrity code (CVC number) on back of card: ";
                cin>>Info.CVC;
                cout<<"\nOk! Your total is: ";
                cout<<"$" <<Info.Total <<" Thank you, have a nice day!"<<endl<<endl;
                system("CLS");
                Ui();
            }
            else
            {
                cout<<"\nOk! Your total is: ";
                cout<<"$" <<Info.Total <<" Thank you, have a nice day!"<<endl<<endl;
                system("CLS");
                Ui();
            }
            
            break;
        }
        case 'B':
        {
            cout<<"Chef";
            system("CLS");
            Ui();
        }
            break;
            
        default:
        {
            system("CLS");
            cout<<"Goodbye.\n";
            return;
            
        }
    }
}