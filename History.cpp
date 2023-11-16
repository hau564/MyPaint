#include "History.h"

History::History(wxWindow* parent, Explorer* explorer)
	: pos(-1), explorer(explorer), parent(parent)
{
}

History::~History()
{

}

void History::AddDoneAction(Action* action)
{
	while (actions.size() > pos + 1)
	{
		explorer->Remove((int)actions.size() - 1);
		//delete actions.back();
		actions.pop_back();
	}

	actions.push_back(action);
	pos++;

	ActionPane *pane = new ActionPane(explorer, action, pos);
	pane->Bind(wxEVT_LEFT_DOWN, [=](wxMouseEvent& event) {
		SetTo(pane->GetId());
	});
	explorer->Add(pane);
}

void History::AddUndoneAction(Action* action)
{
	action->Redo();
	AddDoneAction(action);
}

void History::Undo()
{
	if (pos < 0) return;
	actions[pos]->Undo();
	explorer->SetSelected(pos, false);
	--pos;
}

void History::Redo()
{
	if (pos + 1 >= actions.size()) return;
	++pos;
	actions[pos]->Redo();
	explorer->SetSelected(pos, true);
}

void History::SetTo(int i)
{
	if (i < 0 || i >= actions.size()) return;
	while (pos > i) Undo();
	while (pos < i) Redo();
	parent->Refresh();
}
