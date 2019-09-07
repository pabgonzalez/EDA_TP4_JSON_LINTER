
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
	lineNumber = 1;
}

eventGenerator:: ~eventGenerator()
{
	archJSON.close();
}

short eventGenerator::getNextEvent(void)
{
	char c;
	short nextEvent = NO_EVENT;
	while (archJSON.eof() == false && nextEvent == NO_EVENT)
	{
		archJSON.get(c);
		if (c == '\n')
		{
			lineNumber++;
		}
		else if (c == ' ' || c == '\t')
		{
			//do nothing
		}
		else 
		{
			nextEvent = c;
		}
	}
	if ( archJSON.eof() == true )
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