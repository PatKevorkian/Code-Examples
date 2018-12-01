#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "extraFunct.h"
using namespace std;

void InstructionFetch(char IR[]);
void InstructionDecode(char IR[], int& A, int& B, int& Imm);
void InstructionExecute(int opCode, int A, int B, int Imm, int& ALUout, int& Cond);
void MemoryAccess(int opCode, int B, int ALUout, int Cond, int& LMD);
void WriteBack(int opCode, int ALUout, int LMD);



ifstream PC;
int Regs[32];
int Memory[40];
char binarystring[17];
int opCode;

int main (void)
{
    char IR[33]="00000000000000000000000000000000";
    int A, B, Imm, ALUout, LMD, Cond;
    
    PC.open("/Users/PatrickKevorkian/Desktop/CSC Labs/Mips Simulate/Mips Simulate/Instructions.txt"); // open the input file.
    if (!PC) {cerr <<"File could not be opened\n";  exit(1); }
    
    while (!PC.eof()){
        
        InstructionFetch(IR);
        InstructionDecode(IR, A, B, Imm);
        InstructionExecute(opCode, A,B,Imm, ALUout, Cond);
        MemoryAccess(opCode, B, ALUout, Cond, LMD);
        WriteBack(opCode, ALUout, LMD);
        cout << endl;  // print end of line.
    }
    //Print out result of registers and memory
    cout<<"-----Memory and Registers after program execution-----\n\n Memory:\n\n";
    for(int i = 0; i < 8; i++)
    {
        cout<<"Memory["<<i*4<<"]="<<Memory[i*4]<<"\n";
        
    }
    cout<<"\nRegisters:\n\n";
    for(int i = 0 ; i <= 4; i++)
    {
        cout<<"R"<<i<<"="<<Regs[i]<<"\n";
    }
    getchar(); //pause
    return 1;
}

void InstructionFetch(char IR[])
{
    PC >> IR; // read the instruction
    cout <<"\nCurrent instruction: "<< IR;
    
}


//for the sake of understandability code here that could of been recycled as functions was just reused for each type of instruction
void InstructionDecode(char IR[], int& A, int& B, int& Imm)
{
  
    //get type and op code of instruction
    char OpCode[6];
    
    for(int i = 0; i < 6 ; i++)
    {
        OpCode[i] = IR[i];
    }
    
    //this switch takes in decimal representationof the 6 op code binary
    switch (ToDecimal(OpCode,6))
    {
        case 35:
        {
            //output type of instruction (this isnt the perfect way to do it but for our current purposes it works)
            cout<<"\nLW";
            
            //retrieve and translate the registers needed and address/immediate for lw and this i-type instrucion
            char lwRS[4], lwRT[4], lwImed[16];
            int j=0;
            
            //gettign sounce and destination
            for (int i = 6; i < 11; i++)
            {
                
                lwRS[j]=IR[i];
                lwRT[j]=IR[i+5];
                j++;
            }
            
            //getting address/immediate
            j=0;
            for(int i = 16; i < 32; i++)
            {
                lwImed[j]=IR[i];
                j++;
            }
            
            //assigning apropriate variables
            opCode=35;
            B=ToDecimal(lwRT, 5);
            A=ToDecimal(lwRS,5);
            Imm=ToDecimal(lwImed,16);
            
            //print assembler instruction
            cout<<" R"<<ToDecimal(lwRT, 5)<<","<<ToDecimal(lwImed,16)<<"(R"<<ToDecimal(lwRS,5)<<")\n";
        }
            break;
        case 43:
        {
            cout<<"\nSW";
            
            //retrieve and translate the registers needed and address/immediate for sw and this i-type instrucion
            char swRS[5], swRT[5], swImed[16];
            int j=0;
            
            //gettign source and destination
            for (int i = 6; i < 11; i++)
            {
                
                swRS[j]=IR[i];
                swRT[j]=IR[i+5];
                j++;
            }
            
            //getting address/immediate
            j=0;
            for(int i = 16; i < 32; i++)
            {
                swImed[j]=IR[i];
                j++;
            }
            
            //assign apropriate variables
            opCode=43;
            B=ToDecimal(swRT, 5);
            A=ToDecimal(swRS,5);
            Imm=ToDecimal(swImed,16);
            
            //print out assembler instruction
            cout<<" R"<<ToDecimal(swRT, 5)<<","<<ToDecimal(swImed,16)<<"(R"<<ToDecimal(swRS,5)<<")\n";
            
        }
            break;
        case 0:
        {
            cout<<"\nADD";
            
            //retrieve and translate the registers needed and address/immediate for add and this i-type instrucion
            char addRS[5], addRT[5], addRD[5];
            int j=0;
            
            //gettig sounce and destination
            for (int i = 6; i < 11; i++)
            {
                
                addRS[j]=IR[i];
                addRT[j]=IR[i+5];
                addRD[j]=IR[i+10];
                j++;
            }
            
            //assign appropriate variables
            opCode=0;
            B=ToDecimal(addRT, 5);
            A=ToDecimal(addRS,5);
            Imm=ToDecimal(addRD,5);
            
            //print out assembler instruction
            cout<<" R"<<ToDecimal(addRD,5)<<", R"<<ToDecimal(addRT, 5)<<","<<"R"<<ToDecimal(addRS,5)<<"\n";

        }
            break;
        case 34:
        {
            cout<<"\nSUB";
            
            //retrieve and translate the registers needed and address/immediate for sub and this i-type instrucion
            char subRS[5], subRT[5], subRD[16];
            int j=0;
            
            //gettign sounce and destination
            for (int i = 6; i < 11; i++)
            {
                
                subRS[j]=IR[i];
                subRT[j]=IR[i+5];
                subRD[j]=IR[i+10];
                j++;
            }
            
            //assigneing apropriate variables
            opCode=34;
            B=ToDecimal(subRT, 5);
            A=ToDecimal(subRS,5);
            Imm=ToDecimal(subRD,16);
            
            //print out assembler instruction
            cout<<" R"<<ToDecimal(subRD,5)<<", R"<<ToDecimal(subRT, 5)<<","<<"R"<<ToDecimal(subRS,5)<<"\n";
            
        }
            break;
        case 8:
        {
            cout<<"\nADDI";
            
            //retrieve and translate the registers needed and address/immediate for addi and this i-type instrucion
            char adiRS[5], adiRT[5], adiImed[16];
            int j=0;
            
            //gettign sounce and destination
            for (int i = 6; i < 11; i++)
            {
                
                adiRS[j]=IR[i];
                adiRT[j]=IR[i+5];
                j++;
            }
            //getting address/immediate
            j=0;
            for(int i = 16; i < 32; i++)
            {
                adiImed[j]=IR[i];
                j++;
            }
            
            //assigning appropriate variables
            opCode=8;
            B=ToDecimal(adiRT, 5);
            A=ToDecimal(adiRS,5);
            Imm=ToDecimal(adiImed,16);
            
            //printing assembler instruction
            cout<<" R"<<ToDecimal(adiRT, 5)<<","<<"R"<<ToDecimal(adiRS,5)<<","<<ToDecimal(adiImed,16)<<"\n";
        }
            break;
        //case 4:
            //cout<<"\nBEQ";
            //break;
        case 5:
        {
            cout<<"\nBNE";
            
            //retrieve and translate the registers needed and address/immediate for bne and this i-type instrucion
            char bneRS[5], bneRT[5], bneImed[16];
            int j=0;
            int twosComp;
            
            //gettign sounce and destination
            for (int i = 6; i < 11; i++)
            {
                
                bneRS[j]=IR[i];
                bneRT[j]=IR[i+5];
                j++;
            }
            //getting address/immediate
            j=0;
            for(int i = 16; i < 32; i++)
            {
                bneImed[j]=IR[i];
                j++;
            }
            
            //get complement of the imm
            Complement(bneImed);
            
            //get two's comp
            twosComp=(ToDecimal(bneImed,16)+1)-(2*(ToDecimal(bneImed,16)+1));
            
            //assign appropriate variables
            opCode=5;
            B=ToDecimal(bneRT, 5);
            A=ToDecimal(bneRS,5);
            Imm=twosComp;
            
            //print the assembler instruction
            cout<<" R"<<ToDecimal(bneRS,5)<<","<<"R"<<ToDecimal(bneRT, 5)<<","<<twosComp<<"\n";
            
        }
            break;
        default:
            cout<<"\nInstruction not recognized!";
            break;
    }
}

void InstructionExecute(int opCode, int A, int B, int Imm, int& ALUout, int& Cond)
{
    switch(opCode)
    {
        //calculation for lw instruction with apropriate register and imm
        case 35:
            ALUout =Regs[A] + Imm;
            break;
        //calculation for sw instruction w/ apropriate register and imm
        case 43:
            ALUout = Regs[A] + Imm;
            break;
        //calcualation for add instruction with apropriate registers
        case 0:
            ALUout = Regs[A] + Regs[Imm];
            break;
        //calculation for sub instruction with appropriate registers
        case 34:
            ALUout = Regs[A] - Regs[Imm];
            break;
        case 8:
        //calculation for addi instruction with appropriate register and imm
            ALUout = Regs[A] + Imm;
            break;
        //calculation for bne instruction to decrement the program counter
        case 5:
            ALUout = (Imm * 32) - 10 ;
            Cond = Regs[B] - Regs[A];
            break;
            
    }
    
}

void MemoryAccess(int opCode, int B, int ALUout, int Cond, int& LMD)
{
    switch(opCode)
    {
        //Print and assignment of memory access for lw instruction
        case 35:
            LMD = Memory[ALUout];
            Regs[B] = LMD;
            cout << "Register" << "[" << B << "] = ";
            break;
        //print ans assignement of memory access for sw instruction
        case 43:
            Memory[ALUout] = Regs[B];
            cout << "Memory" << "[" <<ALUout << "] = " << Regs[B];
            break;
        //print and assignemnt of reg for add instruction
        case 0:
            Regs[B] = ALUout;
            cout << "Register" << "[" << B << "] = ";
            break;
        //print and assignemnt of reg for sub instruction
        case 34:
            Regs[B] = ALUout;
            cout << "Register" << "[" << B << "] = ";
            break;
        //print and assignment of reg for addi instruction
        case 8:
            Regs[B] = ALUout;
            cout << "Register" << "[" << B << "] = ";
            break;
        //decrementing pc for bne instruction, printing out loop
        case 5:
            if(Cond != 0)
            {
                //.seekg allows finding arbitrary spot in a file
                PC.seekg(ALUout, ios::end);
                cout << "Loop";
            }
            break;
            
    }
}

void WriteBack(int opCode, int ALUout, int LMD)
{
    switch(opCode)
    {
        //printing out/ write back for alu, lmd, and breaking where needed
        case 35:
            cout << LMD;
            break;
        case 43:
            break;
        case 0:
            cout<<ALUout;
            break;
        case 34:
            cout<<ALUout;
            break;
        case 8:
            cout<<ALUout;
            break;
        case 5:
            break;
    
    }
}
