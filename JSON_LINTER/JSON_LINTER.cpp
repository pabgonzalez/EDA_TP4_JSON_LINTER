// JSON_LINTER.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "eventGenerator.h"
#include "stringFSM.h"
#include "genericFSM.h"

using namespace std;


int main()
{
	eventGenerator myEvents;

	//TEST EVENT GENERATOR 
	/*int lineNumber = 0;
	cout << "testing eventgenerator" << endl;
	cout << "errorcode " << myEvents.getError() << endl;
	if (myEvents.getError() == NO_ERROR) {
		cout << "line number\tcharacters";
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
	cout << endl << "end testing eventgenerator" << endl;*/

	stringFSM fsmS(&myEvents);
	fsmS.cycle();
	cout << "ErrorStatus " << genericFSM::getErrorStatus() << endl;
}

