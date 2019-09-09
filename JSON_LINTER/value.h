#pragma once
#include "eventGenerator.h"

typedef enum {INIT,SUB_FSM,TRUE,FALSE,NULLP,ERROR,OK} stateValueType;
enum eventsValue {START_ST,T,F,N,OTHER };

typedef struct
{
	stateValueType nextState;
	void (*action) (void);
}cellType;

class valueFSM : public genericFSM
{
public:
	valueFSM(eventGenerator*);

	//acciones
	void cycle(void);
	void createFSM(void);
	void isTrue(void);
	void isFalse(void);
	void isNull(void);
private:
	stateValueType state;	
									//START_ST					//T					//F					//N					//OTHER
	const cellType tableFSM[7][5] = {
									{ {SUB_FSM,createFSM()},	{TRUE,isTrue()},	{FALSE,isFalse()},	{NULLP,isNull()},	{ERROR,error()} },		//INIT
									{ {OK,nothing()},			{OK,nothing()},		{OK,nothing()},		{OK,nothing()},		{OK,nothing()}	},		//SUB_FSM
									{ {OK,nothing()},			{OK,nothing()},		{OK,nothing()},		{OK,nothing()},		{OK,nothing()}	},		//TRUE
									{ {OK,nothing()},			{OK,nothing()},		{OK,nothing()},		{OK,nothing()},		{OK,nothing()}	},		//FALSE
									{ {OK,nothing()},			{OK,nothing()},		{OK,nothing()},		{OK,nothing()},		{OK,nothing()}	},		//NULLP
									{ {ERROR,error()},			{ERROR,error()},	{ERROR,error()},	{ERROR,error()},	{ERROR,error()}  },		//ERROR
									{ {OK,nothing()},			{OK,nothing()},		{OK,nothing()},		{OK,nothing()},		{OK,nothing()}	}		//OK
									};
};