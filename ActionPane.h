#pragma once

#ifndef ACTION_PANE_H
#define ACTION_PANE_H

#include "SelectablePane.h"
#include "Action.h"

class ActionPane: public SelectablePane
{
public:
	ActionPane(wxWindow* parent, const Action* action, const int actionId, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	int GetId() const { return id; }
private:
	void DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness) override;
	const Action* action;
	int id;
};

#endif // !ACTION_PANE_H