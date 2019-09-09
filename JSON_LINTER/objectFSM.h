#pragma once
#include "eventGenerator.h"

#define TX(x) ((static_cast)<void (objectFSM::*)(void)>(&objectFSM:: x))

typedef enum { INIT, STRING, VALUE, OK, ERROR } stateObjectType;
enum EVENTS { QUOTE, BRACE, COMA, COLON, OTHER };

typedef struct
{
	stateObjectType nextState;
	void (*action) (void);
}cellType;

class objectFSM
{
public:
	objectFSM(eventGenerator*);
	bool checkValue(void);
	bool checkString(void);
	void nothing(void);
	void error(void);

	//acciones
	void cycle(void);

private:
	stateObjectType state;
	eventGenerator* events;
	bool errorStatus;
	//									 QUOTE					BRACE			COMA				   COLON			    OTHER
	const cellType tableFSM[5][5] = { { {STRING, checkString}, {OK, nothing},  {ERROR, error},		  {ERROR, error},	   {ERROR, error} },		//INIT
									  { {ERROR, error},		   {ERROR, error}, {ERROR, error},		  {VALUE, checkValue}, {ERROR, error} },		//STRING
									  { {ERROR, error},		   {OK, nothing},  {STRING, checkString}, {ERROR, error},	   {ERROR, error} },		//VALUE
									  { {OK, nothing},		   {OK, nothing},  {OK, nothing},		  {OK, nothing},	   {OK, nothing} },			//OK
									  { {ERROR, error},		   {ERROR, error}, {ERROR, error},		  {ERROR, error},	   {ERROR, error} } };		//ERROR
};