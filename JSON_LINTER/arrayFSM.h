#pragma once
#include "eventGenerator.h"
#include "genericFSM.h"

#define TX(x) ((static_cast)<void (arrayFSM::*)(void)>(&arrayFSM:: x))

typedef enum { INIT, VALUE, OK, ERROR } stateArrayType;
enum EVENTS { COMA, NO_COMA, BRACKET };

typedef struct
{
	stateArrayType nextState;
	void (*action) (void);
}cellType;

class arrayFSM : public genericFSM
{
public:
	arrayFSM(eventGenerator*);
	bool checkValue(void);
	void nothing(void);
	void error(void);

	//acciones
	void cycle(void);

private:
	stateArrayType state;
	//									 COMA				  NO_COMA			   BRACKET
	const cellType tableFSM[4][3] = { { {ERROR, error},		 {VALUE, checkValue}, {OK, nothing} },		//INIT
									  {	{VALUE, checkValue}, {ERROR, error},	  {OK, nothing} },		//VALUE
									  {	{OK, nothing},		 {OK, nothing},		  {OK, nothing} },		//OK
									  { {ERROR, error},		 {ERROR, error},	  {ERROR, error} } };	//ERROR
};