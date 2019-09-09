#pragma once
#include "genericFSM.h"

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
