#pragma once
#include "genericFSM.h"

#define NQSTATES 11
#define NQEVENTS 8

class numberFSM : public genericFSM
{
public:
	numberFSM(eventGenerator* events) : genericFSM(&tableFSM[0][0], NQSTATES, NQEVENTS, INIT, events) {}
	void cycle(void);

private:
	enum stateNumberType : stateTypes { INIT, INT, SIGN_INT, CERO, POINT, FRACTION, E, SIGN_EXP, EXP, ERROR, OK };
	enum EVENTS_FOR_NUMBER { ONENINE, CER0, SIGN_MINUS, SIGN_PLUS, P0INT, EXPO, OTHER, EOF_ };
	#define NX(x) (static_cast<void (genericFSM::* ) (void)>(&numberFSM::x))
	//												   ONENINE					CER0					 SIGN_MINUS				  SIGN_PLUS				   P0INT				 EXPO				 OTHER				 EOF_
	const cellType tableFSM[NQSTATES][NQEVENTS] = { { {INT, NX(nothing)},	   {CERO, NX(nothing)},		{SIGN_INT, NX(nothing)}, {ERROR, NX(error)},	  {ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)} },		//INIT
													{ {INT, NX(nothing)},	   {INT, NX(nothing)},		{ERROR, NX(error)},		 {ERROR, NX(error)},	  {POINT, NX(nothing)},	{E, NX(nothing)},	{OK, NX(nothing)},	{OK, NX(cycleOK)} },		//INT
													{ {INT, NX(nothing)},	   {CERO, NX(nothing)},		{ERROR, NX(error)},		 {ERROR, NX(error)},	  {ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)} },		//SIGN_INT
													{ {ERROR, NX(error)},	   {ERROR, NX(error)},		{ERROR, NX(error)},		 {ERROR, NX(error)},	  {POINT, NX(nothing)},	{E, NX(nothing)},	{OK, NX(cycleOK)},	{OK, NX(cycleOK)} },		//CERO
													{ {FRACTION, NX(nothing)}, {FRACTION, NX(nothing)}, {ERROR, NX(error)},		 {ERROR, NX(error)},	  {ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)} },		//POINT
													{ {FRACTION, NX(nothing)}, {FRACTION, NX(nothing)}, {ERROR, NX(error)},		 {ERROR, NX(error)},	  {ERROR, NX(error)},	{E, NX(nothing)},	{OK, NX(cycleOK)},	{OK, NX(cycleOK)} },		//FRACTION
													{ {EXP, NX(nothing)},	   {EXP, NX(nothing)},		{SIGN_EXP, NX(nothing)}, {SIGN_EXP, NX(nothing)}, {ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)} },		//E
													{ {EXP, NX(nothing)},	   {EXP, NX(nothing)},		{ERROR, NX(error)},		 {ERROR, NX(error)},	  {ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)} },		//SIGN_EXP
													{ {EXP, NX(nothing)},	   {EXP, NX(nothing)},		{ERROR, NX(error)},		 {ERROR, NX(error)},	  {ERROR, NX(error)},	{ERROR, NX(error)},	{OK, NX(cycleOK) },	{OK, NX(cycleOK)} },		//EXP
													{ {ERROR, NX(error)},	   {ERROR, NX(error)},		{ERROR, NX(error)},		 {ERROR, NX(error)},	  {ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)},	{ERROR, NX(error)} },		//ERROR    
													{ {OK, NX(cycleOK)},	   {OK, NX(cycleOK)},		{OK, NX(cycleOK)},		 {OK, NX(cycleOK)},		  {OK, NX(cycleOK)},	{OK, NX(cycleOK)},	{OK, NX(cycleOK)},	{OK, NX(cycleOK)} } };		//OK
};