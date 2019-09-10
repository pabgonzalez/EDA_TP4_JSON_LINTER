#pragma once
#include "eventGenerator.h"
#include <functional>
#include <iostream>
#include <new>

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
	genericFSM(const cellType* const table, const unsigned int rows, const unsigned int columns, stateTypes initState, eventGenerator* events_);

	static bool getErrorStatus(void);
	static void setErrorStatus(bool);
protected:
	eventGenerator* events;
	const unsigned int rowCount;
	const unsigned int columnCount;
	const cellType* const pTableFSM;
	stateTypes state;
	static bool errorStatus;
};

