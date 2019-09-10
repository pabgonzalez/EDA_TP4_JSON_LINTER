#include "arrayFSM.h"

using namespace std;
using namespace std::placeholders;

void arrayFSM::cycle(void)
{
	cellType temp;
	while (endCycle == false && getErrorStatus() == false)
	{
		events->getNextEvent();
		if (events->getCurrentEvent() == ',')
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + COMA];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][COMA].nextState;
		}
		else if (events->getCurrentEvent() == ']')
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + BRACKET];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][BRACKET].nextState;
		}
		else
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + NO_COMA];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][NO_COMA].nextState;
		}
	}
}

//void arrayFSM::value(void)
//{
//	//hacer una instancia de valueFSM
//	valueFSM* value = new (nothrow) valueFSM(events);
//	//llamar a cycle de esa instancia
//	value->cycle;
//	delete value;
//}