#ifndef PROCESS_DOT_H
#define PROCESS_DOT_H

#include <stdio.h>

typedef enum {
    READY, RUNNING, EXIT
} State;

typedef struct {
    char processName[10];
    int arrivalTime, burstTime, remainingTime, deadlineTime, serviceTime, turnTime;
    State processState;
} Pcb;

void createPCB(Pcb *pcbPtr, char inpName[], int inpArrivalTime, int inpBurstTime, int inpDeadlineTime);
char *getProcessName(Pcb *pcbPtr);
int getArrivalTime(Pcb *pcbPtr);
int getBurstTime(Pcb *pcbPtr);
int getRemainingTime(Pcb *pcbPtr);
int getTurnTime(Pcb *pcbPtr);
int checkDeadlineMet(Pcb *pcbPtr);
int getWaitTime(Pcb *pcbPtr);
int getServiceTime(Pcb *pcbPtr);
State getProcessState(Pcb *pcbPtr);
void setProcessState(Pcb *pcbPtr, State inpState);
void decRemainingTime(Pcb *pcbPtr);
void freeProcesses(Pcb **inpPA, int numberOfProcesses);
void setProcesses(Pcb **inpPA, int numberOfProcesses);
void setServiceTime(Pcb *pcbPtr, int timeOfInitService);
void setTurnTime(Pcb *pcbPtr, int compTime);
void writeResults(FILE *filePtr, Pcb **pcbArray, int numOfProcesses);

#endif
