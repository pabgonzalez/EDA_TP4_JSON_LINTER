#pragma once
#include "eventGenerator.h"
#include "genericFSM.h"

#define OQSTATES 5
#define OQEVENTS 5

enum stateObjectType : stateTypes { INIT, STRING, VALUE, OK, ERROR };
enum EVENTS { QUOTE, BRACE, COMA, COLON, OTHER };

//typedef struct
//{
//	stateObjectType nextState;
//	void (*action) (void);
//}cellType;

class objectFSM : public genericFSM
{
public:
	//constructor
	objectFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], OQSTATES, OQEVENTS, INIT, events)
	{
		endCycle = false;
	}

	//acciones
	void checkValue(void);
	void checkString(void);
	void nothing(void);
	void error(void);
	void cycleOK(void);

	//fsm
	void cycle(void);

private:
	bool endCycle;
	#define TX(x) (static_cast<void (genericFSM::* ) (void)>(&objectFSM::x))
	//												   QUOTE						BRACE				COMA					   COLON					OTHER
	const cellType tableFSM[OQSTATES][OQEVENTS] = { { {STRING, TX(checkString)},   {OK, TX(nothing)},  {ERROR, TX(error)},		  {ERROR, TX(error)},	   {ERROR, TX(error)} },		//INIT
													{ {ERROR, TX(error)},		   {ERROR, TX(error)}, {ERROR, TX(error)},		  {VALUE, TX(checkValue)}, {ERROR, TX(error)} },		//STRING
													{ {ERROR, TX(error)},		   {OK, TX(cycleOK)},  {STRING, TX(checkString)}, {ERROR, TX(error)},	   {ERROR, TX(error)} },		//VALUE
													{ {OK, TX(cycleOK)},		   {OK, TX(cycleOK)},  {OK, TX(cycleOK)},		  {OK, TX(cycleOK)},	   {OK, TX(cycleOK)} },			//OK
													{ {ERROR, TX(error)},		   {ERROR, TX(error)}, {ERROR, TX(error)},		  {ERROR, TX(error)},	   {ERROR, TX(error)} } };		//ERROR
};