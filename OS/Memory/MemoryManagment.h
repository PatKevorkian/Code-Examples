#ifndef MemoryManagment_h
#define MemoryManagment_h

#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <stdio.h>
#include <sstream>
using namespace std;

class MemoryManagment{
private:
    //struct to represent a partition in memory
    struct memory{
        int size;
        int partNumber;
        bool status; //has a proccess in it
        int freeSpace;
        int usedSpace;
        string jobName;
    };
    //struct to represent a job and its info
    struct process{
        int size;
        string name;
        bool status; //in a partition
    };
    process * jobs;
    memory * parts;
    int wastedSpace, usedSpace, totalAvailSpace, numOfParts, numOfJobs;
public:
    MemoryManagment();
    ~MemoryManagment();
    void MainMenu();
    void menu();
    int getSize(); //gets user input for desired size of either jobs/partitions
    void print();
    void ResetPartsJobs(); //resets all jobs/partition to false and space vars to defualt
    int lenOfInt(int);  //returns teh length of an integer (used for output)
    void firstFit();
    void bestFit();
    void nextFit();
    void worstFit();
    bool isNumber(string); //returns true if the string contains only numbers
};

#endif /* MemoryManagment_hpp */
