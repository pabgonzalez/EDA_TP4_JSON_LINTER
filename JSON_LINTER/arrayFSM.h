#pragma once
#include "eventGenerator.h"
#include "genericFSM.h"
//#include "value.h"

#define AQSTATES 4
#define AQEVENTS 3

enum  stateArrayType : stateTypes { INIT, VALUE, OK, ERROR };
enum EVENTS { COMA, NO_COMA, BRACKET };

//typedef struct
//{
//	stateArrayType nextState;
//	void (*action) (void);
//}cellType;

class arrayFSM : public genericFSM
{
public:
	//constructor
	arrayFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], AQSTATES, AQEVENTS, INIT, events)
	{
		endCycle = false;
	}
	
	//acciones
	void value(void);

	//fsm
	void cycle(void);

private:
	bool endCycle;
	#define TX(x) (static_cast<void (genericFSM::* ) (void)>(&arrayFSM:: x))
	//												   COMA						NO_COMA					 BRACKET
	const cellType tableFSM[AQSTATES][AQEVENTS] = { { {ERROR, TX(error)},	   {VALUE, TX(value)}, {OK, TX(cycleOK)} },		//INIT
													{ {VALUE, TX(value)}, {ERROR, TX(error)},		{OK, TX(cycleOK)} },		//VALUE
													{ {OK, TX(cycleOK)},	   {OK, TX(cycleOK)},		{OK, TX(cycleOK)} },		//OK
													{ {ERROR, TX(error)},	   {ERROR, TX(error)},		{ERROR, TX(error)} } };		//ERROR
};