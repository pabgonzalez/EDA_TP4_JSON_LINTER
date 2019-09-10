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

void objectFSM::nothing(void){}

//void objectFSM::value(void)
//{
//	//hacer una instancia de valueFSM
//	valueFSM* value = new (nothrow) valueFSM(events);
//	//llamar a cycle de esa instancia
//	value->cycle;
//	delete value;
//}

void objectFSM::string(void)
{
	//hacer una instancia de valueFSM
	stringFSM* string = new (nothrow) stringFSM(events);
	//llamar a cycle de esa instancia
	string->cycle;
	delete string;
}

void objectFSM::error(void)
{
	errorStatus = true;
}

void objectFSM::cycleOK(void)
{
	endCycle = true;
}