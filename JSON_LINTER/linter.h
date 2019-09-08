#pragma once
#include "eventGenerator.h"
#include "jsonFSM.h"

class linter
{
public:
	linter(eventGenerator* events);
private:
	bool error;
};