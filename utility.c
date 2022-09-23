#include "utility.h"

int countNumberOfLines(FILE *inpFp)
{
	int numberOfLines = 0, readChar;
	
	while (!feof(inpFp))
	{
		readChar = fgetc(inpFp);
		
		if (readChar == '\n')
		{
			numberOfLines++;
		}
	}
	
	// Reset file cursor to the beginning of the file
	
	rewind(inpFp);
	return numberOfLines;
}

int *getArrivalTimes(FILE *inpFp)
{
	int lineCount = 1, fileCount = countNumberOfLines(inpFp);
	int *arrivalTimes = (int *) malloc(sizeof(int) * fileCount + 1);
	*(arrivalTimes) = fileCount;
	
	while (lineCount <= fileCount)
	{
		fscanf(inpFp, "%*s %d %*d %*d", arrivalTimes + lineCount);
		lineCount++;
	}
	
	// Reset file cursor to the beginning of the file
	
	rewind(inpFp);
	return arrivalTimes;
}

