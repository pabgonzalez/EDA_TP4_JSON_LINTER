#include "number.h"

numberFSM::numberFSM(eventGenerator* eventG)
{
	events = eventG;
	state = INIT;
	errorStatus = false;
}

void numberFSM::nothing(void){}

void numberFSM::error(void)
{
	errorStatus = true;
}

void numberFSM::cycle(void)
{
	while (events->getNextEvent != END_OF_FILE && errorStatus == false)
	{
		if (events->getCurrentEvent() >= '1' && events->getCurrentEvent() <= '9')
		{
			tableFSM[state][ONENINE].action();
			state = tableFSM[state][ONENINE].nextState;
		}
		else if (events->getCurrentEvent() == '0')
		{
			tableFSM[state][CERO].action();
			state = tableFSM[state][CERO].nextState;
		}
		else if (events->getCurrentEvent() == '-')
		{
			tableFSM[state][SIGN_MINUS].action();
			state = tableFSM[state][SIGN_MINUS].nextState;
		}
		else if (events->getCurrentEvent() == '+')
		{
			tableFSM[state][SIGN_PLUS].action();
			state = tableFSM[state][SIGN_PLUS].nextState;
		}
		else if (events->getCurrentEvent() == '.')
		{
			tableFSM[state][POINT].action();
			state = tableFSM[state][POINT].nextState;
		}
		else if (events->getCurrentEvent() == 'E'  || events->getCurrentEvent() == 'e')
		{
			tableFSM[state][E].action();
			state = tableFSM[state][E].nextState;
		}
		else
		{
			tableFSM[state][OTHER].action();
			state = tableFSM[state][OTHER].nextState;
		}
	}
}
