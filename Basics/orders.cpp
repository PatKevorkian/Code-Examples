#include <iostream>
#include <string>
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

int main()
{
//Var 

	string person; 
	Order Info;

//Set default bill to $0"

	Info.Total=0.00;

//UI

	cout<<"Are you a chef or a customer? ";
	cin>>person; 
	if(person=="customer")
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
			cout<<"Ok! Your total is: ";
			cout<<"$" <<Info.Total <<endl<<endl;
		}
		else
		{
			cout<<"Ok! Your total is: ";
			cout<<"$" <<Info.Total <<endl<<endl;
		}
	}
	else
		cout<<"Have a nice day!"; //Add chef side

//Class used as a queue 
 
class Queue

{
	public:

	void Push(Order& CurrentOrder)
	{
		Temp=new Order;
		Temp->TableNum=CurrentOrder.TableNum;
		Temp->order=CurrentOrder.order;
		Temp->name=CurrentOrder.name;
		Temp->PayType=CurrentOrder.PayType;
		Temp->CCnum=CurrentOrder.CCnum;
		Temp->ExDate=CurrentOrder.ExDate;
		Temp->CVC=CurrentOrder.CVC;
		Temp->Total=CurrentOrder.Total;
		Temp->ptr=rear;
		rear=Temp;
	}

	bool isEmptyQ() 	
	{

	}

	void Q() 
	{
		rear=NULL;
		Temp=NULL;
	}

	Order Front() 
	{

	}

	Order back() 
	{

	}

	private:

	Order *rear, *Temp;

};

system("pause");
return 0;
}




