#include "linter.h"

linter::linter(eventGenerator* events)
{
	error = true;
	jsonFSM jsonFSM(events);
	jsonFSM.cycle();
}