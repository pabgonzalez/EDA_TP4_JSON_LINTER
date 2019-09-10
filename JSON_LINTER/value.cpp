#pragma once
#include "value.h"


void valueFSM::cycle(void)
{
	while (endCycle == false && getErrorStatus() == false)
	{
		events->getNextEvent();
		if (events->getCurrentEvent() == 't')
		{
			next(T);
		}
		else if (events->getCurrentEvent() == 'f')
		{
			next(F);
		}
		else if (events->getCurrentEvent() == 'n')
		{
			next(N);
		}
		else if (events->getCurrentEvent() == END_OF_FILE)
		{
			next(EOF_);
		}
		else
		{
			next(START_ST);
		}
	}
}

void valueFSM::createFSM(void)
{
	if (events->getCurrentEvent() == '-' || (events->getCurrentEvent() >= '0' && events->getCurrentEvent() <= '9'))
	{
		numberFSM* number = new (nothrow) numberFSM(events);
		number->cycle();
		delete number;
	}
	else if (events->getCurrentEvent() == '{')
	{
		objectFSM* object = new (nothrow) objectFSM(events);
		object->cycle();
		delete object;
	}
	else if (events->getCurrentEvent() == '"')
	{
		stringFSM* string_ = new (nothrow) stringFSM(events);
		string_->cycle();
		delete string_;
	}
	else if (events->getCurrentEvent() == '[')
	{
		arrayFSM* array_ = new (nothrow) arrayFSM(events);
		array_->cycle();
		delete array_;
	}
	else
	{
		error();
	}
}
void valueFSM::isTrue(void)
{
	if (events->getNextEvent() != 'r')
	{
		setErrorStatus(true);
	}
	else if (events->getNextEvent() != 'u')
	{
		setErrorStatus(true);
	}
	else if (events->getNextEvent() == 'e')
	{
		setErrorStatus(true);
	}
}

void valueFSM::isFalse(void)
{
	if (events->getNextEvent() != 'a')
	{
		setErrorStatus(true);
	}
	else if (events->getNextEvent() != 'l')
	{
		setErrorStatus(true);
	}
	else if (events->getNextEvent() == 's')
	{
		setErrorStatus(true);
	}
	else if (events->getNextEvent() == 'e')
	{
		setErrorStatus(true);
	}
}

void valueFSM::isNull(void)
{
	if (events->getNextEvent() != 'u')
	{
		setErrorStatus(true);
	}
	else if (events->getNextEvent() != 'l')
	{
		setErrorStatus(true);
	}
	else if (events->getNextEvent() == 'l')
	{
		setErrorStatus(true);
	}
}