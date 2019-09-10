#pragma once
#include "genericFSM.h"

#define SQSTATES 6
#define SQEVENTS 5

enum stateStringType : stateTypes { INIT, CH, B_INV, ESC, OK, ERROR };
enum EVENTS { QUOTE, CHARAC, BARRA_INV, ESCAPE, EOF_ };

class stringFSM : public genericFSM
{
public:
	//constructor
	stringFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], SQSTATES, SQEVENTS, INIT, events) {}

	//acciones

	//fsm
	void cycle(void);
private:
	#define TX(x) (static_cast<void (genericFSM::* ) (void)>(&stringFSM::x))
	//												   QUOTE				 CHARAC				 BARRA_INV			   ESC				EOF_
	const cellType tableFSM[SQSTATES][SQEVENTS] = { { {OK, TX(cycleOK)},  {CH, TX(nothing)},  {B_INV, TX(nothing)}, {CH, TX(nothing)}, {ERROR, TX(error)}  },	//INIT
												  { {OK, TX(cycleOK)},  {CH, TX(nothing)},  {B_INV, TX(nothing)}, {CH, TX(nothing)}, {ERROR, TX(error)}  },		//CH
												  { {ESC, TX(nothing)}, {ERROR, TX(error)}, {ESC, TX(nothing)}, {ESC, TX(nothing)}, {ERROR, TX(error)} },		//B_INV
												  { {OK, TX(nothing)},  {CH, TX(nothing)},  {B_INV, TX(nothing)}, {CH, TX(nothing)}, {ERROR, TX(error)}  },		//ESC
												  { {OK, TX(cycleOK)},  {OK, TX(cycleOK)},  {OK, TX(cycleOK)},    {OK, TX(cycleOK)}, {OK, TX(cycleOK)}  },		//OK
												  { {ERROR, TX(error)}, {ERROR, TX(error)}, {ERROR, TX(error)},   {ERROR, TX(error)}, {ERROR, TX(error)} } };	//ERROR
};