
#include "eventGenerator.h"
#include <string>

using namespace std;


eventGenerator::eventGenerator()
{
	cout << "JSON Linter" << endl;
	cout << "Ingrese el nombre del archivo: ";
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
	event = NO_EVENT;
	c = 0;
	countChars = 0;
	countTabs = 0;
	countSpaxes = 0;
}

eventGenerator:: ~eventGenerator()
{
	archJSON.close();
}

short eventGenerator::getNextEvent(void)
{
	short event = NO_EVENT;
	while (archJSON.eof() == false && event == NO_EVENT)
	{
		archJSON.get(c);
		if (c == '\n' || c == '\r')
		{
			lineNumber++;
			countChars = 0;
			countTabs = 0;
			countSpaces = 0;
		}
		else if (c == ' ')
		{
			//do nothing
			countSpaces++;
		}
		else if (c == '\t')
		{
			countTabs++;
		}
		else 
		{
			countChars++;
			event = EVENT;
		}
	}
	if ( archJSON.eof() == true )
	{
		event = END_OF_FILE;
	}
	return event;
}

int eventGenerator::getError(void)
{
	return errorCode;
}

int eventGenerator::getLineNumber(void)
{
	return lineNumber;
}

char eventGenerator::getChar(void)
{
	return c;
}

char eventGenerator::getCurrentEvent(void)
{
	return c;
}