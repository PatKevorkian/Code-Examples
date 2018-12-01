//
//  processManagement.hpp
//  Process Management
//
//  Created by Pat Kevorkian on 11/6/15.
//  Copyright © 2015 Pat Kevorkian. All rights reserved.
//

#ifndef processManagement_hpp
#define processManagement_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

class processManagement
{
    
private:
    struct Process
    {
        int process_num;
        int arrival_time;
        int priority;
        int cpu_time;
        bool terimanted;
        int time_terminated;
        int starting_time()
        {
            return time_terminated-cpu_time;
        };
        int time_waiting()
        {
            return starting_time()-arrival_time;
        };
        int turnAroundTime()
        {
            return time_terminated-arrival_time;
        };
    };
    
    int num_processes,time,tot_turn_around_time;
    Process * processes;
    
public:
    processManagement();
    ~processManagement();
    void menu();
    void MainMenu();
    int getTime();
    int getPriority();
    void FCFS();
    void SJN();
    void Priority();
    void print(int);
    void reset();
    double get_avg_tat();
};

#endif /* processManagement_hpp */
