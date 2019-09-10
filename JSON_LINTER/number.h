#pragma once
#include "genericFSM.h"

#define NQSTATES 11
#define NQEVENTS 8

enum stateNumberType : stateTypes {INIT,INT,SIGN_INT,CERO,POINT,FRACTION,E,SIGN_EXP,EXP,ERROR,OK};
enum EVENTS_FOR_NUMBER {ONENINE,CERO,SIGN_MINUS,SIGN_PLUS,POINT,E,OTHER,EOF_};

class numberFSM : public genericFSM
{
public:
	numberFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], NQSTATES, NQEVENTS, INIT, events) {}
	void cycle(void);
private:
	#define TX(x) (static_cast<void (genericFSM::* ) (void)>(&numberFSM::x))
	const cellType tableFSM[NQSTATES][NQEVENTS] = {

										//ONENINE				//CERO					//SIGN_MINUS			//SIGN_PLUS				//POINT				//E					//OTHER				EOF_
										{ {INT,TX(nothing)},	{CERO, TX(nothing)},	{SIGN_INT,TX(nothing)},	{ERROR,TX(error)},	{ERROR,TX(error)},		{ERROR,TX(error)},	{ERROR,TX(error)} ,	{ERROR,TX(error)}	},		//INIT
										{ {INT,TX(nothing)},	{INT,TX(nothing)},		{ERROR,TX(error)},		{ERROR,TX(error)},	{POINT,TX(nothing)},	{E,TX(nothing)},	{OK,TX(nothing)} ,	{OK,TX(cycleOK)}	},		//INT
										{ {INT,TX(nothing)},	{CERO, TX(nothing)},	{ERROR,TX(error)},		{ERROR,TX(error)},	{ERROR,TX(error)},		{ERROR,TX(error)},	{ERROR,TX(error)},	{ERROR,TX(error)	},		//SIGN_INT
										{ {ERROR,TX(error)},	{ERROR, TX(error)},		{ERROR,TX(error)},		{ERROR,TX(error)},	{POINT,TX(nothing)},	{E,TX(nothing)},	{OK,TX(cycleOK)},	{OK,TX(cycleOK)}	},		//CERO
										{ {FRACTION,TX(nothing)}, {FRACTION,TX(nothing)}, {ERROR,(error)},		{ERROR,TX(error)},	{ERROR, TX(error)},		{ERROR,TX(error)},	{ERROR,TX(error)},	{ERROR,TX(error)}	},		//POINT
										{ {FRACTION,TX(nothing)}, {FRACTION,TX(nothing)}, {ERROR,TX(error)},	{ERROR,TX(error)},	{ERROR, TX(error)},		{E,TX(nothing)},	{OK,TX(cycleOK)},	{OK,TX(cycleOK)}	},		//FRACTION
										{ {EXP,TX(nothing)},	{EXP,TX(nothing)},		{SIGN_EXP,TX(nothing)},	{SIGN_EXP,TX(nothing)}, {ERROR,TX(error)},	{ERROR,TX(error)},	{ERROR,TX(error)},	{ERROR,TX(error)}	},		//E
										{ {EXP,TX(nothing)},	{EXP,TX(nothing)},		{ERROR,TX(error)},		{ERROR,TX(error)},	{ERROR,TX(error)},		{ERROR,TX(error)},	{ERROR,TX(error)},	{ERROR,TX(error)}	},		//SIGN_EXP
										{ {EXP,TX(nothing)},	{EXP,TX(nothing)},		{ERROR,TX(error)},		{ERROR,TX(error)},	{ERROR,TX(error)},		{ERROR,TX(error)},	{OK,TX(cycleOK) },	{OK,TX(cycleOK)}	},		//EXP
										{ {ERROR,TX(error)},	{ERROR,TX(error)},		{ERROR,TX(error)},		{ERROR,TX(error)},	{ERROR,TX(error)},		{ERROR,TX(error)},	{ERROR,TX(error)},	{ERROR,TX(error)}	},		//ERROR    
										{ {OK,TX(cycleOK)},		{OK,TX(cycleOK)},		{OK,TX(cycleOK)},		{OK,TX(cycleOK)},	{OK,TX(cycleOK)},		{OK,TX(cycleOK)},	{OK,TX(cycleOK)},	{OK,TX(cycleOK)}	}		//OK
									};

};