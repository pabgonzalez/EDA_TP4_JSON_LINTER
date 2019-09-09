#pragma once
#include "genericFSM.h"

bool genericFSM::errorStatus = false;

genericFSM:: genericFSM(const cellType* const table = NULL, const unsigned int rows = 0, const unsigned int columns = 0, stateTypes initState = 0, eventGenerator* events_ = NULL)
	: state(initState), rowCount(rows), columnCount(columns), pTableFSM(table), events(events_) {}

void genericFSM::setErrorStatus(bool status)
{
	if (errorStatus == true && status == false)
	{
		cout << "Cannot change errorStatus from true to false" << endl;
	}
	else
	{
		errorStatus = status;
	}
}

bool genericFSM::getErrorStatus(void)
{
	return errorStatus;
}
