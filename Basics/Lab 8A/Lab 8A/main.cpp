//*******************************************************************
//*  Programmer: Patrick Kevorkian *
//*  CSC 126 – xxxx                Instructor: Frederick E. Johnson *
//*  Date: 23 April 2013                                            *
//*                            Lab 8A                               *
//*                                                                 *
//*  Write a program that reads in the “data8B.txt” file.  The data *
//*  should be loaded into an array and the numbers should display  *
//*  on the screen as they are read in.                             *
//*                                                                 *
//*  EXAMPLE:  If the data file            Then the display         *
//*            had the following           screen would be          *
//*            values:                     as follows:              *
//*                     3                                           *
//*                     2                 3 2 17 0 6 24 8 13        *
//*                     17                                          *
//*                     0                                           *
//*                     6                                           *
//*                     24                                          *
//*                     8                                           *
//*                     13                                          *
//*                                                                 *
//*   Now create a function that displays a menu of choices and     *
//*   prompts the user to indicate the desired task.                *
//*                                                                 *
//*  EXAMPLE:  Please indicate what action is desired:              *
//*               <1> To add the #’s                                *
//*               <2> To find the largest #                         *
//*               <3> To find the smallest #                        *
//*               <4> To exit program                               *
//*                                                                 *
//*   The function should return the choice back to main where a    *
//*   “switch” structure performs the task and displays the result. *
//*                                                                 *
//*******************************************************************

# include <iostream>
# include <fstream>
using namespace std;
int menu();
int main()
{
    
// Declaration of variables
    
	int amt=0,i=0,sum=0,x, num, arry[50];
	ifstream file;
        
// Retrevial of data file
    
	file.open("//Users//PatrickKevorkian/Desktop//Lab 8A.txt");
    if(!file)
    {
        cout<<"File not found";
        return 1;
    }
    
// Load Text into Array
    
    file>>num;           //priming input
    while (!file.eof())
    {
        arry[amt]=num;
        amt++;
        file>>num;      //pumping input
    }
    
    
// Display all numbers
    
    for(i=0;i<amt;i++)
		cout<<arry[i]<<" ";
    
// Calling of function Menu
    
	menu();
    
//Caluculations for user selection
    
    //Selection 1
    
    
        for(i=0;i<amt;i++)
            sum+=arry[i];
    
    cout<<sum;
    
    return 0;
}

// Function for menu

    int menu()
    {
        int selec;
        cout<<"\n\nPlease indicate what action is desired:\n\n   <1> To add the #'s\n   <2> To find the largest #\n   <3> To find the smallest #\n   <4> To exit program\n\n    ";
        cin>>selec;
    
        return selec;
    }



