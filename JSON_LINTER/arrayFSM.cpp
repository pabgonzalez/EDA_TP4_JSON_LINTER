#include "arrayFSM.h"

arrayFSM::arrayFSM(eventGenerator* eventG)
{
	state = INIT;
	events = eventG;
	errorStatus = false;
}

void arrayFSM::cycle(void)
{
	while (events->getNextEvent != END_OF_FILE && errorStatus == false)
	{
		if (events->getCurrentEvent() == ',')
		{
			tableFSM[state][COMA].action();
			state = tableFSM[state][COMA].nextState;
		}
		else if (events->getCurrentEvent() == ']')
		{
			tableFSM[state][BRACKET].action();
			state = tableFSM[state][BRACKET].nextState;
		}
		else
		{
			tableFSM[state][NO_COMA].action();
			state = tableFSM[state][NO_COMA].nextState;
		}
	}
}

bool arrayFSM::checkValue(void)
{
	//hacer una instancia de valueFSM
	//llamar a cycle de esa instancia
}

void arrayFSM::nothing(void)
{

}

void arrayFSM::error(void)
{
	errorStatus = true;
}
