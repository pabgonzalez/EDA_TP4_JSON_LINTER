#pragma once
#include "eventGenerator.h"
#include "genericFSM.h"

#define SQSTATES 6
#define SQEVENTS 5

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
	enum stateStringType : stateTypes { INIT, CH, B_INV, ESC, OK, ERROR };
	enum EVENTS { QUOTE, CHARAC, BARRA_INV, ESCAPE, EOF_ };
	bool endCycle;
	#define SX(x) (static_cast<void (genericFSM::* ) (void)>(&stringFSM::x))
	//												   QUOTE			   CHARAC			   BARRA_INV			 ESC				 EOF_
	const cellType tableFSM[SQSTATES][SQEVENTS] = { { {OK, SX(cycleOK)},  {CH, SX(nothing)},  {B_INV, SX(nothing)}, {CH, SX(nothing)},  {ERROR, SX(error)} },		//INIT
													{ {OK, SX(cycleOK)},  {CH, SX(nothing)},  {B_INV, SX(nothing)}, {CH, SX(nothing)},  {ERROR, SX(error)} },		//CH
													{ {ESC, SX(nothing)}, {ERROR, SX(error)}, {ESC, SX(nothing)},	{ESC, SX(nothing)}, {ERROR, SX(error)} },		//B_INV
													{ {OK, SX(nothing)},  {CH, SX(nothing)},  {B_INV, SX(nothing)}, {CH, SX(nothing)},  {ERROR, SX(error)} },		//ESC
													{ {OK, SX(cycleOK)},  {OK, SX(cycleOK)},  {OK, SX(cycleOK)},    {OK, SX(cycleOK)},  {OK, SX(cycleOK)} },		//OK
													{ {ERROR, SX(error)}, {ERROR, SX(error)}, {ERROR, SX(error)},   {ERROR, SX(error)}, {ERROR, SX(error)} } };		//ERROR
};