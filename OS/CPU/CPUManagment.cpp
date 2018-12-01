#include "CPUManagment.h"

/*gets the user input for the number of processes. allocates the dynamic
 arrays for proccesses.  gets the time of cpu/arrival time/prioirity
 and generates the other importnant info needed*/
CPUManagment::CPUManagment(){
    num_processes=time=tot_turn_around_time=0;
    
    system("clear");
    cout<<"+--------------------------------+"<<endl;
    cout<<"|          CSC 305 LAB 3         |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<"|          CPU MANAGMENT         |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<endl<<endl<<"Enter the number of processes below; (1-10): "<<endl;
    string checknum_processes;
    bool goodinput=false;
    
    //gets the number of proccesses needed , checking if the input
    //is invalid. i.e not a number or not in range
    while (!goodinput){
        try{
            
            cin>>checknum_processes;
            
            if (!isNumber(checknum_processes)) throw 1;
            
            istringstream(checknum_processes) >>num_processes;    //converts a string to an int
            
            if (num_processes>10 || num_processes<1) throw 0;
            
            goodinput=true;
        }
        catch (int a){
            if (a==1)
                cout<<"Error! this input is not a number. Redo: "<<endl;
            else
                cout<<"Error! this number is our of range. Redo: "<<endl;
        }
    }
    
    //sets up the array with the necessary info for each partition
    processes = new Process[num_processes];
    system("clear");
    cout<<"Getting Process information: "<<endl;
    for(int i = 0; i<num_processes; i++){
        cout<<"Setting up process: "<<i<<endl;
        processes[i].process_num=i;
        cout<<"Get arival time: "<<endl;
        processes[i].arrival_time=getTime();//calls function for user input to get the desired time
        cout<<"Get CPU time: "<<endl;
        processes[i].cpu_time=getTime();//calls function for user input to get the desired time
        cout<<"Get Priority: "<<endl;
        processes[i].priority=getPriority();//calls function for user input to get the desired priority
        processes[i].terimanted=false;
    }
    
    system("clear");
    
}

CPUManagment::~CPUManagment(){
    delete [] processes;
}

//shows menu options
void CPUManagment::menu(){
    cout<<"+--------------------------------+"<<endl;
    cout<<"|          CSC 305 LAB 3         |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<"|           CPU MANAGMENT        |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<"|Choose an algorithm to impliment|"<<endl;
    cout<<"|(1) First Come First Serve      |"<<endl;
    cout<<"|(2) Shortest Job Next           |"<<endl;
    cout<<"|(3) Priority                    |"<<endl;
    cout<<"|(4) Quit                        |"<<endl;
    cout<<"+--------------------------------+"<<endl;
}

//main interface for entire program. shows the user options for which method
//to run and continues until the user decides to quir
void CPUManagment::MainMenu(){
    int choice=0;
    while (choice!=4){
        menu();     //shows user options for methods
        bool goodinput=false;
        string choiceCheck;
        
        //gets and checks the choice to make sure it is valid
        //i.e a only a number and that the value is between 1-4
        while (!goodinput){
            try{
                cout<<"Which CPU Managment Method would you like to impliment?"<<endl;
                cout<<"Enter a number 1-4: ";
                cin>>choiceCheck;
                
                if (!isNumber(choiceCheck)) throw 1;
                
                istringstream(choiceCheck) >> choice;    //converts a string to an int
                
                if (choice>4 || choice<1) throw 0;
                
                goodinput=true;
            }
            catch (int a){
                if (a==1)
                    cout<<"Error! this input is not a number. Redo: "<<endl;
                else
                    cout<<"Error! this number is our of range. Redo: "<<endl;
            }
        }
        
        if (choice==1){
            FCFS();
        }
        else if (choice==2){
            SJN();
        }
        else if (choice==3){
            Priority();
        }
        //if the user didnt want to quit, prepare to reset for another method
        if (choice!=4){
            cout<<"The average turn around time is: "<<get_avg_tat()<<endl;
            cin.ignore();
            cout<<"Press any enter to return to the main menu";
            cin.get();
            reset();
        }
        system("clear");
    }
}

void CPUManagment::FCFS(){
    bool found=false;
    int tempArrivalTime = -1, tempIndex = -1, terminated_process=num_processes;
    
    //make sure all processes are terminated before ending loop
    while(terminated_process>0){
        
        tempArrivalTime = tempIndex = -1;           //temporary values to find lowest arrival time
        found=false;                                //used for finding the first value
        
        //find the lowest arrival time by itterate over every process
        for(int i = 0; i < num_processes; i++){
            
            //if the arrival time is greater the temp time (exclusivly -1) and there was no smallest cpu time found
            //and the process has yet to be terminated (which may be redundent)
            if(processes[i].arrival_time > tempArrivalTime
               && found==0 && processes[i].terimanted == false){
                tempIndex = i;
                tempArrivalTime = processes[i].arrival_time;
                found=true;
            }
            //if there is already a process found, is this process smaller than the temp
            if (found && processes[i].arrival_time < processes[tempIndex].arrival_time
                && processes[i].terimanted == false){
                tempIndex = i;
                tempArrivalTime = processes[i].arrival_time;
            }
        }
        
        //accounting for a process with the first proess to run with an arival time =/=0
        if (time==0 && processes[tempIndex].arrival_time >0)
            time+=processes[tempIndex].arrival_time;
        
        //update time and termination for the process next in the order
        time+=processes[tempIndex].cpu_time;
        processes[tempIndex].time_terminated=time;
        processes[tempIndex].terimanted = true;
        tot_turn_around_time+=processes[tempIndex].turnAroundTime();
        print(tempIndex);       //print out the desired index of process i
        terminated_process--;
    }
    
}

void CPUManagment::SJN(){
    int tempIndex=-1, shortestcpu=-1, terminated_process=num_processes, lowestTimeIndex=-1, lowestTime=-1;
    bool found=false;
    
    //make sure every process is terminated
    while (terminated_process>0){
        tempIndex = shortestcpu = -1;
        found = false;
        
        //find the process with the smallest arrival time, if none is found that is
        //withing the time needed to be arrived yet, index=-1
        for(int i = 0; i < num_processes; i++){
            if(processes[i].cpu_time>shortestcpu && found==0 && !processes[i].terimanted
               && processes[i].arrival_time <= time){
                tempIndex = i;
                shortestcpu = processes[i].cpu_time;
                found=true;
            }
            
            // there was a process found with smaller cpu time, is it smaller than the temp
            if (found && processes[i].cpu_time < processes[tempIndex].cpu_time
                && !processes[i].terimanted  && processes[i].arrival_time <= time){
                tempIndex = i;
                shortestcpu = processes[i].cpu_time;
            }
        }
        
        //if no process is smallest and arrived yet, get the shortest arrival time
        if(tempIndex == -1){
            lowestTimeIndex = lowestTime = -1;
            found = false;
            //find the lowest arrival time
            for(int i = 0; i < num_processes; i++){
                if(processes[i].arrival_time > lowestTime
                   && !found && !processes[i].terimanted ){
                    lowestTimeIndex = i;
                    lowestTime = processes[i].arrival_time;
                    found=true;
                }
                //if there is already a process found, is this process smaller?
                if (found && processes[i].arrival_time < processes[lowestTimeIndex].arrival_time
                    && !processes[i].terimanted){
                    lowestTimeIndex = i;
                    lowestTime = processes[i].arrival_time;
                }
            }
            tempIndex=lowestTimeIndex;//update the tempindex
        }
        
        //accounting for a process with the first proess to run with an arival time =/=0
        if (time==0 && processes[tempIndex].arrival_time >0)
            time+=processes[tempIndex].arrival_time;
        
        //update the time for the next process and turn around time
        time+=processes[tempIndex].cpu_time;
        processes[tempIndex].time_terminated=time;
        processes[tempIndex].terimanted = true;
        tot_turn_around_time+=processes[tempIndex].turnAroundTime();
        print(tempIndex);   //print desired process at tempIndex
        terminated_process--;
    }
}

void CPUManagment::Priority(){
    int tempIndex=-1, smallestPrio=-1, lowestTimeIndex=-1, lowestTime=-1, num_terminated=num_processes;
    bool found=false;
    
    //make sure to itterate over every process
    while (num_terminated>0){
        tempIndex = smallestPrio = -1;
        found = false;
        
        //find the process with the smallest priority time, if none is found that is
        //withing the time needed to be arrived yet, index=-1
        for(int i = 0; i < num_processes; i++){
            if(processes[i].priority > smallestPrio && !found
               && !processes[i].terimanted  && processes[i].arrival_time <= time){
                tempIndex = i;
                smallestPrio = processes[i].priority;
                found=true;
            }
            
            // there was a process found with smaller priority, is it smaller than the temp;
            if (found && processes[i].priority < processes[tempIndex].priority
                && !processes[i].terimanted  && processes[i].arrival_time <= time){
                tempIndex = i;
                smallestPrio = processes[i].priority;
            }
        }
        
        //if no process is smallest and arrived yet, get the shortest arrival time
        if(tempIndex == -1){
            lowestTimeIndex = -1;
            lowestTime = -1;
            found = false;
            
            //find the lowest arrival time by itterate over every process
            for(int i = 0; i < num_processes; i++){
                if(processes[i].arrival_time > lowestTime
                   && !found && !processes[i].terimanted ){
                    lowestTimeIndex = i;
                    lowestTime = processes[i].arrival_time;
                    found=true;
                }
                
                //if there is already a process found, is this process smaller?
                if (found && processes[i].arrival_time < processes[lowestTimeIndex].arrival_time
                    && !processes[i].terimanted){
                    lowestTimeIndex = i;
                    lowestTime = processes[i].arrival_time;
                }
            }
            tempIndex=lowestTimeIndex;  //update tempIndex
        }
        //accounting for a process with the first proess to run with an arival time =/=0
        if (time==0 && processes[tempIndex].arrival_time >0)
            time+=processes[tempIndex].arrival_time;
        
        //update time for next process and turn around time
        time+=processes[tempIndex].cpu_time;
        processes[tempIndex].time_terminated=time;
        processes[tempIndex].terimanted = true;
        tot_turn_around_time+=processes[tempIndex].turnAroundTime();
        print(tempIndex);   //print out desired process tempIndex
        num_terminated--;
    }
}

//prints the info in a desired process i
void CPUManagment::print(int i){
    
    cout<<"+-----------------------------+"<<endl;
    cout<<"|Process Number: " <<processes[i].process_num<<setw(13-lenOfInt(processes[i].process_num))<<' '<<"|"<<endl;
    cout<<"|Priority: " << processes[i].priority <<setw(19-lenOfInt(processes[i].priority))<<' '<<"|"<<endl;
    cout<<"|Arrival Time (MS): " << processes[i].arrival_time<<setw(10-lenOfInt(processes[i].arrival_time))<<' '<<"|"<<endl;
    cout<<"|CPU Time (MS): " << processes[i].cpu_time<<setw(14-lenOfInt(processes[i].cpu_time))<<' '<<"|"<<endl;
    cout<<"|Starting Time (MS): " << processes[i].starting_time()<<setw(9-lenOfInt(processes[i].starting_time()))<<' '<<"|"<<endl;
    cout<<"|Terminated Time (MS): " << processes[i].time_terminated<<setw(7-lenOfInt(processes[i].time_terminated))<<' '<<"|"<<endl;
    cout<<"|Turn Around Time (MS): " << processes[i].turnAroundTime()<<setw(6-lenOfInt( processes[i].turnAroundTime() ))<<' '<<"|"<<endl;
    cout<<"|Waiting Time (MS): " << processes[i].time_waiting()<<setw(10-lenOfInt(processes[i].time_waiting()))<<' '<<"|"<<endl;
    cout<<"+-----------------------------+"<<endl;
    
}

//returns true if the string contains only numbers
bool CPUManagment::isNumber(string num){
    for (int i=0; i<num.length(); i++)
        if (!isdigit(num[i]))
            return false;
    return true;
}

//asks user input for a desired time for the priority
int CPUManagment::getPriority(){
    int choice=0;
    bool goodinput=false;
    string choiceCheck;
    //gets and checks the choice to make sure it is valid
    //i.e a only a number and that the value is between 1-10
    while (!goodinput){
        try{
            cout<<"Enter a priority: (1-10)";
            cin>>choiceCheck;
            
            if (!isNumber(choiceCheck)) throw 1;
            
            istringstream(choiceCheck) >> choice;    //converts a string to an int
            
            if (choice> 10 || choice<1) throw 0;
            
            goodinput=true;
        }
        catch (int a){
            if (a==1)
                cout<<"Error! this input is not a number. Redo: "<<endl;
            else
                cout<<"Error! this number is our of range. Redo: "<<endl;
        }
    }
    return choice;
}

//asks user input for a desired time for the cpu time/arrival time
int CPUManagment::getTime(){
    int choice=0;
    bool goodinput=false;
    string choiceCheck;
    //gets and checks the choice to make sure it is valid
    //i.e a only a number and that the value is between 1-100
    while (!goodinput){
        try{
            cout<<"Enter time (0-100)";
            cin>>choiceCheck;
            
            if (!isNumber(choiceCheck)) throw 1;
            
            istringstream(choiceCheck) >> choice;    //converts a string to an int
            
            if (choice> 100 || choice<0) throw 0;
            
            goodinput=true;
        }
        catch (int a){
            if (a==1)
                cout<<"Error! this input is not a number. Redo: "<<endl;
            else
                cout<<"Error! this number is our of range. Redo: "<<endl;
        }
    }
    return choice;
}

//returns the length of an integer, this is called in print to format the output
int  CPUManagment::lenOfInt(int num){
    if (num==0) return 1;
    int size=0;
    while (num>0){
        size++;
        num/=10;
    }
    return size;
}

//resets varibles to defaults to use another method on the same procecesses
void CPUManagment::reset(){
    time=tot_turn_around_time=0;
    for (int i=0; i<num_processes; i++){
        processes[i].time_terminated=0;
        processes[i].terimanted=false;
    }
}

//returns the average turn around time of every process
double CPUManagment::get_avg_tat(){
    return (double)tot_turn_around_time/num_processes;
}
