//
//  main.cpp
//  Adv OS Proj 2
//
//  Created by Pat Kevorkian on 5/11/17.
//  Copyright © 2017 Pat Kevorkian. All rights reserved.
//

//Solution to Reader Writer Problem using Test & Set

#include<iostream>
#include<thread>
#include<vector>
#include<atomic>
#include<random>
#include<chrono>
using namespace std;

//A "file" of 10 numbers that can be read and written
int file[9];

//Locks used in Test & Set functions
atomic_flag fileLock = ATOMIC_FLAG_INIT;
atomic_flag numReaderLock = ATOMIC_FLAG_INIT;

int numReadersInCS=0;
int numWritersInCS=0;

//Random Number Generator seed and ranges
random_device rd;
mt19937_64 mt(rd());

int randTime(int max)
{
    //Returns random # between 0 and parameter max
    uniform_int_distribution<int> randomTime(0, max);
    return randomTime(mt);
}

//Print out the file contents
void printFile()
{
    cout<<endl;
    cout<<"File Contents: ";
    for(int i = 0 ; i < 10 ; i++)
        printf("%d,",file[i]);
    printf("\b ");
    cout<<endl<<endl;
}

//Reader Program
void reader(int waitTime, int accessTime, int exitTime, int tid);
//Writer Program
void writer(int waitTime, int accessTime, int exitTime, int tid);

int main()
{
    int numReaders, numWriters, sleepBeforeTerminating;
    
    //Poplating file with 10 random int
    for(int i = 0 ; i < 10 ; i++)
        file[i] = randTime(100);
    printFile();
    
    //Get number of producers, consumers,
    cout<<"Number of Readers (1-9): ";
    cin>>numReaders;
    cout<<"Number of Writers (1-3): ";
    cin>>numWriters;
    cout<<"Time to sleep before terminating: ";
    cin>>sleepBeforeTerminating;
    cout<<endl;
    
    //Vectors to hold reader and writer threads
    vector<thread> readers;
    vector<thread> writers;
    
    //Create Reader Threads
    for(int i=0;i<numReaders;i++)
        readers.push_back(thread(reader, randTime(1000),randTime(10000), randTime(10000), i));
    
    //Create Writer Threads
    for(int i=0;i<numWriters;i++)
        writers.push_back(thread(writer, randTime(1000),randTime(10000), randTime(10000), i));
    
    for(unsigned i = 0 ; i < numReaders ; i ++)
    {
        readers.at(i).join();
    }
    for(unsigned i = 0 ; i < numWriters ; i ++)
    {
        writers.at(i).join();
    }
    
    return 0;
}

//Reader Program
void reader(int waitTime, int accessTime, int exitTime, int tid)
{
    while(1)
    {
        //PREFIX i   Reader waits before requesting access to CS
        this_thread::sleep_for(chrono::milliseconds(waitTime));
        printf("Reader %d requests access to the file\n", tid);
        while(numWritersInCS>0) {}	//wait for lock
        fileLock.test_and_set();
        
        //CRITICAL SECTION   Reader waits while inside CS
        while(numReaderLock.test_and_set()){}	//wait to increase num active writers in CS
        int rFileNum = randTime(9); //Random place for the reader to read in the file
        numReadersInCS++;
        numReaderLock.clear();	//clear lock
        printf("Reader %d is in the CS reading File[ %d ] = %d \n", tid,rFileNum,file[rFileNum]); //Prints what is being read
        this_thread::sleep_for(chrono::milliseconds(accessTime));
        
        //SUFFIX i    Reader waits after exiting CS (simulates data processing)
        while(numReaderLock.test_and_set()){}	//wait to increase num active writers in CS
        numReadersInCS--;
        numReaderLock.clear();	//clear lock
        
        //check if all readers are done
        while(numReaderLock.test_and_set()){}
        if(numReadersInCS==0)
            fileLock.clear();
        numReaderLock.clear();
        
        printf("Reader %d exited the CS.\n", tid);
        this_thread::sleep_for(chrono::milliseconds(exitTime));
    }
}


//Writer Program
void writer(int waitTime, int accessTime, int exitTime, int tid)
{
    while(1)
    {
        //PREFIX i    Writer waits before requesting access to CS
        this_thread::sleep_for(chrono::milliseconds(waitTime));
        cout<<"\nWriter " << tid << " requests access to file." <<endl;
        while(fileLock.test_and_set()) {}		//wait for lock
        
        //CRITICAL SECTION    Writer waits while inside CS
        int wFileNum = randTime(9); //Random place for writer to write within file
        int newWriteVal = randTime(100); //Random number to write in the file
        numWritersInCS++;
        printf("Writer %d is in the CS and is writing: %d to File[ %d ]\n", tid, newWriteVal, wFileNum); //Prints what is beign written and where
        file[wFileNum] = newWriteVal; //Changes a file value
        printFile(); //P rint new file contents
        this_thread::sleep_for(chrono::milliseconds(accessTime));		
        
        //SUFFIX i    Writer waits after exiting CS (simulates data processing)
        numWritersInCS--;
        printf("Writer %d exited the CS. \n", tid);
        fileLock.clear();	//release lock on file	
        this_thread::sleep_for(chrono::milliseconds(exitTime));
    }
}
