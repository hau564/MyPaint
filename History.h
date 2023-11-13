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

protected:
	std::vector<Action*> actions;
	int pos;
	Explorer *explorer;
	wxWindow *parent;
};

#endif // !HISTORY_H