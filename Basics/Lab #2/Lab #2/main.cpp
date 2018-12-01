#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
    
    //Declare Variables
    
    int i=0;
    char lttr[5];
    double g1=0,g2=0,g3=0,g4=0,g5=0,add,avg1,avg2,avg3,avg4,avg5,avg[5];
	string name[5];
    ifstream filein;
    
    //Open file
    
	filein.open("StudentGrades.txt");
    if(!filein)
    {
        cout<<"file not found!";
        return 1;
    }
    
    //Prompt user
    
    cout<<"Enter 5 students names and their grades from a file to recieve an average and letter grade. \n\n       Names in file: ";
    
    //Array created to enter student names
    
    for(i=0;i<5;i++)
    {   filein>>name[i];
        cout<<name[i]<<"\n                      ";
    }
    
    //Promt user
    
    cout<<"\n5 grades for each student in the order from the file.\n\n      Grades in file: ";
    
    //5 grades for each student then added together
    
    cout<<"\n\n          "<<name[0]<<": ";
    for(i=0;i<5;i++)
    {   filein>>add;
        cout<<add<<" ";
        g1=add+g1;
    }
    add=0;
    cout<<"\n\n          "<<name[1]<<": ";
    for(i=0;i<5;i++)
    {   filein>>add;
        cout<<add<<" ";
        g2=add+g2;
    }
    add=0;
    cout<<"\n\n          "<<name[2]<<": ";
    for(i=0;i<5;i++)
    {   filein>>add;
        cout<<add<<" ";
        g3=add+g3;
    }
    add=0;
    cout<<"\n\n          "<<name[3]<<": ";
    for(i=0;i<5;i++)
    {   filein>>add;
        cout<<add<<" ";
        g4=add+g4;
    }
    add=0;
    cout<<"\n\n          "<<name[4]<<": ";
    for(i=0;i<5;i++)
    {   filein>>add;
        cout<<add<<" ";
        g5=add+g5;
    }
    
    //Calculate average
    
    avg1=g1/5;
    avg2=g2/5;
    avg3=g3/5;
    avg4=g4/5;
    avg5=g5/5;
    
    //Put average of each student into an array
    
    
    avg[0]=avg1;
    avg[1]=avg2;
    avg[2]=avg3;
    avg[3]=avg4;
    avg[4]=avg5;
    
    //Determine Letter grade for average and Put into array
    
	for(i=0;i<5;i++)
	{
		if(avg[i]>=90)
			lttr[i]='A';
		else if(avg[i]>=80)
			lttr[i]='B';
		else if(avg[i]>=70)
			lttr[i]='C';
		else if(avg[i]>=60)
			lttr[i]='D';
		else
			lttr[i]='F';
	}
    
    //Output
    
	cout<<"\n\nNAME            AVERAGE             LETTER GRADE\n\n";
	for(i=0;i<5;i++)
	{	cout<<name[i]<<":                "<<avg[i]<<"                        "<<lttr[i];
		cout<<"\n";
	}
	cout<<"\n\n\n";
    
    //Pause Program
    
	system ("PAUSE");
    
    return 0;
    
}






