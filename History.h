#pragma once

#ifndef HISTORY_H
#define HISTORY_H

#include <wx/wx.h>
#include<vector>
#include "Explorer.h"
#include "Action.h"

class History
{
public:
	History(wxWindow* parent, Explorer* explorer);
	~History();

	void AddDoneAction(Action* action);
	void AddUndoneAction(Action* action);
	void Undo();
	void Redo();
	void SetTo(int i);

	void Hide();

protected:
	std::vector<Action*> actions;
	int pos;
	wxWindow *parent;
	Explorer *explorer;
};

#endif // !HISTORY_H