#pragma once
#include "eventGenerator.h"
#include "genericFSM.h"
#include "number.h"
#include "arrayFSM.h"
#include "stringFSM.h"
#include "objectFSM.h"

#define VQSTATES 7
#define VQEVENTS 5

class valueFSM : public genericFSM
{
public:
	valueFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], VQSTATES, VQEVENTS, INIT, events){}

	//acciones
	void cycle(void);
	void createFSM(void);
	void isTrue(void);
	void isFalse(void);
	void isNull(void);

private:
	enum stateValueType : stateTypes { INIT, SUB_FSM, TRUE, FALSE, NULLP, ERROR, OK };
	enum eventsValue { START_ST, T, F, N, EOF_ };
	#define VX(x) (static_cast<void (genericFSM::* ) (void)>(&valueFSM::x))
	//												   START_ST					 T					 F					   N					EOF_
	const cellType tableFSM[VQSTATES][VQEVENTS] = { { {SUB_FSM, VX(createFSM)},	{TRUE, VX(isTrue)},	{FALSE, VX(isFalse)}, {NULLP, VX(isNull)}, {ERROR, VX(error)} },	//INIT
													{ {OK, VX(cycleOK)},		{OK, VX(cycleOK)},	{OK, VX(cycleOK)},	  {OK, VX(cycleOK)},   {OK, VX(cycleOK)} },		//SUB_FSM
													{ {OK, VX(cycleOK)},		{OK, VX(cycleOK)},	{OK, VX(cycleOK)},	  {OK, VX(cycleOK)},   {OK, VX(cycleOK)} },		//TRUE
													{ {OK, VX(cycleOK)},		{OK, VX(cycleOK)},	{OK, VX(cycleOK)},	  {OK, VX(cycleOK)},   {OK, VX(cycleOK)} },		//FALSE
													{ {OK, VX(cycleOK)},		{OK, VX(cycleOK)},	{OK, VX(cycleOK)},	  {OK, VX(cycleOK)},   {OK, VX(cycleOK)} },		//NULLP
													{ {ERROR, VX(error)},		{ERROR, VX(error)},	{ERROR, VX(error)},	  {ERROR, VX(error)},  {ERROR, VX(error)} },	//ERROR
													{ {OK, VX(cycleOK)},		{OK, VX(cycleOK)},	{OK, VX(cycleOK)},	  {OK, VX(cycleOK)},   {OK, VX(cycleOK) } } };	//OK
};