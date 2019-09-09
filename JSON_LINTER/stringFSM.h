#pragma once
#include "eventGenerator.h"
#include "genericFSM.h"

#define SQSTATES 6
#define SQEVENTS 5

enum stateStringType : stateTypes { INIT, CH, B_INV, ESC, OK, ERROR };
enum EVENTS { QUOTE, CHARAC, BARRA_INV, ESCAPE, EOF_ };

//typedef struct
//{
//	stateStringType nextState;
//	void (*action) (void);
//}cellType;

class stringFSM : public genericFSM
{
public:
	//constructor
	stringFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], SQSTATES, SQEVENTS, INIT, events) 
	{
		endCycle = false;
	}

	//acciones
	void nothing(void);
	void error(void);
	void cycleOK(void);

	//fsm
	void cycle(void);
private:
	bool endCycle;
	#define TX(x) (static_cast<void (genericFSM::* ) (void)>(&stringFSM::x))
	//												   QUOTE				 CHARAC				 BARRA_INV			   ESC				EOF_
	const cellType tableFSM[SQSTATES][SQEVENTS] = { { {OK, TX(nothing)},  {CH, TX(nothing)},  {B_INV, TX(nothing)}, {CH, TX(nothing)}, {ERROR, TX(error)}  },	//INIT
												  { {OK, TX(nothing)},  {CH, TX(nothing)},  {B_INV, TX(nothing)}, {CH, TX(nothing)}, {ERROR, TX(error)}  },		//CH
												  { {ESC, TX(nothing)}, {ERROR, TX(error)}, {B_INV, TX(nothing)}, {ESC, TX(nothing)}, {ERROR, TX(error)} },		//B_INV
												  { {OK, TX(nothing)},  {CH, TX(nothing)},  {B_INV, TX(nothing)}, {CH, TX(nothing)}, {ERROR, TX(error)}  },		//ESC
												  { {OK, TX(cycleOK)},  {OK, TX(cycleOK)},  {OK, TX(cycleOK)},    {OK, TX(cycleOK)}, {OK, TX(cycleOK)}  },		//OK
												  { {ERROR, TX(error)}, {ERROR, TX(error)}, {ERROR, TX(error)},   {ERROR, TX(error)}, {ERROR, TX(error)} } };	//ERROR
};