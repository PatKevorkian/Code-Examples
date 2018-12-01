
#ifndef CPUManagment_h
#define CPUManagment_h

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <string>
#include <sstream>  
#include <iomanip>
using namespace std;

class CPUManagment{
    
private:
    struct Process{
        int process_num;
        int arrival_time;
        int priority;
        int cpu_time;
        bool terimanted; //if a process has been terminated yed
        int time_terminated;
        
         //function to calculate time process is executed
        int starting_time(){
            return time_terminated-cpu_time;
        };
         //function to calculate waiting time
        int time_waiting(){
            return starting_time()-arrival_time;
        };
        //function to calculate turn around time
        int turnAroundTime(){
            return time_terminated-arrival_time;
        };
    };
    
    int num_processes,time,tot_turn_around_time;
    Process * processes;        //array to hold procecesses

public:
    CPUManagment();
    ~CPUManagment();
    void menu();
    void MainMenu();
    bool isNumber(string);      //used to error check input for all digits
    int getTime();              //gets an integer designated for cpu/arrival time
    int getPriority();          //gets an integer designated for priority
    void FCFS();                //first come first serve function
    void SJN();                 //shortest job next function
    void Priority();            //priority function
    void print(int);            //takes in an index and prints its info
    int lenOfInt(int);          //used to format ouput
    void reset();               //resets time, to_turn_around time, each process terminated
    double get_avg_tat();       //returns the avergate turn around time of every process
};
#endif /* CPUManagment_hpp */
