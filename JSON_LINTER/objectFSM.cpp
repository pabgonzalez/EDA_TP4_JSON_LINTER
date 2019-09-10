#include "objectFSM.h"

using namespace std;
using namespace std::placeholders;

void objectFSM::cycle(void)
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
		else if (events->getCurrentEvent() == '}')
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + BRACE];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][BRACE].nextState;
		}
		else if (events->getCurrentEvent() == ':')
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + COLON];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][COLON].nextState;
		}
		else if (events->getCurrentEvent() == ',')
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + COMA];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][COMA].nextState;
		}
	}
}

void objectFSM::nothing(void)
{

}

void objectFSM::checkValue(void)
{
	//hacer una instancia de valueFSM
	//llamar a cycle de esa instancia
}

void objectFSM::checkString(void)
{
	//hacer una instancia de valueFSM
	//llamar a cycle de esa instancia
}

void objectFSM::error(void)
{
	errorStatus = true;
}

void objectFSM::cycleOK(void)
{
	endCycle = true;
}