#pragma once
#include "genericFSM.h"
#include "value.h"

#define JQSTATES 5
#define JQEVENTS 3

class jsonFSM : public genericFSM
{
public:
	jsonFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], JQSTATES, JQEVENTS, INIT, events) {}

	void element(void);

	//acciones
	void cycle(void);

private:
	enum stateJSONType : stateTypes { INIT, ELEMENT, COMA, ERROR, OK };
	enum EVENTS { NO_COMA, C0MA, EOF_ };
	#define JX(x) (static_cast<void (genericFSM::* ) (void)>(&jsonFSM::x))
	//												   NOCOMA				   C0MA				    EOF_
	const cellType tableFSM[JQSTATES][JQEVENTS] = { { {ELEMENT, JX(element)}, {ERROR, JX(error)},  {OK, JX(cycleOK)}  },		//INIT
													{ {ERROR, JX(error)},	  {COMA, JX(nothing)}, {OK, JX(cycleOK)}  },		//ELEMENT
													{ {ELEMENT, JX(element)}, {ERROR, JX(error)},  {ERROR, JX(error)} },		//COMA
													{ {ERROR, JX(error)},	  {ERROR, JX(error)},  {ERROR, JX(error)} } };		//ERROR
};