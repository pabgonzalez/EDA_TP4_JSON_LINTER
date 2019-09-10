#pragma once

#include <iostream>
#include <fstream>
#define MAX_CHAR_NAME	50

using namespace std;

enum errors { NO_ERROR, FILE_NOT_OPENED };
typedef enum { NO_EVENT = -2, END_OF_FILE , EVENT} eventType;

class eventGenerator 
{
public:
	eventGenerator();
	~eventGenerator();
	short getNextEvent(void);
	int getError(void); 
	int getLineNumber(void);
	char getCurrentEvent(void);
	void printfNow(void);
	void goBack(void);
private:
	ifstream archJSON;
	ifstream start;
	int lineNumber;
	int errorCode;
	char archivo[MAX_CHAR_NAME];
	char c;
	int countChars;
	int countTabs;
	int countSpaces;
	eventType event;
};