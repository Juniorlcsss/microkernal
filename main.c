#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//consts
#define MAX_PROCESSES 10

//structs
typedef struct{
    int id;
    char name[20];
    int priority;
    int burstTime;
    int arrivalTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int state; // 0 - ready, 1 - running, 2 - blocked
    int priorityQueueIndex;
    int waitingQueueIndex;
} Process;

Process* process_table[MAX_PROCESSES];
int processCount = 0;

//Create a new process
int process_builder(const char* name){
    if(processCount >= MAX_PROCESSES){
        //process table is full
        return -1;
    }
    else{
        Process* newProcess = (Process*)malloc(sizeof(Process));
        newProcess->id = processCount + 1;
        strcpy(newProcess->name, name, sizeof(newProcess->name));
        newProcess->name[sizeof(newProcess->name) -1] = '\0';
        newProcess->priority = 0;
        newProcess->burstTime = 0;
        newProcess->arrivalTime = 0;
        newProcess->remainingTime = 0;
        newProcess->completionTime = 0;
        newProcess->turnaroundTime = 0;
        newProcess->waitingTime = 0;
        newProcess->state = 0; //ready
        newProcess->priorityQueueIndex = -1;
        newProcess->waitingQueueIndex = -1;

        process_table[processCount++] = newProcess;
        return newProcess->id;
    }
}

//list processes
void process_list(){
    printf("ID\tName\tPriority\tBurst Time\tArrival Time\tRemaining Time\tCompletion Time\tTurnaround Time\tWaiting Time\tState\n");
    for(int i = 0; i < processCount; i++){
        Process* currentProcess = process_table[i];
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", currentProcess->id, currentProcess->name, currentProcess->priority, currentProcess->burstTime, currentProcess->arrivalTime, currentProcess->remainingTime, currentProcess->completionTime, currentProcess->turnaroundTime, currentProcess->waitingTime, currentProcess->state);
    }
}

//main
int main(){
    //create processes
    process_builder("Process1");
    process_builder("Process2");

    process_list();

    for(int i=0; i< processCount; i++){
        free(process_table[i]);
    }

    return 0;
}