#pragma once
#include "genericFSM.h"
#include "value.h"

#define AQSTATES 4
#define AQEVENTS 4

class arrayFSM : public genericFSM
{
public:
	//constructor
	arrayFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], AQSTATES, AQEVENTS, INIT, events)	{}
	
	//acciones
	void value(void);

	//fsm
	void cycle(void);

private:
	enum  stateArrayType : stateTypes { INIT, VALUE, OK, ERROR };
	enum EVENTS { COMA, NO_COMA, BRACKET, EOF_ };
	#define AX(x) (static_cast<void (genericFSM::* ) (void)>(&arrayFSM:: x))
	//												   COMA				   NO_COMA			   BRACKET			   EOF_
	const cellType tableFSM[AQSTATES][AQEVENTS] = { { {ERROR, AX(error)}, {VALUE, AX(value)}, {OK, AX(cycleOK)},  {ERROR, AX(error)} },		//INIT
													{ {VALUE, AX(value)}, {ERROR, AX(error)}, {OK, AX(cycleOK)},  {ERROR, AX(error)} },		//VALUE
													{ {OK, AX(cycleOK)},  {OK, AX(cycleOK)},  {OK, AX(cycleOK)},  {OK, AX(cycleOK)} },		//OK
													{ {ERROR, AX(error)}, {ERROR, AX(error)}, {ERROR, AX(error)}, {ERROR, AX(error)} } };	//ERROR
};