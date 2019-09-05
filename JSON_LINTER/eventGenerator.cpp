
#include "eventGenerator.h"

#include <string>

using namespace std;

#define MAX_CHAR_NAME	50

eventGenerator::eventGenerator()
{
	int open;
	char archivo[MAX_CHAR_NAME];
	cout << "JSON Linter" << endl;
	cout << "Ingrese el nombre del archivo" << endl;
	cin >> archivo;
	cout << archivo << endl;
	open = fopen_s(&archivoJSON, archivo, "r");
	cout << "Error " << open << endl;
	if (open != 0)
	{
		errorCode = FILE_NOT_OPENED;
	}
	else
	{
		errorCode = NO_ERROR;
	}
	lineNumber = 1;
}

eventGenerator:: ~eventGenerator()
{
	if (fclose(archivoJSON) == 0)
	{
		errorCode = NO_ERROR;
	}
	else
	{
		errorCode = FILE_NOT_CLOSED;
	}
}

short eventGenerator::getNextEvent(void)
{
	int c;
	short nextEvent = NO_EVENT;
	while ( (c = fgetc(archivoJSON)) != EOF && nextEvent == NO_EVENT)
	{
		if (c == '\n')
		{
			lineNumber++;
		}
		else if (c == ' ')
		{
			//do nothing
		}
		else 
		{
			nextEvent = c;
		}
	}
	if (c == EOF)
	{
		return END_OF_FILE;
	}
	return nextEvent;
}

int eventGenerator::getError(void)
{
	return errorCode;
}

int eventGenerator::getLineNumber(void)
{
	return lineNumber;
}