#pragma once

#include<vector>
#include "Action.h"
#include "ActionNewObject.h"

class History
{
public:
	History();
	~History();

	void AddDoneAction(Action* action);
	void AddUndoneAction(Action* action);
	void Undo();
	void Redo();
	void SetTo(int i);

private:
	std::vector<Action*> actions;
	int pos;
};

