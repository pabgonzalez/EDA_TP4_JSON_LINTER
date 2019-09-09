#pragma once
#include "eventGenerator.h"

class genericFSM
{
public:
	void setErrorStatus(bool);
	bool getErrorStatus(void);
protected:
	bool errorStatus;
	eventGenerator* events;
};

