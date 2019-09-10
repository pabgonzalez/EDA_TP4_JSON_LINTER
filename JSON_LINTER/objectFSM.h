#pragma once

#include "genericFSM.h"
#include "value.h"
#include "stringFSM.h"

#define OQSTATES 5
#define OQEVENTS 5


class objectFSM : public genericFSM
{
public:
	//constructor
	objectFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], OQSTATES, OQEVENTS, INIT, events)
	{
		endCycle = false;
	}

	//acciones
	void value(void);
	void string(void);
	void eatNvalue(void);
	void eatNstring(void);
	//fsm
	void cycle(void);

private:
	enum stateObjectType : stateTypes { INIT, STRING, VALUE, OK, ERROR };
	enum EVENTS { QUOTE, BRACE, COMA, COLON, OTHER };
	
	#define OX(x) (static_cast<void (genericFSM::* ) (void)>(&objectFSM::x))
	//												   QUOTE				   BRACE			   COMA					 COLON				 OTHER
	const cellType tableFSM[OQSTATES][OQEVENTS] = { { {STRING, OX(string)},   {OK, OX(nothing)},  {ERROR, OX(error)},	{ERROR, OX(error)},	{ERROR, OX(error)} },		//INIT
													{ {ERROR, OX(error)},	  {ERROR, OX(error)}, {ERROR, OX(error)},	{VALUE, OX(eatNvalue)}, {ERROR, OX(error)} },		//STRING
													{ {ERROR, OX(error)},	  {OK, OX(cycleOK)},  {STRING, OX(eatNstring)}, {ERROR, OX(error)},	{ERROR, OX(error)} },		//VALUE
													{ {OK, OX(cycleOK)},	  {OK, OX(cycleOK)},  {OK, OX(cycleOK)},	{OK, OX(cycleOK)},	{OK, OX(cycleOK)} },			//OK
													{ {ERROR, OX(error)},	  {ERROR, OX(error)}, {ERROR, OX(error)},	{ERROR, OX(error)},	{ERROR, OX(error)} } };		//ERROR
};