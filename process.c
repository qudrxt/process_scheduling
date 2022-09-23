#include "process.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void createPCB(Pcb *pcbPtr, char inpName[], int inpArrivalTime, int inpBurstTime, int inpDeadlineTime)
{
    strcpy(pcbPtr -> processName, inpName);
    pcbPtr -> arrivalTime = inpArrivalTime;
    pcbPtr -> burstTime = inpBurstTime;
    pcbPtr -> remainingTime = inpBurstTime;
    pcbPtr -> deadlineTime = inpDeadlineTime;
    pcbPtr -> processState = READY;
    pcbPtr -> serviceTime = -1;
    pcbPtr -> turnTime;
}

char *getProcessName(Pcb *pcbPtr)
{
    return pcbPtr -> processName;
}

int getArrivalTime(Pcb *pcbPtr)
{
    return pcbPtr -> arrivalTime;
}

int getBurstTime(Pcb *pcbPtr)
{
    return pcbPtr -> burstTime;
}

int getRemainingTime(Pcb *pcbPtr)
{
    return pcbPtr -> remainingTime;
}

int getTurnTime(Pcb *pcbPtr)
{
	return pcbPtr -> turnTime;
}

int checkDeadlineMet(Pcb *pcbPtr)
{
	int turnTime = pcbPtr -> turnTime, deadTime = pcbPtr -> deadlineTime;
	
	return turnTime <= deadTime;
}

int getWaitTime(Pcb *pcbPtr)
{
	return (pcbPtr -> serviceTime) - (pcbPtr -> arrivalTime);
}

int getServiceTime(Pcb *pcbPtr)
{
	return pcbPtr -> serviceTime;
}

State getProcessState(Pcb *pcbPtr)
{
    return pcbPtr -> processState;
}

void setProcessState(Pcb *pcbPtr, State inpState)
{
	pcbPtr -> processState = inpState;
}

void decRemainingTime(Pcb *pcbPtr)
{
    pcbPtr -> remainingTime = (pcbPtr -> remainingTime) - 1;
}

void freeProcesses(Pcb **inpPA, int numberOfProcesses)
{
	// Free all processes that the array stores
	
	int i;
	
	for (i = 0; i < numberOfProcesses; i++)
	{
		free(inpPA[i]);
	}
}

void setProcesses(Pcb **inpPA, int numberOfProcesses)
{
	// Set all locations of inpPA to a Pcb 
	
	int i;
	
	for (i = 0; i < numberOfProcesses; i++)
	{
		inpPA[i] = (Pcb *) malloc(sizeof(Pcb));
	}
}

void setServiceTime(Pcb *pcbPtr, int timeOfInitService)
{
	pcbPtr -> serviceTime = timeOfInitService;
}

void setTurnTime(Pcb *pcbPtr, int compTime)
{
	pcbPtr -> turnTime = compTime - pcbPtr -> arrivalTime;
}

void writeResults(FILE *filePtr, Pcb **pcbArray, int numOfProcesses)
{
	char pName[10];
	int pWTime, pTTime, pDMet, processInd;

	// Writing loop

	for (processInd = 0; processInd < numOfProcesses; processInd++)
	{
		strcpy(pName, getProcessName(pcbArray[processInd]));
		pWTime = getWaitTime(pcbArray[processInd]);
		pTTime = getTurnTime(pcbArray[processInd]);
		pDMet = checkDeadlineMet(pcbArray[processInd]);
		
		// Append data to result file
		
		fprintf(filePtr, "%s %d %d %d\n", pName, pWTime, pTTime, pDMet);
	}
}

