#pragma once

#include <wx/wx.h>
#include "SelectionBox.h"

class Object
{
public:
	virtual void DrawContent(wxGraphicsContext* gc);
	virtual void DrawBox(wxGraphicsContext* gc);
	virtual void Draw(wxGraphicsContext* gc);
	virtual void BuildSelectionBox() = 0;

public:
	SelectionBox selectionBox;
};

