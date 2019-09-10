#include "number.h"

void numberFSM::cycle(void)
{
	do
	{
		if (events->getCurrentEvent() >= '1' && events->getCurrentEvent() <= '9')
		{
			next(ONENINE);
		}
		else if (events->getCurrentEvent() == '0')
		{
			next(CER0);
		}
		else if (events->getCurrentEvent() == '-')
		{
			next(SIGN_MINUS);
		}
		else if (events->getCurrentEvent() == '+')
		{
			next(SIGN_PLUS);
		}
		else if (events->getCurrentEvent() == '.')
		{
			next(P0INT);
		}
		else if (events->getCurrentEvent() == 'E'  || events->getCurrentEvent() == 'e')
		{
			next(EXPO);
		}
		else if (events->getCurrentEvent() == END_OF_FILE)
		{
			next(EOF_);
		}
		else
		{
			next(OTHER);
		}
		events->getNextEvent();
	} while (endCycle == false && errorStatus == false);
}