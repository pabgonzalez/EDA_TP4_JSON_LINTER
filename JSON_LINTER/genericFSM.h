#pragma once
/*
class genericFSM;
using stateTypes = unsigned int;

struct fsmCell
{
	stateTypes nextState;
	void (genericFSM::* action)(genericEvent *);
};

class genericFSM
{
public:
	genericFSM (const fsmCell* const table, const unsigned int rows, const unsigned int columns, stateTypes initState);
	void cycle(genericEvent* ev);

private:
	stateTypes state;
	const unsigned int rowCount;
	const unsigned int columnCount;
	const fsmCell* const FSMTable;

};
*/