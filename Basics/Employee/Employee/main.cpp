//Housekeeping
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct EmployeeType //Struct to group data types
{	string name;
	string emplID;
	string Address;
	string city;
	string state;
	string zip;
	string phone;
	string location;
	int salary;
	int sales;
};

EmployeeType Emptemp;

void SelectionSort(EmployeeType list[], int length);

int main()
{
    //Declare Vairiables
    
	ifstream infile;
	EmployeeType employees[50];
	int i=0;
	
    //Inform user of the programms function
    
	cout<<"This program will display all employee info from a file \nand calculate their bonus.\n\n";
    
    //Open File (TextFile1.txt)
    
	infile.open("/Users/PatrickKevorkian/Desktop/TextFile1.txt");
    if(!infile)
    {
        cout<<"File not found!";
        return 1; //If the file used isnt found, the program ends
    }
    
    //Load file into Stuct array
    
	for (i=0;i<5;i++)
	{
		infile>>employees[i].name
        >>employees[i].emplID
        >>employees[i].Address
        >>employees[i].city
        >>employees[i].state
        >>employees[i].zip
        >>employees[i].phone
        >>employees[i].location
        >>employees[i].salary
        >>employees[i].sales;
	}
    
    //Sort file for first three highest slalaries
    
	SelectionSort (employees, 50);
    
	for(i=0;i<5;i++)
	{
        cout<<employees[i].name<<endl
        <<employees[i].emplID<<endl
        <<employees[i].Address<<endl
        <<employees[i].city<<endl
        <<employees[i].state<<endl
        <<employees[i].zip<<endl
        <<employees[i].phone<<endl
        <<employees[i].location<<endl
        <<employees[i].salary<<endl
        <<employees[i].sales<<endl<<endl;
	}
    
   
    return 0;
}//End of main

//function to sort employee structure

void SelectionSort(EmployeeType list[], int length)
{
	int index=0, largestIndex=0, location=1;
    
    for(index=0; index < length-1; index++)
	{
		largestIndex=index;
		
		for(location=index+1; location < length; location++)
			if(list[largestIndex].sales < list[location].sales )
			{
				largestIndex=location;
				Emptemp=list[largestIndex];
				list[largestIndex]=list[index];
				list[index]=Emptemp;
			}
	}
}

