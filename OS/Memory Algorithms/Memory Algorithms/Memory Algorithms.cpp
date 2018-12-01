//
//  Memory Algorithms.cpp
//  Memory Algorithms
//
//  Created by Pat Kevorkian on 10/8/15.
//  Copyright © 2015 Pat Kevorkian. All rights reserved.
//

#include "Memory Algorithms.hpp"

MemoryAlgorithms::MemoryAlgorithms()
{
    system("clear");
    
    //give default value
    wastedSpace=usedSpace=allAvailSpace=0;
    numOfParts=0;
    
    //user input
    cout<<"Enter # of partitions in memory:";
    cin>>numOfParts;
    
    //create array of partitions for # of parts
    parts= new partitions[numOfParts];
    
    system("clear");
    
    for(int i = 0; i<numOfParts; i++)
    {
        cout<<endl<<"Partition number: "<<i+1<<endl;
        cout<<"Enter the size of the partition: " <<endl;
        parts[i].size = getJP();
        parts[i].usedSpace = 0;
        parts[i].freeSpace =parts[i].size;
        parts[i].partNum = i+1;
        parts[i].state = false;
        parts[i].jobName = "NULL";
    }
    
    system("clear");
    
    cout<<"Number of processes: ";
    cin>>numOfJobs;
    
    //create array of jobs for # of jobs
    
    jobs=new job [numOfJobs];
    string jobNumS;
    
    //sets up the arry with the necessary info for each job (job number, size)
    for(int i = 0; i<numOfJobs; i++)
    {
        cout<<endl<<"Job Number: "<<i+1<<endl;
        cout<<"Enter the size of the partition: " <<endl;
        jobs[i].size = getJP();//calls function for user input to get the desired size
        jobs[i].name=to_string(i+1);
        jobs[i].state=false;
        
    }
    
    system("clear");
    
}

MemoryAlgorithms::~MemoryAlgorithms()
{
    //free memory
    delete [] jobs;
    delete [] parts;
}

void MemoryAlgorithms::menu()
{
    //user selections for algorithms
    cout<<endl;
    cout<<"(1) First-fit"<<endl;
    cout<<"(2) Best-fit"<<endl;
    cout<<"(3) Next-fit"<<endl;
    cout<<"(4) Worst-fit"<<endl;
    cout<<"(5) Quit"<<endl<<endl;
}

void MemoryAlgorithms::mMenu()
{
    int choice=0;
    
    while (choice!=5)
    {
        menu();
            
        cout<<"Which Memory Algorithm would you like?"<<endl;
        cout<<"Enter a number 1-5: ";
        cin>>choice;
        
        if (choice==1)
        {
            firstFit();
        }
        else if (choice==2)
        {
            bestFit();
        }
        else if (choice==3)
        {
            nextFit();
        }
        else if (choice==4)
        {
            worstFit();
        }
        
        //arrays and space values reset
        if (choice!=5)
        {
            print();
            cin.ignore();
            cout<<endl;
            cout<<"Press any key to return to main menu";
            cin.get();
            resetJP();
        }
        system("clear");
    }
}


//gets job and partition input

int  MemoryAlgorithms::getJP()
{
    string num1;
    int num;
    
    cout<<"Size in KB: ";
    cin>>num1;
    istringstream(num1) >> num;
            

    return num;
}

void  MemoryAlgorithms::print()
{
    system("clear");
    
    //output
    for (int i=0; i<numOfParts; i++)
    {
        cout<<endl;
        cout<<"Partition: " << parts[i].partNum<<endl;
        cout<<"Status: " << ((parts[i].state==true) ? "Busy" : "Free ")<<endl;
        cout<<"Job Name: " <<parts[i].jobName<<endl;
        cout<<"Size(KB): " << parts[i].size<<endl;
        cout<<"Space Used(KB): " << parts[i].usedSpace<<endl;
        cout<<"Space free(KB): " << parts[i].freeSpace<<endl;
        usedSpace+=parts[i].usedSpace;
        wastedSpace+=parts[i].freeSpace;
        allAvailSpace+=parts[i].size;
        cout<<endl;
    }
    
    cout<<endl;
    
    //jobs waiting
    for(int l = 0; l<numOfJobs; l++){
        if (!jobs[l].state)
            cout<<"Job: "<<jobs[l].name<<" ("<<jobs[l].size<<" KB) is waiting."<<endl;
    }
    cout<<endl;
    cout<<"Space of all partitions is: "<<allAvailSpace<< " KB"<<endl;
    cout<<"Total amount of space used is: "<<usedSpace<<" KB"<<endl;
    cout<<"Total amount of space wasted is: "<<wastedSpace<<" KB"<<endl;
    
    
}

void  MemoryAlgorithms::resetJP()
{
    //resets all jobs and partitions
    for (int i=0; i<numOfParts; i++)
    {
        parts[i].freeSpace =parts[i].size;
        parts[i].state = false;
        parts[i].jobName = "NULL";
        parts[i].usedSpace=0;
    }
    
    for ( int j=0; j<numOfJobs; j++)
        jobs[j].state=false;
    
    wastedSpace=usedSpace=allAvailSpace=0;
}

//first fit
void  MemoryAlgorithms::firstFit()
{
    //itterates on jobs
    for (int j=0; j< numOfJobs; j++)
    {
        
        //itterates on partitions
        for (int i=0; ( i < numOfParts && !jobs[j].state ); i++)
        {
            
            //if a job fits and the partition is free the nthe job is put there.
            if (jobs[j].size<=parts[i].size  && !parts[i].state)
            {
                jobs[j].state=true;
                parts[i].state=true;
                parts[i].jobName=jobs[j].name;
                parts[i].freeSpace-=jobs[j].size;
                parts[i].usedSpace=jobs[j].size;
            }
        }
    }
    
}

//best fit
void MemoryAlgorithms::bestFit()
{
    //partition with smallest hole
    int best;
    //best partition is found
    bool bestPart;
    
    //itterate on jobs
    for (int j=0; j<numOfJobs; j++)
    {
        //reset best
        best=0;
        //resets best partition found
        bestPart=false;
        
        //itterates on partitions
        for (int p=0; p<numOfParts; p++)
        {
            
            //if the partition is open and the job fits
            if (!parts[p].state && (jobs[j].size<=parts[p].size))
            {
                
                //check if there is no best partition yet,
                if (bestPart==false)
                {
                    //if not, this is the current bestIndex
                    best=p;
                    bestPart=true;
                }
                else
                {
                    //already have a best partition, see if the new one is better
                    if (parts[p].size<parts[best].size)
                    {
                        //if so this is the new index
                        best=p;
                    }
                }
            }
        }
        
        //best partition found
        if (bestPart)
        {
            jobs[j].state=true;
            parts[best].state=true;
            parts[best].jobName=jobs[j].name;
            parts[best].freeSpace-=jobs[j].size;
            parts[best].usedSpace=jobs[j].size;
        }
    }
}

// next fit
void  MemoryAlgorithms::nextFit()
{
    //var for start, end, and the last partition
    int end=numOfParts, lastPart=0, start=0;
    //used to reset the loop
    bool reset=false;
    
    //itterat on jobs
    for (int j=0; j<numOfJobs; j++)
    {
        
        //itterate on patritions
        for (int p=start; (p<end && !jobs[j].state);p++)
        {
            
            //job fits and partition open
            if (jobs[j].size<=parts[p].size  && !parts[p].state)
            {
                
               
                jobs[j].state=true;
                parts[p].state=true;
                parts[p].jobName=jobs[j].name;
                parts[p].freeSpace-=jobs[j].size;
                parts[p].usedSpace=jobs[j].size;
                
                //saves last part
                lastPart=start=p+1;
                end=numOfParts;
            }
            
            //loop ends and reset is flagged
            if (p+1==end && start!=0)
            {
                start=0;
                end=lastPart;
                reset=true;
            }
        }
        
        //goes back if not set at this point
        if (reset && !jobs[j].state)
        {
            start=lastPart;
            end=numOfParts;
        }
        
        reset=false;
    }
    
}

//worst fit
void MemoryAlgorithms::worstFit()
{
    //vars
    int best;
    bool bestPart;
    
    //itterates on jobs
    for (int j=0; j< numOfJobs; j++)
    {
        
        best=0;
        bestPart=false;
        
        //itterates on partitions
        for (int p=0; p<numOfParts; p++)
        {
            
            //job fits in partition
            if (jobs[j].size<=parts[p].freeSpace )
            {
                //new partition is better use that one
                if ( (parts[p].freeSpace > parts[best].freeSpace) ||
                    ( (parts[p].freeSpace == parts[best].freeSpace) && bestPart==false) )
                {
                    best=p;
                    bestPart=true;
                }
            }
        }
        
        //then add job to partition 
        if (bestPart)
        {
            jobs[j].state=true;
            parts[best].state=true;
            if (parts[best].jobName=="NULL") parts[best].jobName="";
            parts[best].jobName+=jobs[j].name+" ";
            parts[best].freeSpace-=jobs[j].size;
            parts[best].usedSpace+=jobs[j].size;
        }
    }
}




















