#pragma once
#include <functional>
#include <iostream>
#include <new>
#include "eventGenerator.h"
#include <functional>
#include <iostream>
#include <new>

using namespace std;
using namespace std::placeholders;
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
	void next(int event);

	static bool getErrorStatus(void);
	static void setErrorStatus(bool);
protected:
	void nothing(void);
	void error(void);
	void cycleOK(void);
	cellType temp;
	eventGenerator* events;
	const unsigned int rowCount;
	const unsigned int columnCount;
	const cellType* const pTableFSM;
	stateTypes state;
	bool endCycle;
	static bool errorStatus;
};

