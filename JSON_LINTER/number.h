#pragma once
#include "eventGenerator.h"
#include "genericFSM.h"

typedef enum {INIT,INT,SIGN_INT,CERO,POINT,FRACTION,E,SIGN_EXP,EXP,ERROR,OK}stateNumberType;
enum EVENTS_FOR_NUMBER {ONENINE,CERO,SIGN_MINUS,SIGN_PLUS,POINT,E,OTHER};


typedef struct
{
	stateNumberType nextState;
	void (*action) (void);
}cellType;

class numberFSM : public genericFSM
{
public:
	numberFSM(eventGenerator*);
	void nothing(void);
	void error(void);
	void cycle(void);
private:
	stateNumberType state;
										//ONENINE			//CERO				//SIGN_MINUS		//SIGN_PLUS				//POINT				//E					//OTHER
	const cellType tableFSM[11][7] = {
										{ {INT,nothing()},	{CERO, nothing()}, {SIGN_INT,nothing()},	{ERROR,error()},	{ERROR,error()}	,	{ERROR,error()},	{ERROR,error()}	},		//INIT
										{ {INT,nothing()},	{INT, nothing()},  {ERROR,error()},			{ERROR,error()},	{POINT,nothing()},	{E,nothing()},		{OK,nothing()}	},		//INT
										{ {INT,nothing()},  {CERO, nothing()}, {ERROR,error()},			{ERROR,error()},	{ERROR,error()},	{ERROR,error()},	{ERROR,error()}	},		//SIGN_INT
										{ {ERROR,error()},	{ERROR, error()},  {ERROR,error()},			{ERROR,error()},	{POINT, nothing()}, {E,nothing()},		{OK,nothing()}	},		//CERO
										{ {FRACTION,nothing()}, {FRACTION,nothing()}, {ERROR,error()},	{ERROR,error()},	{ERROR, error()},	{ERROR,error()},	{ERROR,error()}	},		//POINT
										{ {FRACTION,nothing()}, {FRACTION,nothing()}, {ERROR,error()},	{ERROR,error()},	{ERROR, error()},	{E,nothing()},		{OK,nothing()}	},		//FRACTION
										{ {EXP,nothing()},	{EXP,nothing()},	{SIGN_EXP,nothing()},	{SIGN_EXP,nothing()}, {ERROR,error()},	{ERROR,error()},	{ERROR,error()}	},		//E
										{ {EXP,nothing()},	{EXP,nothing()},	{ERROR,error()},		{ERROR,error()},	{ERROR,error()},	{ERROR,error()},	{ERROR,error()} },		//SIGN_EXP
										{ {EXP,nothing()},  {EXP,nothing()},	{ERROR,error()},		{ERROR,error()},	{ERROR,error()},	{ERROR,error()},	{OK,nothing() }	},		//EXP
										{ {ERROR,error()},	{ERROR,error()},	{ERROR,error()},		{ERROR,error()},	{ERROR,error()},	{ERROR,error()},	{ERROR,error()}	},		//ERROR    
										{ {OK,nothing()},	{OK,nothing()},		{OK,nothing()},			{OK,nothing()},		{OK,nothing()},		{OK,nothing()},		{OK,nothing()}  }		//OK
									};

};