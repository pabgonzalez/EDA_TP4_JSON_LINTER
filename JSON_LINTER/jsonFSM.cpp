#include "jsonFSM.h"
#include "value.h"

void jsonFSM::cycle(void)
{
	cellType temp;
	while (endCycle == false && errorStatus == false)
	{
		events->getNextEvent();
		if (events->getCurrentEvent() == ',')
		{
			next(COMA);
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

void jsonFSM::element(void)
{
	//hacer una instancia de valueFSM
	valueFSM* element = new (nothrow) valueFSM(events);
	//llamar a cycle de esa instancia
	element->cycle();
	delete element;
}

