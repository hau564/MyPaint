#pragma once

#include <wx/wx.h>
#include "SelectionBox.h"

class Object
{
public:
	virtual void Draw(wxGraphicsContext* gc) = 0;
	virtual void BuildSelectionBox() = 0;

public:
	SelectionBox selectionBox;
};

