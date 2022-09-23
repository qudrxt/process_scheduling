#include "process.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char pName[10], *filePath;
	int pATime, pBTime, pDTime;

	// Determine if a file path has been specified
	
	filePath = argc > 1 ? argv[1] : "processes.txt";
	
	FILE *readPtr = fopen(filePath, "r"), *writePtr = fopen("fcfs-results.txt", "w");
	
	// Results file has either been cleared or created
	
	writePtr = fopen("fcfs-results.txt", "a");
	
	if (readPtr && writePtr)
	{
		int *arrivalTimes = getArrivalTimes(readPtr), comProcesses = 0, processInd = 0;
		int numOfProcesses = *(arrivalTimes), curTime;
		Pcb **pcbArray = (Pcb **) malloc(sizeof(Pcb *) * numOfProcesses);
		
		// Allocate memory for all processes
		
		setProcesses(pcbArray, numOfProcesses);
		
		// Add the first process into the process array
		
		fscanf(readPtr, "%s %d %d %d", pName, &pATime, &pBTime, &pDTime);
		createPCB(pcbArray[processInd], pName, pATime, pBTime, pDTime);
		
		// Set the start time as the arrival time of the first process
		
		curTime = pATime;
		
		// Set the service time of the first process
		
		setServiceTime(pcbArray[processInd], curTime);
		
		printf("Time %d: %s has entered the system.\n", curTime, getProcessName(pcbArray[processInd]));
		printf("Time %d: %s is in the running state.\n", curTime, getProcessName(pcbArray[processInd]));
		
		processInd++;

		while (comProcesses < *(arrivalTimes))
		{
			// Check if currently executing process has completed execution
			
			if (getRemainingTime(pcbArray[comProcesses]) == 0)
			{
				printf("Time %d: %s has completed execution.\n", curTime, getProcessName(pcbArray[comProcesses]));
				
				// Set the turnaround time for the completed process
				
				setTurnTime(pcbArray[comProcesses], curTime);
				
				// Denote that a new process is now executing
				
				comProcesses++;
				
				if (comProcesses <= numOfProcesses-1)
				{
					printf("Time %d: %s is in the running state.\n", curTime, getProcessName(pcbArray[comProcesses]));
					
					// Set the time of the process' inital service
					
					setServiceTime(pcbArray[comProcesses], curTime);
				}
			}
			
			if (comProcesses <= numOfProcesses-1)
			{
				// Decrement the remaining time of the currently executing process
			
				decRemainingTime(pcbArray[comProcesses]);
			}
			
			// Check if processes have arrived
			
			while (curTime == *(arrivalTimes + (processInd + 1)))
			{
				// Add newly arrived process into array of PCBs
				
				fscanf(readPtr, "%s %d %d %d", pName, &pATime, &pBTime, &pDTime);
				createPCB(pcbArray[processInd], pName, pATime, pBTime, pDTime);
				
				printf("Time %d: %s has entered the system.\n", curTime, getProcessName(pcbArray[processInd]));
				
				processInd++;
			}
			
			curTime++;
		}
		
		writeResults(writePtr, pcbArray, numOfProcesses);
		freeProcesses(pcbArray, *(arrivalTimes));
		free(pcbArray);
		free(arrivalTimes);
	}
	
	fclose(readPtr);
	fclose(writePtr);

    return 0;
}
