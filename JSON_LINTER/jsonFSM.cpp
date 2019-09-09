#include "jsonFSM.h"

jsonFSM::jsonFSM(eventGenerator* eventG)
{
	state = INIT;
	events = eventG;
	errorStatus = false;
}

void jsonFSM::cycle(void)
{
	while (events->getNextEvent != END_OF_FILE && errorStatus == false)
	{
		if (events->getCurrentEvent() == ',')
		{
			tableFSM[state][COMA].action();
			state = tableFSM[state][COMA].nextState;
		}
		else
		{
			tableFSM[state][NO_COMA].action();
			state = tableFSM[state][NO_COMA].nextState;
		}
	}
}

void jsonFSM::element(void)
{
	//hacer una instancia de valueFSM
	//llamar a cycle de esa instancia
}

void jsonFSM::coma(void)
{
	
}

void jsonFSM::error(void)
{
	errorStatus = true;
}