#pragma once
#include "value.h"
#include "number.h"
#include "arrayFSM.h"
#include "stringFSM.h"
#include "objectFSM.h"

using namespace std;
using namespace std::placeholders;

void valueFSM::cycle(void)
{
	cellType temp;
	while (endCycle == false && getErrorStatus() == false)
	{
		events->getNextEvent();
		if (events->getCurrentEvent() == 't')
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + T];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][T].nextState;
		}
		else if (events->getCurrentEvent() == 'f')
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + F];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][F].nextState;
		}
		else if (events->getCurrentEvent() == 'n')
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + N];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][N].nextState;
		}
		else if (events->getCurrentEvent() == END_OF_FILE)
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + EOF_];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][EOF_].nextState;
		}
		else
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + START_ST];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][START_ST].nextState;
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
		arrayFSM* array = new (nothrow) arrayFSM(events);
		array->cycle();
		delete array;
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
