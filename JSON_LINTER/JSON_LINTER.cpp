// JSON_LINTER.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "eventGenerator.h"

using namespace std;



int main()
{
	eventGenerator myEvents;
	//TEST EVENT GENERATOR 
	
	int lineNumber = 0;
	cout << "Testing eventGenerator" << endl;
	cout << "errorCode " << myEvents.getError() << endl;
	if (myEvents.getError() == NO_ERROR) {
		cout << "Line Number\tCharacters";
		short event;
		while ( (event = myEvents.getNextEvent()) != END_OF_FILE)
		{
			if ((lineNumber != myEvents.getLineNumber()))
			{
				lineNumber++;
				cout << endl << myEvents.getLineNumber() << "\t\t";
			}
			cout << myEvents.getChar();
		}
	}
	cout << endl << "END Testing eventGenerator" << endl;
	

}

