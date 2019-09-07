#pragma once

#include <iostream>
#include <fstream>
#define MAX_CHAR_NAME	50

using namespace std;

enum errors { NO_ERROR, FILE_NOT_OPENED };
enum events { NO_EVENT = -2, END_OF_FILE };

class eventGenerator 
{
public:
	eventGenerator();
	~eventGenerator();
	short getNextEvent(void);
	int getError(void); 
	int getLineNumber(void);

private:
	ifstream archJSON;
	int lineNumber;
	int errorCode;
	char archivo[MAX_CHAR_NAME];
};