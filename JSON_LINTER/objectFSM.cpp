#include "objectFSM.h"


void objectFSM::cycle(void)
{
	while (endCycle == false && getErrorStatus() == false)
	{
		events->getNextEvent();
		if (events->getCurrentEvent() == '"')
		{
			next(QUOTE);
		}
		else if (events->getCurrentEvent() == '}')
		{
			next(BRACE);
		}
		else if (events->getCurrentEvent() == ':')
		{
			next(COLON);
		}
		else if (events->getCurrentEvent() == ',')
		{
			next(COMA);
		}
	}
}

void objectFSM::value(void)
{
	//hacer una instancia de valueFSM
	valueFSM* value = new (nothrow) valueFSM(events);
	//llamar a cycle de esa instancia
	value->cycle();
	delete value;
}

void objectFSM::string(void)
{
	//hacer una instancia de valueFSM
	stringFSM* string = new (nothrow) stringFSM(events);
	//llamar a cycle de esa instancia
	string->cycle();
	delete string;
}

void objectFSM::eatNvalue(void)
{
	events->getNextEvent();
	value();
}

void objectFSM::eatNstring(void)
{
	events->getNextEvent();
	string();
}