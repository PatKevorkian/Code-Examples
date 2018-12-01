//Reader Writer Problem using Test & Set instructions

#include<iostream>
#include<thread>
#include<vector>
#include<atomic>
#include<random>
#include<chrono>
using namespace std;

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

//Reader Program
void reader(int waitTime, int accessTime, int exitTime, int tid);
//Writer Program
void writer(int waitTime, int accessTime, int exitTime, int tid);

int main()
{
	int numReaders, numWriters, sleepBeforeTerminating;

	//Get number of producers, consumers, 
	cout<<"Number of Readers (1-9): ";
	cin>>numReaders;
	cout<<"Number of Writers (1-3): ";
	cin>>numWriters;
	cout<<"Time to sleep before terminating: ";
	cin>>sleepBeforeTerminating;

	//Vectors to hold reader and writer threads
	vector<thread> readers;
	vector<thread> writers;
	
	//Create Reader Threads
	for(int i=0;i<numReaders;i++)
		readers.push_back(thread(reader, randTime(1000),randTime(10000), randTime(10000), i));

	//Create Writer Threads
	for(int i=0;i<numWriters;i++)
		writers.push_back(thread(writer, randTime(1000),randTime(10000), randTime(10000), i));

	for(auto& th : readers) th.join();
	for(auto& th: writers) th.join();

	return 0;
}

//Reader Program
void reader(int waitTime, int accessTime, int exitTime, int tid)
{
	while(1)	
	{	
		//PREFIX i   Reader waits before requesting access to CS
		this_thread::sleep_for(chrono::milliseconds(waitTime));
		cout<<"Reader " << tid << " requests access to file." <<endl;
		while(numWritersInCS>0) {}	//wait for lock
		fileLock.test_and_set();

		//CRITICAL SECTION   Reader waits while inside CS
		while(numReaderLock.test_and_set()){}	//wait to increase num active writers in CS
		numReadersInCS++;
		numReaderLock.clear();	//clear lock
		cout<<"Reader " << tid << " is in the CS."<<endl;	
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

		cout<<"Reader " <<tid << " exited the CS." <<endl;		
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
		cout<<"Writer " << tid << " requests access to file." <<endl;
		while(fileLock.test_and_set()) {}		//wait for lock

		//CRITICAL SECTION    Writer waits while inside CS
		numWritersInCS++;
		cout<<"Writer " << tid << " is in the CS."<<endl;
		this_thread::sleep_for(chrono::milliseconds(accessTime));		
			
		//SUFFIX i    Writer waits after exiting CS (simulates data processing)
		numWritersInCS--;
		cout<<"Writer " <<tid << " exited the CS." <<endl;
		fileLock.clear();	//release lock on file	
		this_thread::sleep_for(chrono::milliseconds(exitTime));
	}
}
