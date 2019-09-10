#include "stringFSM.h"

void stringFSM::cycle(void)
{
	while (endCycle == false && getErrorStatus() == false)
	{
		events->getNextEvent();
		if (events->getCurrentEvent() == '"')
		{
			next(QUOTE);
		}
		else if (events->getCurrentEvent() == '\\')
		{
			next(BARRA_INV);
		}
		else if (events->getCurrentEvent() == END_OF_FILE)
		{
			next(EOF_);
		}
		else if (events->getCurrentEvent() == '/' || events->getCurrentEvent() == 'b' || events->getCurrentEvent() == 'f' || events->getCurrentEvent() == 'n' ||
			events->getCurrentEvent() == 'r' || events->getCurrentEvent() == 't' || events->getCurrentEvent() == '\\' || events->getCurrentEvent() == '"')
		{
			next(ESC);
		}
		else
		{
			next(CHARAC);
		}
	}
}