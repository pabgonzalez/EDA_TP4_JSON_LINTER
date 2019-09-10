#pragma once
#include <functional>
#include <iostream>
#include <new>
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
	genericFSM(const cellType* const table, const unsigned int rows, const unsigned int columns, stateTypes initState, eventGenerator* events_);

	static bool getErrorStatus(void);
	static void setErrorStatus(bool);
protected:
	void nothing(void);
	void error(void);
	void cycleOK(void);

	eventGenerator* events;
	const unsigned int rowCount;
	const unsigned int columnCount;
	const cellType* const pTableFSM;
	stateTypes state;
	bool endCycle;
	static bool errorStatus;
};

