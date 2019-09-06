
#include "eventGenerator.h"

#include <string>

using namespace std;


eventGenerator::eventGenerator()
{
	cout << "JSON Linter" << endl;
	cout << "Ingrese el nombre del archivo" << endl;
	cin >> archivo;
	archJSON.open(archivo, ifstream::in);
	if (archJSON.is_open() == true)
	{
		errorCode = NO_ERROR;
	}
	else
	{
		errorCode = FILE_NOT_OPENED;
	}
	cout << "errorCode " << errorCode << endl;
	lineNumber = 1;
}

eventGenerator:: ~eventGenerator()
{
	archJSON.close();
}

short eventGenerator::getNextEvent(void)
{
	int c;
	short nextEvent = NO_EVENT;
	while ( (c = archJSON.get()) != EOF && nextEvent == NO_EVENT)
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