
#include "jsonFSM.h"
#include "value.h"


using namespace std;
using namespace std::placeholders;

void jsonFSM::cycle(void)
{
	cellType temp;
	while (endCycle == false && errorStatus == false)
	{
		events->getNextEvent();
		if (events->getCurrentEvent() == ',')
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + COMA];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][COMA].nextState;
		}
		else if (events->getCurrentEvent() == END_OF_FILE)
		{
			temp = pTableFSM[static_cast<unsigned int>(state) * columnCount + EOF_];
			auto f = bind(temp.action, this);
			f();
			state = tableFSM[state][EOF_].nextState;
			endCycle = true;
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

void jsonFSM::element(void)
{
	//hacer una instancia de valueFSM
	valueFSM* element = new (nothrow) valueFSM(events);
	//llamar a cycle de esa instancia
	element->cycle();
	delete element;
}

