#pragma once
#include "value.h"
#include "number.h"
#include "arrayFSM.h"
#include "stringFSM.h"

void cycle(void);

void valueFSM::createFSM(void)
{
	if (events->getCurrentEvent() == '-' || (events->getCurrentEvent() >= '0' && events->getCurrentEvent() <= '9'))
	{
		numberFSM * number = new numberFSM(events);
		number->cycle();
		if (number->getErrorStatus() == true)
		{
			
		}
	}
}
void isTrue(void);
void isFalse(void);
void isNull(void);