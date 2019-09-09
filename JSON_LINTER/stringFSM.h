#pragma once
#include "eventGenerator.h"
#include "genericFSM.h"

enum stateStringType : stateTypes { INIT, CH, B_INV, ESC, OK, ERROR };
enum EVENTS { QUOTE, CHARAC, BARRA_INV, ESCAPE };

//typedef struct
//{
//	stateStringType nextState;
//	void (*action) (void);
//}cellType;

class stringFSM : public genericFSM
{
public:
	stringFSM(eventGenerator*);
	void nothing(void);
	void error(void);

	//acciones
	void cycle(void);

private:
#define TX(x) (static_cast<void (genericFSM::* ) (void)>(&stringFSM::x))
	//									 QUOTE				 CHARAC				 BARRA_INV			   ESC	  
	const cellType tableFSM[6][4] = { { {OK, TX(nothing)},  {CH, TX(nothing)},  {B_INV, TX(nothing)}, {CH, TX(nothing)}  },		//INIT
									  { {OK, TX(nothing)},  {CH, TX(nothing)},  {B_INV, TX(nothing)}, {CH, TX(nothing)}  },		//CH
									  { {ESC, TX(nothing)}, {ERROR, TX(error)}, {B_INV, TX(nothing)}, {ESC, TX(nothing)} },		//B_INV
									  { {OK, TX(nothing)},  {CH, TX(nothing)},  {B_INV, TX(nothing)}, {CH, TX(nothing)}  },		//ESC
									  { {OK, TX(nothing)},  {OK, TX(nothing)},  {OK, TX(nothing)},    {OK, TX(nothing)}  },		//OK
									  { {ERROR, TX(error)}, {ERROR, TX(error)}, {ERROR, TX(error)},   {ERROR, TX(error)} } };	//ERROR
};