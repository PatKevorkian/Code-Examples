//
//  processManagement.cpp
//  Process Management
//
//  Created by Pat Kevorkian on 11/6/15.
//  Copyright © 2015 Pat Kevorkian. All rights reserved.
//

#include "processManagement.hpp"

//user input for number of processes
processManagement::processManagement()
{
    num_processes=time=tot_turn_around_time=0;
    
    cout<<endl<<endl<<"Enter the number of processes: "<<endl;
            
            cin>>num_processes;
    
    //sets up the array with the necessary info for each partition
    processes = new Process[num_processes];
    system("clear");
    cout<<"Getting Process information: "<<endl;
    for(int i = 0; i<num_processes; i++)
    {
        cout<<endl;
        cout<<"Setting up process: "<<i<<endl;
        processes[i].process_num=i;
        cout<<"Get arival time: "<<endl;
        processes[i].arrival_time=getTime();
        cout<<"Get CPU time: "<<endl;
        processes[i].cpu_time=getTime();
        cout<<"Get Priority: "<<endl;
        processes[i].priority=getPriority();
        processes[i].terimanted=false;
        cout<<endl;
    }
    
    system("clear");
    
}

processManagement::~processManagement()
{
    delete [] processes;
}

//shows options
void processManagement::menu()
{
  
    cout<<"(1) First Come First Serve"<<endl;
    cout<<"(2) Shortest Job Next"<<endl;
    cout<<"(3) Priority"<<endl;
    cout<<"(4) Quit"<<endl;
    
}

//menue
void processManagement::MainMenu()
{
    int choice=0;
    while (choice!=4)
    {
        menu();
        cin>>choice;


        if (choice==1)
        {
            FCFS();
        }
        else if (choice==2)
        {
            SJN();
        }
        else if (choice==3)
        {
            Priority();
        }
        if (choice!=4)
        {
            cout<<"Average turn around time: "<<get_avg_tat()<<endl;
            cin.ignore();
            cout<<"Press any key to return to the main menu";
            cin.get();
            reset();
        }
        system("clear");
    }
}
void processManagement::FCFS()
{
    bool found=false;
    int tempArrivalTime = -1, tempIndex = -1, terminated_process=num_processes;
    
    while(terminated_process>0)
    {
        
        tempArrivalTime = tempIndex = -1;
        
        found=false;
        
        //itterate over every process
        for(int i = 0; i < num_processes; i++)
        {
            
            //if arrival time is greater than temp time and there was no smallest cpu time
            if(processes[i].arrival_time > tempArrivalTime
               && found==0 && processes[i].terimanted == false)
            {
                tempIndex = i;
                tempArrivalTime = processes[i].arrival_time;
                found=true;
            }
            //if there is process found, is this process smaller than temp
            if (found && processes[i].arrival_time < processes[tempIndex].arrival_time
                && processes[i].terimanted == false)
            {
                tempIndex = i;
                tempArrivalTime = processes[i].arrival_time;
            }
        }
        
        //if first proess to run with an arival time 0
        if (time==0 && processes[tempIndex].arrival_time >0)
            time+=processes[tempIndex].arrival_time;
        
        //update time and termination
        time+=processes[tempIndex].cpu_time;
        processes[tempIndex].time_terminated=time;
        processes[tempIndex].terimanted = true;
        tot_turn_around_time+=processes[tempIndex].turnAroundTime();
        print(tempIndex);       //print
        terminated_process--;
    }
    
}

void processManagement::SJN()
{
    int tempIndex=-1, shortestcpu=-1, terminated_process=num_processes, lowestTimeIndex=-1, lowestTime=-1;
    bool found=false;
    
    //term processes
    while (terminated_process>0)
    {
        tempIndex = shortestcpu = -1;
        found = false;
        
        //process with the smallest arrival time in time needed to arrive
        for(int i = 0; i < num_processes; i++)
        {
            if(processes[i].cpu_time>shortestcpu && found==0 && !processes[i].terimanted
               && processes[i].arrival_time <= time)
            {
                tempIndex = i;
                shortestcpu = processes[i].cpu_time;
                found=true;
            }
            
            // smaller cpu time, smaller than the temp
            if (found && processes[i].cpu_time < processes[tempIndex].cpu_time
                && !processes[i].terimanted  && processes[i].arrival_time <= time)
            {
                tempIndex = i;
                shortestcpu = processes[i].cpu_time;
            }
        }
        
        //no process is smallest and arrived yet, its the shortest arrival
        if(tempIndex == -1)
        {
            lowestTimeIndex = lowestTime = -1;
            found = false;
            //find lowest arrival time
            for(int i = 0; i < num_processes; i++){
                if(processes[i].arrival_time > lowestTime
                   && !found && !processes[i].terimanted )
                {
                    lowestTimeIndex = i;
                    lowestTime = processes[i].arrival_time;
                    found=true;
                }
                //if process found, decide if process smallest
                if (found && processes[i].arrival_time < processes[lowestTimeIndex].arrival_time
                    && !processes[i].terimanted){
                    lowestTimeIndex = i;
                    lowestTime = processes[i].arrival_time;
                }
            }
            tempIndex=lowestTimeIndex;//update the tempindex
        }
        
        //first proess to run with an arival time 0
        if (time==0 && processes[tempIndex].arrival_time >0)
            time+=processes[tempIndex].arrival_time;
        
        //update the time
        time+=processes[tempIndex].cpu_time;
        processes[tempIndex].time_terminated=time;
        processes[tempIndex].terimanted = true;
        tot_turn_around_time+=processes[tempIndex].turnAroundTime();
        print(tempIndex);   //print
        terminated_process--;
    }
}

void processManagement::Priority()
{
    int tempIndex=-1, smallestPrio=-1, lowestTimeIndex=-1, lowestTime=-1, num_terminated=num_processes;
    bool found=false;
    
    //itterate over every process
    while (num_terminated>0)
    {
        tempIndex = smallestPrio = -1;
        found = false;
        
        //process with the smallest priority time
        for(int i = 0; i < num_processes; i++)
        {
            if(processes[i].priority > smallestPrio && !found
               && !processes[i].terimanted  && processes[i].arrival_time <= time)
            {
                tempIndex = i;
                smallestPrio = processes[i].priority;
                found=true;
            }
            
            //process found with smaller priority, it smaller temp;
            if (found && processes[i].priority < processes[tempIndex].priority
                && !processes[i].terimanted  && processes[i].arrival_time <= time)
            {
                tempIndex = i;
                smallestPrio = processes[i].priority;
            }
        }
        
        //no process is smallest and arrive, get shortest arrival
        if(tempIndex == -1)
        {
            lowestTimeIndex = -1;
            lowestTime = -1;
            found = false;
            
            //find the lowest arrival time
            for(int i = 0; i < num_processes; i++)
            {
                if(processes[i].arrival_time > lowestTime
                   && !found && !processes[i].terimanted )
                {
                    lowestTimeIndex = i;
                    lowestTime = processes[i].arrival_time;
                    found=true;
                }
                
                //this process smaller
                if (found && processes[i].arrival_time < processes[lowestTimeIndex].arrival_time
                    && !processes[i].terimanted){
                    lowestTimeIndex = i;
                    lowestTime = processes[i].arrival_time;
                }
            }
            tempIndex=lowestTimeIndex;  //update temp
        }
        //first proess to run with an arival time 0
        if (time==0 && processes[tempIndex].arrival_time >0)
            time+=processes[tempIndex].arrival_time;
        
        //update time
        time+=processes[tempIndex].cpu_time;
        processes[tempIndex].time_terminated=time;
        processes[tempIndex].terimanted = true;
        tot_turn_around_time+=processes[tempIndex].turnAroundTime();
        print(tempIndex);   //print
        num_terminated--;
    }
}

//prints

void processManagement::print(int i)
{
    cout<<endl<<endl;
    cout<<"Process Number: " <<processes[i].process_num<<endl;
    cout<<"Priority: " << processes[i].priority<<endl;
    cout<<"Arrival Time (MS): " << processes[i].arrival_time<<endl;
    cout<<"CPU Time (MS): " << processes[i].cpu_time<<endl;
    cout<<"Starting Time (MS): " << processes[i].starting_time()<<endl;
    cout<<"Terminated Time (MS): " << processes[i].time_terminated<<endl;
    cout<<"Turn Around Time (MS): " << processes[i].turnAroundTime()<<endl;
    cout<<"Waiting Time (MS): " << processes[i].time_waiting()<<endl;
    cout<<endl<<endl;
    
}

//asks user input for a desired time for the priority
int processManagement::getPriority()
{
    int choice=0;

            cout<<"Enter a priority: ";
            cin>>choice;
    
    return choice;
}

//asks user input for a desired time for the cpu time/arrival time
int processManagement::getTime()
{
    int choice=0;
   
    cout<<"Enter time:";
    cin>>choice;
    
    return choice;
}

//resets variables
void processManagement::reset()
{
    time=tot_turn_around_time=0;
    for (int i=0; i<num_processes; i++)
    {
        processes[i].time_terminated=0;
        processes[i].terimanted=false;
    }
}

//returns the average turnaround time
double processManagement::get_avg_tat()
{
    return (double)tot_turn_around_time/num_processes;
}
