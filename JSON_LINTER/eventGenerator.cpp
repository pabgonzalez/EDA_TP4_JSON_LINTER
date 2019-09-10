#include "eventGenerator.h"
#include <string>

using namespace std;

eventGenerator::eventGenerator()
{
	cout << "JSON Linter" << endl;
	cout << "Ingrese el nombre del archivo: ";
	cin >> archivo;
	archJSON.open(archivo, ifstream::in);
	start.open(archivo);
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
	countSpaces = 0;
	finalCount = 0;
	finalTabs = 0;
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
		if (c == '\n')	//falta \r
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
		c = END_OF_FILE;
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

char eventGenerator::getCurrentEvent(void)
{
	return c;
}

void eventGenerator::goBack(void)
{
	archJSON.putback(c);
	countChars--;
}

void eventGenerator::printfNow(void)
{
	string line;
	int count = 0;
	while (start.good())
	{
		getline(start, line);
		cout << ++count << "\t" << line << endl;
		if (count == lineNumber)
		{
			cout << "\t";
			for (int i = 0; i < (finalCount - 1); i++)
			{
				cout << " ";
			}
			for (int i = 0; i < finalTabs; i++)
			{
				cout << "\t";
			}
			cout << "^" << endl;
		}
	}
}

void eventGenerator:: setDisplayError(void)
{
	finalCount = countChars + countSpaces;
	finalTabs = countTabs;
}