#pragma once
#include "eventGenerator.h"

#define TX(x) ((static_cast)<void (stringFSM::*)(void)>(&stringFSM:: x))

typedef enum { INIT, CH, B_INV, ESC, OK, ERROR } stateStringType;
enum EVENTS { QUOTE, CHARAC, BARRA_INV, ESCAPE };

typedef struct
{
	stateStringType nextState;
	void (*action) (void); 
}cellType;

class stringFSM
{
public:
	stringFSM(eventGenerator*);
	void nothing(void);
	void error(void);

	//acciones
	void cycle(void);

private:
	stateStringType state;
	eventGenerator* events;
	bool errorStatus;
	//									 QUOTE			 CHARAC		     BARRA_INV		   ESC	  
	const cellType tableFSM[6][4] = { { {OK, nothing},  {CH, nothing},  {B_INV, nothing}, {CH, nothing}  },		//INIT
									  { {OK, nothing},  {CH, nothing},  {B_INV, nothing}, {CH, nothing}  },		//CH
									  { {ESC, nothing}, {ERROR, error}, {B_INV, nothing}, {ESC, nothing} },		//B_INV
									  { {OK, nothing},  {CH, nothing},  {B_INV, nothing}, {CH, nothing}  },		//ESC
									  { {OK, nothing},  {OK, nothing},  {OK, nothing},    {OK, nothing}  },		//OK
									  { {ERROR, error}, {ERROR, error}, {ERROR, error},   {ERROR, error} } };	//ERROR
};