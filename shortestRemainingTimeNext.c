#include "process.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getActivePInd(Pcb **inpPA, int numOfProcesses)
{
	int foundProcess = 0, i = 0;
	
	while (!foundProcess && i < numOfProcesses)
	{
		// Check if process is active
	
		if (getProcessState(inpPA[i]) != EXIT)
		{
			foundProcess = 1;
		}
		
		else
		{
			i++;
		}
	}
	
	return i;
}

void findMinProcess(Pcb **inpPA, int *processInd, int numOfProcesses)
{
	int activeProcessInd = getActivePInd(inpPA, numOfProcesses), i;
	Pcb *minProcess = inpPA[activeProcessInd];
	
	for (i = activeProcessInd; i < numOfProcesses; i++)
	{
		// Check if process is active
		
		if (getProcessState(inpPA[i]) != EXIT)
		{
			// Check if process is minimal
			
			if (getRemainingTime(inpPA[i]) < getRemainingTime(minProcess))
			{
				minProcess = inpPA[i];
				activeProcessInd = i;
			}
		}
	}
	
	*(processInd) = activeProcessInd;
}

int main(int argc, char *argv[])
{
	char pName[10], *filePath;
	int pATime, pBTime, pDTime;
	int pWTime, pTTime, pDMet;
	
	// Determine if a file path has been specified
	
	filePath = argc > 1 ? argv[1] : "processes.txt";
	
	FILE *readPtr = fopen(filePath, "r"), *writePtr = fopen("srtn-results.txt", "w");
	
	// Results file has either been cleared or created
	
	writePtr = fopen("srtn-results.txt", "a");
	
	if (readPtr && writePtr)
	{
		int *arrivalTimes = getArrivalTimes(readPtr), comProcesses = 0, processInd = 0;
		int numOfProcesses = *(arrivalTimes), timeQuantum = 3, comProcess, curTime, subInd;
		Pcb **pcbArray = (Pcb **) malloc(sizeof(Pcb *) * numOfProcesses);
		int *minProcessInd = (int *) malloc(sizeof(int)), noOfArrivals = 0, quantumUsed;
		
		// Allocate memory for all processes
		
		setProcesses(pcbArray, numOfProcesses);
		
		// Add the first process into the process array
		
		fscanf(readPtr, "%s %d %d %d", pName, &pATime, &pBTime, &pDTime);
		createPCB(pcbArray[processInd], pName, pATime, pBTime, pDTime);
		
		// Set the start time as the arrival time of the first process
		
		curTime = pATime;
		
		*(minProcessInd) = 0;
		
		// Set the service time of the first process
		
		setServiceTime(pcbArray[*(minProcessInd)], curTime);
		setProcessState(pcbArray[*(minProcessInd)], RUNNING);
		
		printf("Time %d: %s has entered the system.\n", curTime, getProcessName(pcbArray[*(minProcessInd)]));
		printf("Time %d: %s is in the running state.\n", curTime, getProcessName(pcbArray[*(minProcessInd)]));
		
		noOfArrivals++;
		processInd++;
		
		while (comProcesses < *(arrivalTimes))
		{
			quantumUsed = 0;
			comProcess = 0;
			
			while (quantumUsed < timeQuantum && !comProcess)
			{
				// Check if currently executing process has completed execution
				
				if (getRemainingTime(pcbArray[*(minProcessInd)]) == 0)
				{
					printf("Time %d: %s has completed execution.\n", curTime, getProcessName(pcbArray[*(minProcessInd)]));
					
					// Set the state of the process as exited
					
					setProcessState(pcbArray[*(minProcessInd)], EXIT);
					
					// Set the turnaround time for the completed process
					
					setTurnTime(pcbArray[*(minProcessInd)], curTime);
					
					// Denote that a process has completed execution
					
					comProcess = 1;
					comProcesses++;
					
					if (comProcesses < numOfProcesses)
					{
						if (!comProcess)
						{
							// Set previously executing process to READY state
						
							setProcessState(pcbArray[*(minProcessInd)], READY);
						}
						
						// Reset minimum process
						
						findMinProcess(pcbArray, minProcessInd, noOfArrivals);
						
						// Set process to RUNNING state
						
						setProcessState(pcbArray[*(minProcessInd)], RUNNING);
					
						// Denote that execution has changed to another process
					
						printf("Time %d: %s is in the running state.\n", curTime, getProcessName(pcbArray[*(minProcessInd)]));
						
						if (getServiceTime(pcbArray[*(minProcessInd)]) == -1)
						{
							// Set the time of the process' inital service
							
							setServiceTime(pcbArray[*(minProcessInd)], curTime);
						}
					}
				}
				
				decRemainingTime(pcbArray[*(minProcessInd)]);
				
				// Check if processes have arrived
			
				while (curTime == *(arrivalTimes + (processInd + 1)))
				{
					// Add newly arrived process into array of PCBs
					
					fscanf(readPtr, "%s %d %d %d", pName, &pATime, &pBTime, &pDTime);
					createPCB(pcbArray[processInd], pName, pATime, pBTime, pDTime);
					
					printf("Time %d: %s has entered the system.\n", curTime, getProcessName(pcbArray[processInd]));
					
					processInd++;
					noOfArrivals++;
				}
				
				quantumUsed++;
				curTime++;
			}
			
			// Set previously executing process to READY state
			
			setProcessState(pcbArray[*(minProcessInd)], READY);
			
			// Reset minimum process
			
			findMinProcess(pcbArray, minProcessInd, noOfArrivals);
			
			// Set process to RUNNING state
			
			setProcessState(pcbArray[*(minProcessInd)], RUNNING);
		}
		
		writeResults(writePtr, pcbArray, numOfProcesses);
		free(minProcessInd);
		freeProcesses(pcbArray, *(arrivalTimes));
		free(pcbArray);
		free(arrivalTimes);
	}
	
	fclose(readPtr);
	fclose(writePtr);

    return 0;
}
