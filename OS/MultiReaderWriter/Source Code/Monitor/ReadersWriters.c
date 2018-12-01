#include<stdio.h>
#include<conio.h>
#include<pthread.h>

/* Global variables */ 
pthread_mutex_t m;    //mutex initilizer
pthread_cond_t turn; /* Event:turn */
long writing, writers; //reader and writer declarations
long reading;

void init() {     // initilizatoins of the global variables 
	 pthread_mutex_init(&m, NULL);    
	 pthread_cond_init(&turn, NULL);
	 reading = 0;
	 writing = 0;
	 writers = 0;
}

void reader(void *arg)  // Reader Function 
{
	 long data = (long *) arg;   
	 pthread_mutex_lock(&m);
	 if (writers){  //checking to see if writers is finished 
	 	//pthread_cond_wait(&turn, &m);
	 	pthread_cond_signal(&turn); 
	 }
	 while (writing){
	 	pthread_cond_wait(&turn, &m); // While accessing  this will hold the process
	 }
	 reading++;  //adds reader 
	 srand (time(NULL));   //creates a random time seed 
	 long randNum = (rand()%(1000-1))+ 1;   // randome number between 1-1000
	 Sleep(randNum);  //Sleep time 
	 pthread_mutex_unlock(&m);  // unlocks the thread 
	 /* Reading here */
	 pthread_mutex_lock(&m);  //relocks the thread 
	 srand (time(NULL));
	 randNum = (rand()%(10000-1))+ 1;
	 Sleep(randNum);
	 printf("File is read by reader thread - %ld\n",data);
	 reading--; // readers release 
	 pthread_cond_broadcast(&turn);  // signnal that reader is finished 
	 pthread_mutex_unlock(&m); // unlocks the thread 
     pthread_exit(NULL); // the threads exit and finish 
}

void writer(void *arg) // writer function 
{
	 long data = (long *) arg;
	 pthread_mutex_lock(&m);
	 writers++;
	 while (reading > 0 || writing){ //checks to see if the readers have releasd 
	 	//pthread_cond_signal(&turn);
	 	pthread_cond_wait(&turn, &m);  // see if the condition is clear for locking 
	 }
	 writing++;
	 srand (time(NULL));
	 long randNum = (rand()%(1000-1))+ 1;
	 Sleep(randNum);
	 pthread_mutex_unlock(&m);
	 /* Writing here */
	 pthread_mutex_lock(&m);
	 srand (time(NULL));
	 randNum = (rand()%(10000-1))+ 1;
	 Sleep(randNum);
	 printf("File is written by writer thread - %ld\n",data);
	 writing--;
	 writers--;	
	 pthread_cond_broadcast(&turn);
	 pthread_mutex_unlock(&m);
	 pthread_exit(NULL);
}

int main()
{  
	long i=0,NumberofReaderThread=0,NumberofWriterThread,SleepTime;
	init();
	// Print statements/ user inputs 
	pthread_t Readers_thr[100],Writer_thr[100];
	printf("\nEnter how long to sleep before terminating :- ");
	scanf("%ld",&SleepTime);
	printf("\nEnter number of Readers thread(1 - 9) :- ");
	scanf("%ld",&NumberofReaderThread);
	if(NumberofReaderThread<1 || NumberofReaderThread>9)
	{
		printf("Invalid number of Readers... please only input between 1 - 9\n");
		system("PAUSE");
		exit(1);
	}
	printf("\nEnter number of Writers thread(1 - 3) :- ");
	scanf("%ld",&NumberofWriterThread);
	if(NumberofWriterThread<1 || NumberofWriterThread>3)
	{
		printf("Invalid number of Writers... please only input between 1 - 3\n");
		system("PAUSE");
		exit(1);
	}	
	while(1)   //continue the process 
   {
    
	for(i=0;i<NumberofWriterThread;i++)
	{
		srand (time(NULL));
		pthread_create(&Writer_thr[i],NULL,(void*) &writer,(void*)i);
	}
	for(i=0;i<NumberofReaderThread;i++)
	{
		srand (time(NULL));
		pthread_create(&Readers_thr[i],NULL,(void*) &reader,(void*)i);
	}
	for(i=0;i<NumberofReaderThread;i++)
	{
		srand (time(NULL));
	 	Sleep(SleepTime);
		pthread_join(Readers_thr[i],NULL);
	}
	for(i=0;i<NumberofWriterThread;i++)
	{
		srand (time(NULL));
	 	Sleep(SleepTime);
		pthread_join(Writer_thr[i],NULL);
	}
	//pthread_exit(NULL);
	//return 0;
}

}
