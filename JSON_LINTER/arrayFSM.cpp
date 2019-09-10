#include "arrayFSM.h"

void arrayFSM::cycle(void)
{
	while (endCycle == false && getErrorStatus() == false)
	{
		events->getNextEvent();
		if (events->getCurrentEvent() == ',')
		{
			next(COMA);
		}
		else if (events->getCurrentEvent() == ']')
		{
			next(BRACKET);
		}
		else if (events->getCurrentEvent() == END_OF_FILE)
		{
			next(EOF_);
		}
		else
		{
			next(NO_COMA);
		}
	}
}

void arrayFSM::value(void)
{
	//hacer una instancia de valueFSM
	valueFSM* value = new (nothrow) valueFSM(events);
	//llamar a cycle de esa instancia
	value->cycle();
	delete value;
}

void arrayFSM::eatNvalue(void)
{
	events->getNextEvent();
	value();
}
