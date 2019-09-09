#pragma once
#include "genericFSM.h"

genericFSM::genericFSM(const cellType* const table, const unsigned int rows, const unsigned int columns, stateTypes initState)
	: state(initState), rowCount(rows), columnCount(columns), tableFSM(table) {}

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
