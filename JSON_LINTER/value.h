#pragma once
#include "eventGenerator.h"
#include "genericFSM.h"

enum stateValueType: stateTypes {INIT,SUB_FSM,TRUE,FALSE,NULLP,ERROR,OK};
enum eventsValue {START_ST,T,F,N,EOF_ };

#define VQSTATES 7
#define VQEVENTS 5

class valueFSM : public genericFSM
{
public:
	valueFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], VQSTATES, VQEVENTS, INIT, events)
	{
	}

	//acciones
	void cycle(void);
	void createFSM(void);
	void isTrue(void);
	void isFalse(void);
	void isNull(void);
private:
	#define TX(x) (static_cast<void (genericFSM::* ) (void)>(&valueFSM::x))
									//START_ST					//T					//F					//N						//EOF_
	const cellType tableFSM[VQSTATES][VQEVENTS] = {
									{ {SUB_FSM,TX(createFSM)},	{TRUE,TX(isTrue)},	{FALSE,TX(isFalse)},	{NULLP,TX(isNull)},	{ERROR,TX(error)}	},		//INIT
									{ {OK,TX(cycleOK)},			{OK,TX(cycleOK)},	{OK,TX(cycleOK)},		{OK,TX(cycleOK)},	{OK,TX(cycleOK)}		},		//SUB_FSM
									{ {OK,TX(cycleOK)},			{OK,TX(cycleOK)},	{OK,TX(cycleOK)},		{OK,TX(cycleOK)},	{OK,TX(cycleOK)}	},		//TRUE
									{ {OK,TX(cycleOK)},			{OK,TX(cycleOK)},	{OK,TX(cycleOK)},		{OK,TX(cycleOK)},	{OK,TX(cycleOK)}	},		//FALSE
									{ {OK,TX(cycleOK)},			{OK,TX(cycleOK)},	{OK,TX(cycleOK)},		{OK,TX(cycleOK)},	{OK,TX(cycleOK)}	},		//NULLP
									{ {ERROR,TX(error)},		{ERROR,TX(error)},	{ERROR,TX(error)},		{ERROR,TX(error)},	{ERROR,TX(error)}   },		//ERROR
									{ {OK,TX(cycleOK)},			{OK,TX(cycleOK)},	{OK,TX(cycleOK)},		{OK,TX(cycleOK)},	{OK,TX(cycleOK)	}	}		//OK
									};
};