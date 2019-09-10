#pragma once
#include "genericFSM.h"

#define JQSTATES 5
#define JQEVENTS 3

enum stateJSONType: stateTypes {INIT,ELEMENT,COMA,ERROR,OK};
enum EVENTS {NO_COMA,COMA,EOF_};

class jsonFSM : public genericFSM
{
public:
	jsonFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], JQSTATES, JQEVENTS, INIT, events) {}

	void element(void);

	//acciones
	void cycle(void);
private:
	#define TX(x) (static_cast<void (genericFSM::* ) (void)>(&jsonFSM::x))
														//NOCOMA					COMA				 EOF_
	const cellType tableFSM[JQSTATES][JQEVENTS] = {
													{ {ELEMENT, TX(element)} ,		{ERROR,TX(error)},	{OK,TX(cycleOK)}  },		//INIT
													{ {ERROR,TX(error)},			{COMA,TX(nothing)},	{OK,TX(cycleOK)}  },		//ELEMENT
													{ {ELEMENT,TX(element)},		{ERROR,TX(error)},	{ERROR,TX(error)} },		//COMA
													{ {ERROR, TX(error)},			{ERROR, TX(error)},	{ERROR,TX(error)} }			//ERROR
												};

};