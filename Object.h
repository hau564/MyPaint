#pragma once

#include <wx/wx.h>
#include "SelectionBox.h"

class Object
{
public:
	virtual void DrawContent(wxGraphicsContext* gc) = 0;
	void DrawBox(wxGraphicsContext* gc);
	void Draw(wxGraphicsContext* gc);
	virtual void BuildSelectionBox() = 0;

public:
	SelectionBox selectionBox;
	bool showing = true;
};

