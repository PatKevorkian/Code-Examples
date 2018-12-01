#include "MemoryManagment.h"

//gets the user input for the number of jobs/partitions
//allocates the dynamic arrays for jobs/partitions
//gets the size of each job/partition and generates the other importnant info needed
MemoryManagment::MemoryManagment(){
    system("clear");
    
    wastedSpace=usedSpace=totalAvailSpace=0;//set attributes so they have a defualt value
    
    cout<<"+--------------------------------+"<<endl;
    cout<<"|          CSC 305 LAB 2         |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<"|         MEMORY MANAGMENT       |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<endl<<endl<<"Enter the number of partitions for the memory below"<<endl;
    
    numOfParts=0;
    string checkNumOfParts;
    bool goodinput=false;
    
    //gets the number of partitions needed for the memory, checking if the input
    //is invalid. i.e not a number or not in range
    while (!goodinput){
        try{
            cout<<"How many PARTITIONS (1-5): ";
            cin>>checkNumOfParts;
            
            if (!isNumber(checkNumOfParts)) throw 1;
            
            istringstream(checkNumOfParts) >>numOfParts;    //converts a string to an int
            
            if (numOfParts>5 || numOfParts<1) throw 0;
            
            goodinput=true;
        }
        catch (int a){
            if (a==1)
                cout<<"Error! this input is not a number. Redo: "<<endl;
            else
                cout<<"Error! this number is our of range. Redo: "<<endl;
        }
    }
    
    
    parts = new memory[numOfParts];
    system("clear");
    cout<<"Now Entering the number of partitoins of the memory"<<endl;
    
    //sets up the array with the necessary info for each partition
    for(int i = 0; i<numOfParts; i++){
        
        cout<<endl<<"Setting up Partition number: "<<i+1<<endl;
        cout<<"Enter the size of the partition below" <<endl;
        parts[i].size = getSize();//calls function for user input to get the desired size
        parts[i].usedSpace = 0;
        parts[i].freeSpace =parts[i].size;
        parts[i].partNumber = i+1;
        parts[i].status = false;
        parts[i].jobName = "NULL";
    }
    
    system("clear");
    
    cout<<"Now Entering the number of jobs to run"<<endl;

    goodinput=false;
    
    //gets the number of proccesses to run, checking if the input
    //is invalid. i.e not a number or not in range
    while (!goodinput){
        try{
            cout<<"How many Jobs (1-10): ";
            cin>>checkNumOfParts;
            
            if (!isNumber(checkNumOfParts)) throw 1;
            
            istringstream(checkNumOfParts) >> numOfJobs;    //converts a string to an int
            
            if (numOfJobs>10 || numOfJobs<1) throw 0;
            
            goodinput=true;
        }
        catch (int a){
            if (a==1)
                cout<<"Error! this input is not a number. Redo: "<<endl;
            else
                cout<<"Error! this number is our of range. Redo: "<<endl;
        }
    }
    
    jobs=new process[numOfJobs];
    
    char JobNumCharArr[3];//a buffer to hold the job number when converting from int->string
    
    string JobNum;
    
    //sets up the arry with the necessary info for each job (job number, size)
    for(int i = 0; i<numOfJobs; i++){
        if (i>8)
            sprintf(JobNumCharArr,"J%d",i+1);       //convert an int to a string
        else
            sprintf(JobNumCharArr,"J0%d",i+1);      //convert a int to a string
        
        JobNum=JobNumCharArr;
        
        cout<<endl<<"Setting up Job Number: "<<JobNum<<endl;
        cout<<"Enter the size of the partition below" <<endl;
        jobs[i].size = getSize();//calls function for user input to get the desired size
        jobs[i].name=JobNum;
        jobs[i].status=false;
    }
    
    system("clear");
}

//deallocates the memory created for the arrays
MemoryManagment::~MemoryManagment(){
    delete [] jobs;
    delete [] parts;
}

//a main display to show the user options on how to place data
void MemoryManagment::menu(){
    cout<<"+--------------------------------+"<<endl;
    cout<<"|          CSC 305 LAB 2         |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<"|         MEMORY MANAGMENT       |"<<endl;
    cout<<"+--------------------------------+"<<endl;
    cout<<"|Choose an algorithm to impliment|"<<endl;
    cout<<"|(1) First-fit                   |"<<endl;
    cout<<"|(2) Best-fit                    |"<<endl;
    cout<<"|(3) Next-fit                    |"<<endl;
    cout<<"|(4) Worst-fit                   |"<<endl;
    cout<<"|(5) Quit                        |"<<endl;
    cout<<"+--------------------------------+"<<endl;
}

//the main interface with the user. it promts the user to choose the memory managment
//method, shows the user the result, and then prompt the user to return back until
//the user decides to end the program
void MemoryManagment::MainMenu(){
    int choice=0;
    
    while (choice!=5){
        menu(); //displays the menu with choices on how to manipulate data
        bool goodinput=false;
        string choiceCheck;
        
        //gets and checks the choice to make sure it is valid
        //i.e a only a number and that the value is between 1-5
        while (!goodinput){
            try{
                cout<<"Which Memory Managment Method would you like to impliment?"<<endl;
                cout<<"Enter a number 1-5: ";
                cin>>choiceCheck;
                
                if (!isNumber(choiceCheck)) throw 1;
                
                istringstream(choiceCheck) >> choice;    //converts a string to an int
                
                if (choice>5 || choice<1) throw 0;
                
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
            firstFit();
        }
        else if (choice==2){
                bestFit();
            }
        else if (choice==3){
                nextFit();
            }
        else if (choice==4){
                worstFit();
            }
        
        //if the user doesnt choose to exit the program, the arrays and space values
        //get reset to their defualt values
        if (choice!=5){
            print();    //print out the results of the memory managment method
            cin.ignore();
            cout<<"Press any enter to return to the main menu";
            cin.get();
            ResetPartsJobs();
        }
        system("clear");
    }
}

//returns an integer greater than 0 which desginate the size of a partition or job
int  MemoryManagment::getSize(){
    bool goodinput=false;
    int num=-1;
    string checkNum;
    
    //get and check the input to make sure it is valid, a number,
    //and in range, greater than 0
    while (!goodinput){
        try{
            cout<<"Size in KB: ";
            cin>>checkNum;
            
            if (!isNumber(checkNum)) throw 1;
            
            istringstream(checkNum) >> num;    //converts a string to an int
            
            //check if the number is 0 or less, making it invlaid if so
            if (0>=num) throw 0;
            
            goodinput=true;
        }
        catch (int a){
            if (a==1)
                cout<<"Error! this input is not a number. Redo: "<<endl;
            else
                cout<<"Error! this number is our of range. Redo: "<<endl;
        }
    }
    return num;
}

//ouputs the results of the memory managment method by printing the info of each partitoin
//as well as showing the jobs that werent fit, if there were any
//as well as the total space used, wasted space and entire space avilable
void  MemoryManagment::print(){
    system("clear");
    for (int i=0; i<numOfParts; i++){
        cout<<"+-----------------------------+"<<endl;
        cout<<"|Partition: " << parts[i].partNumber<<setw(18-lenOfInt(parts[i].partNumber))<<' '<<"|"<<endl;
        cout<<"|Status: " << ((parts[i].status==true) ? "Busy                 |" : "Free                 |")<<endl;
        cout<<"|Job Name: " <<parts[i].jobName<<setw(19-(int)parts[i].jobName.length())<<' '<<"|"<<endl;
        cout<<"|Size(KB): " << parts[i].size<<setw(19-lenOfInt(parts[i].size))<<' '<<"|"<<endl;
        cout<<"|Space Used(KB): " << parts[i].usedSpace <<setw(13-lenOfInt(parts[i].usedSpace))<<' '<<"|"<<endl;
        cout<<"|Space free(KB): " << parts[i].freeSpace <<setw(13-lenOfInt(parts[i].freeSpace))<<' '<<"|"<<endl;
        usedSpace+=parts[i].usedSpace;
        wastedSpace+=parts[i].freeSpace;
        totalAvailSpace+=parts[i].size;
    }
    
    cout<<"+-----------------------------+"<<endl;
    cout<<endl;
    //show which jobs have yet to be proccessed
    for(int l = 0; l<numOfJobs; l++){
        if (!jobs[l].status)
            cout<<"Job: "<<jobs[l].name<<'('<<jobs[l].size<<" KB) is waiting to be allocated"<<endl;
    }
    cout<<endl;
    cout<<"The total space of all partitions is: "<<totalAvailSpace<< " KB"<<endl;
    cout<<"The total amount of space used is: "<<usedSpace<<" KB"<<endl;
    cout<<"The total amount of space wasted is: "<<wastedSpace<<" KB"<<endl;
    
    
}

//resets the partition back to the defualts
//resets the job status back to false
//resets the space varibles back to 0 to do another method
void  MemoryManagment::ResetPartsJobs(){
    
    for (int i=0; i<numOfParts; i++){
        parts[i].freeSpace =parts[i].size;
        parts[i].status = false;
        parts[i].jobName = "NULL";
        parts[i].usedSpace=0;
    }
    
    for ( int j=0; j<numOfJobs; j++)
        jobs[j].status=false;
    
    wastedSpace=usedSpace=totalAvailSpace=0;
}

//returns the length of an integer, this is called in print to format the output
int  MemoryManagment::lenOfInt(int num){
    if (num==0) return 1;
    int size=0;
    while (num>0){
        size++;
        num/=10;
    }
    return size;
    
}

//given a string, it will return true if the string is all numbers
//return false when the string is anything other than all numbers
bool MemoryManagment::isNumber(string num){
    for (int i=0; i<num.length(); i++)
        if (!isdigit(num[i]))
            return false;
    return true;
}

//impliments the first fit method. Each job gets placed in order into the first partition
//in memory, that is open, that the job can fit in.
void  MemoryManagment::firstFit(){
    //on every job
    for (int j=0; j< numOfJobs; j++) {
        
        //on every partition
        //if a job is already set, it will stop checking for open partitions for that job
        for (int i=0; ( i < numOfParts && !jobs[j].status ); i++){
            
            //if the job size fits in the partition size and the partition is free...
            //set a partition
            if (jobs[j].size<=parts[i].size  && !parts[i].status){
                jobs[j].status=true;
                parts[i].status=true;
                parts[i].jobName=jobs[j].name;
                parts[i].freeSpace-=jobs[j].size;
                parts[i].usedSpace=jobs[j].size;
            }
        }
    }
    
}

//impliments the best fit method. Eacho job gets placed consecutively in order into the
//partition that is open, that the job can fit into and has the least amount of free space
void MemoryManagment::bestFit(){
    
    int bestIndex;  //the index of the partition with the best (smallest) hole
    bool bestFound;   //indicates that a best partition is found
    
    //on every job
    for (int j=0; j<numOfJobs; j++){
        
        bestIndex=0;    //reset the best index
        bestFound=false;  //reset the bestFound flag
        
        //on every partition
        for (int p=0; p<numOfParts; p++){
            
            //if the partition is open and the job fits into the partition
            if (!parts[p].status && (jobs[j].size<=parts[p].size)){

                //check if there is no best partition yet,
                if (bestFound==false){
                    //if not, this is the current bestIndex
                    bestIndex=p;
                    bestFound=true;
                }
                else {
                    //there was already a best partition found.
                    //so check if this new partition is smaller than the best
                    if (parts[p].size<parts[bestIndex].size){
                        //if so this is the new index
                        bestIndex=p;
                    }
                    //note: this ignores the case that the current and best partition are
                    //equal, since it is infact, not better than the current but equal
                }
            }
        }
        
        //a best partition was found, set the statuses to true and update size/name info
        if (bestFound){
            jobs[j].status=true;
            parts[bestIndex].status=true;
            parts[bestIndex].jobName=jobs[j].name;
            parts[bestIndex].freeSpace-=jobs[j].size;
            parts[bestIndex].usedSpace=jobs[j].size;
        }
    }
}

//impliments the next fit method. Each job gets placed in order into the first partition
//in memory, that is open, that the job can fit in. the starting point of each partition
//to check is that of the previously set partition, to lessen the time to set all jobs.
//if the job is not set and the last partition is checked, it will loop around to the first
//partition and continue checking up until the last partition set (possibly checking every
//partition)
void  MemoryManagment::nextFit(){
    
    int end=numOfParts, lastSetPart=0, start=0;
    bool resetLoop=false;   //checks if the partitoins loop needs to loop around
    
    //on every job
    for (int j=0; j<numOfJobs; j++){
        
        //ove every partition
        for (int p=start; (p<end && !jobs[j].status);p++){
            
            //if the job fits into the partition and the partition is open
            if (jobs[j].size<=parts[p].size  && !parts[p].status){
                
                //set the partition/job info
                jobs[j].status=true;
                parts[p].status=true;
                parts[p].jobName=jobs[j].name;
                parts[p].freeSpace-=jobs[j].size;
                parts[p].usedSpace=jobs[j].size;
                
                //keep track of the new starting and ending points
                lastSetPart=start=p+1;
                end=numOfParts;
            }
            
            //if the partition loop reaches the end and didnt check the indexs 0 to
            //last set partition, the resetloop flag is set so it can do that
            if (p+1==end && start!=0){
                start=0;
                end=lastSetPart;
                resetLoop=true;
            }
        }
        
        //if it looped to see all indexs and the partition still wasnt set
        //we reset the search to the last set part->end
        //(going back to what it was prior to looping around
        if (resetLoop && !jobs[j].status){
            start=lastSetPart;
            end=numOfParts;
        }
        
        resetLoop=false;
    }
    
}

//impliments the worst fit algorithm. each job get set consecutively on a partition that
//has the most free space available. It does not matter if the partition already has a
//partition in it already, so there can be multiple jobs to a partition.
void MemoryManagment::worstFit(){

    int bestIndex;  //indicates that this index has the largest amount of free space
    bool bestFound; //a index was found that will be ideal to place the job in
    
    //on every job
    for (int j=0; j< numOfJobs; j++){
        
        bestIndex=0;
        bestFound=false;
        
        //over every partition
        for (int p=0; p<numOfParts; p++){
            
            //if the job fits into the partition
            if (jobs[j].size<=parts[p].freeSpace ){
                
                //if the new partition is better than the best partition, that is the new
                //best partition. (ignoring the not better sized equal sized partitions
                //if the best found flag is not set and the sizes are equal, it is the
                //best partition and then from on ignores the equal sized partitions
                if ( (parts[p].freeSpace > parts[bestIndex].freeSpace) ||
                    ( (parts[p].freeSpace == parts[bestIndex].freeSpace) && bestFound==false) ){
                    bestIndex=p;
                    bestFound=true;
                }
            }
        }
        
        //if there is a best index, add the job to the partition and update the space size
        if (bestFound){
            jobs[j].status=true;
            parts[bestIndex].status=true;
            if (parts[bestIndex].jobName=="NULL") parts[bestIndex].jobName="";
            parts[bestIndex].jobName+=jobs[j].name+" ";
            parts[bestIndex].freeSpace-=jobs[j].size;
            parts[bestIndex].usedSpace+=jobs[j].size;
        }
    }
}
