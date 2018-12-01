//
//  Memory Algorithms.hpp
//  Memory Algorithms
//
//  Created by Pat Kevorkian on 10/8/15.
//  Copyright © 2015 Pat Kevorkian. All rights reserved.
//

#ifndef Memory_Algorithms_hpp
#define Memory_Algorithms_hpp
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
using namespace std;

class MemoryAlgorithms
{
private:
    
        //struct for partitions
        struct partitions
        {
            int partNum, size, freeSpace, usedSpace;
            bool state;
            string jobName;
        };
    
        //struct for jobs
        struct job
        {
            int size;
            bool state;
            string name;
        };
    
        //var
        partitions * parts;
        job * jobs;
        int usedSpace, allAvailSpace, wastedSpace, numOfJobs, numOfParts;

public:
    
    MemoryAlgorithms();
    ~MemoryAlgorithms();
    void mMenu();
    void menu();
    void firstFit();
    void bestFit();
    void nextFit();
    void worstFit();
    int getJP();
    void resetJP();
    void print();
    
    
};

#endif /* Memory_Algorithms_hpp */
