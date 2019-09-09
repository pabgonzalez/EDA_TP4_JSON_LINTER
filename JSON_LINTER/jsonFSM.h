#pragma once
#include "eventGenerator.h"
#include "genericFSM.h"

#define TX(x) ((static_cast)<void (jsonFSM::*)(void)>(&jsonFSM:: x))

typedef enum {INIT,ELEMENT,COMA,ERROR} stateJSONType;
enum EVENTS {NO_COMA,COMA};

typedef struct
{
	stateJSONType nextState;
	void (*action) (void);
}cellType;

class jsonFSM : public genericFSM
{
public:
	jsonFSM(eventGenerator*);
	void element(void);
	void coma(void);
	void error(void);

	//acciones
	void cycle(void);
private:
	stateJSONType state;
										//NOCOMA				COMA	
	const cellType tableFSM[4][2] = {{{ELEMENT, &element} ,		{ERROR,error()}  },				//INIT
									{ {ERROR,error()},			{COMA,coma()}    },				//ELEMENT
									{ {ELEMENT,element()},		{ERROR,error()}  },				//COMA
									{ {ERROR, error()},			{ERROR, error()}         } };	//ERROR

};