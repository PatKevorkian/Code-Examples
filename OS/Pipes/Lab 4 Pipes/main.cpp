//
//  main.cpp
//  Lab 4 Pipes
//
//  Created by Pat Kevorkian on 11/23/15.
//  Copyright © 2015 Pat Kevorkian. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define P1_READ 0
#define P2_WRITE 1
#define P2_READ 2
#define P1_WRITE 3

#define NUM_PIPES 2


int main()
{
    int fd[2*NUM_PIPES];
    const char* phrase = "";
    long int len, i;
    pid_t pid, ppid;
    
    for(i=0; i<NUM_PIPES; i++)
    {
        pipe(fd+(i*2));
    }
    
    //Split the process to create child program
    pid = fork();
    
    if(pid == 0)
    {
        //close pipes
        close(fd[P1_READ]);
        close(fd[P1_WRITE]);
        
        //get process id of child
        pid = getpid();
        //get process id
        ppid= getppid();
        
        //Child Reads, buffer 100
        len = read(fd[P2_READ], &phrase, 100);
        
        //Prints phrase recieved from parent
        printf("Child(%d): PPiD:(%d) Received: %s\n", pid, ppid, phrase);
        
        //Phrase to be sent and then recieved by parent
        phrase = "No!";
        
        //Print phrase to be sent to parent
        printf("Child(%d): PPiD:(%d) Sending: %s back\n", pid, ppid, phrase);
        
        //Child sends phrase to parent
        write(fd[P2_WRITE], &phrase, strlen(phrase)+1);
        
        //close pipes
        close(fd[P2_READ]);
        close(fd[P2_WRITE]);
    }
    else
    {
        //close pipes
        close(fd[P2_READ]);
        close(fd[P2_WRITE]);
        
        //get process id of parent program
        pid = getpid();
        
        //Phrase to be sent to child
        phrase = "Go to sleep!";
        
        //Prints the phrase to be sent
        printf("Parent(%d): Sending %s to child\n", pid, phrase);
        
        //Parent sends phrase to child
        write(fd[P1_WRITE], &phrase, strlen(phrase)+1);
        
        //Parent reads phrase sent from child, buffer of 100
        len = read(fd[P1_READ], &phrase, 100);
        
        //Prints phrase recieved from child
        printf("Parent(%d): Received %s\n", pid, phrase);
        
        //close pipes
        close(fd[P1_READ]);
        close(fd[P1_WRITE]);
    }
    return 0;
}