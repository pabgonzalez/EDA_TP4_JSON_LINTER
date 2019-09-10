#include "linter.h"

linter::linter(eventGenerator* events)
{
	jsonFSM jsonFSM(events);
	jsonFSM.cycle();
	error = genericFSM::getErrorStatus();
}