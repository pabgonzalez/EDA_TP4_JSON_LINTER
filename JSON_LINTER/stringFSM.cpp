
#include "stringFSM.h"
#include <functional>
#include <iostream>

using namespace std;
using namespace std::placeholders;


void stringFSM::cycle(void)
{
	cellType temp;
	while (endCycle == false && getErrorStatus() == false)
	{
		events->getNextEvent();
		if (events->getCurrentEvent() == '"')
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + QUOTE];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][QUOTE].nextState;
		}
		else if (events->getCurrentEvent() == '\\')
		{
			cellType temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + BARRA_INV];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][BARRA_INV].nextState;
		}
		else if (events->getCurrentEvent() == END_OF_FILE)
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + EOF_];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][EOF_].nextState;
			endCycle = true;
		}
		else if (events->getCurrentEvent() == '/' || events->getCurrentEvent() == 'b' || events->getCurrentEvent() == 'f' || 
			events->getCurrentEvent() == 'n' || events->getCurrentEvent() == 'r' || events->getCurrentEvent() == 't')
		{
			cellType temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + ESC];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][ESC].nextState;
		}
		else
		{
			cellType temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + CHARAC];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][CHARAC].nextState;
		}
	}
}

void stringFSM::nothing(void)
{
	printf("nothing\n");
}

void stringFSM::error(void)
{
	printf("error\n");
	setErrorStatus(true);
}

void stringFSM::cycleOK(void)
{
	endCycle = true;
}