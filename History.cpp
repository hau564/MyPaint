#include "History.h"

History::History()
{
	pos = -1;
}

History::~History()
{
}

void History::AddDoneAction(Action* action)
{
	while (actions.size() > pos + 1)
	{
		delete actions.back();
		actions.pop_back();
	}

	actions.push_back(action);
	pos++;
}

void History::AddUndoneAction(Action* action)
{
	while (actions.size() > pos + 1)
	{
		delete actions.back();
		actions.pop_back();
	}
	actions.push_back(action);
	pos++;
	action->Redo();
}

void History::Undo()
{
	if (pos < 0) return;
	actions[pos]->Undo();
	--pos;
}

void History::Redo()
{
	if (pos + 1 >= actions.size()) return;
	++pos;
	actions[pos]->Redo();
}

void History::SetTo(int i)
{
	if (i < 0 || i >= actions.size()) return;
	while (pos > i) Undo();
	while (pos < i) Redo();
}
