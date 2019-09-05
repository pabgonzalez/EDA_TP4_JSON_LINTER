#pragma once

#include <iostream>

enum errors { NO_ERROR, FILE_NOT_OPENED, FILE_NOT_CLOSED };
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
	FILE* archivoJSON;
	int lineNumber;
	int errorCode;
};