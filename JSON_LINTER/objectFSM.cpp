#include "objectFSM.h"

objectFSM::objectFSM(eventGenerator* eventG)
{
	state = INIT;
	events = eventG;
	errorStatus = false;
}

void objectFSM::cycle(void)
{
	while (events->getNextEvent != END_OF_FILE && errorStatus == false)
	{
		if (events->getCurrentEvent() == '"')
		{
			tableFSM[state][QUOTE].action();
			state = tableFSM[state][QUOTE].nextState;
		}
		else if (events->getCurrentEvent() == '}')
		{
			tableFSM[state][BRACE].action();
			state = tableFSM[state][BRACE].nextState;
		}
		else if (events->getCurrentEvent() == ':')
		{
			tableFSM[state][COLON].action();
			state = tableFSM[state][COLON].nextState;
		}
		else if (events->getCurrentEvent() == ',')
		{
			tableFSM[state][COMA].action();
			state = tableFSM[state][COMA].nextState;
		}
	}
}

void objectFSM::nothing(void)
{

}

bool objectFSM::checkValue(void)
{
	//hacer una instancia de valueFSM
	//llamar a cycle de esa instancia
}

bool objectFSM::checkString(void)
{
	//hacer una instancia de valueFSM
	//llamar a cycle de esa instancia
}

void objectFSM::error(void)
{
	errorStatus = true;
}