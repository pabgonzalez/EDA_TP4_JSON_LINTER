#include "stringFSM.h"

stringFSM::stringFSM(eventGenerator* eventG)
{
	state = INIT;
	events = eventG;
	errorStatus = false;
}

void stringFSM::cycle(void)
{
	while (events->getNextEvent != END_OF_FILE && error == false)
	{
		if (events->getCurrentEvent() == '"')
		{
			tableFSM[state][QUOTE].action();
			state = tableFSM[state][QUOTE].nextState;
		}
		else if (events->getCurrentEvent() == '\\')
		{
			tableFSM[state][BARRA_INV].action();
			state = tableFSM[state][BARRA_INV].nextState;
		}
		else if (events->getCurrentEvent() == '/' || events->getCurrentEvent() == 'b' || events->getCurrentEvent() == 'f' || 
			events->getCurrentEvent() == 'n' || events->getCurrentEvent() == 'r' || events->getCurrentEvent() == 't')
		{
			tableFSM[state][ESC].action();
			state = tableFSM[state][ESC].nextState;
		}
		else
		{
			tableFSM[state][CHARAC].action();
			state = tableFSM[state][CHARAC].nextState;
		}
	}
}

void stringFSM::nothing(void)
{

}

void stringFSM::error(void)
{
	errorStatus = true;
}