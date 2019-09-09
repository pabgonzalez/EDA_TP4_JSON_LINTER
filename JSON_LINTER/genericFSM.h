#pragma once
#include "eventGenerator.h"

using stateTypes = unsigned int;

class genericFSM;

typedef struct
{
	stateTypes nextState;
	void (genericFSM::* action) (void);
}cellType;


class genericFSM
{
public:
	genericFSM(const cellType* const table, const unsigned int rows, const unsigned int columns, stateTypes initState);
	void setErrorStatus(bool);
	bool getErrorStatus(void);

protected:
	bool errorStatus;
	eventGenerator* events;
	const unsigned int rowCount;
	const unsigned int columnCount;
	const cellType* const tableFSM;
	stateTypes state;
};

