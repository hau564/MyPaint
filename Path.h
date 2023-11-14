#pragma once

#ifndef PATH_H
#define PATH_H

#include <wx/wx.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/splitter.h>
#include <iostream>

#include "Transform.h"
#include "SelectionBox.h"

class Path: public std::vector<wxPoint2DDouble>
{
public:
	Path() { color = *wxBLACK, width = 1; };
	Path(wxColour color, int width);

	void BuildSelectionBox();

	void Draw(wxGraphicsContext* gc);

	std::vector<wxPoint2DDouble> GetTransformedPoints() const;
	
public:
	wxColour color;
	int width;
	SelectionBox selectionBox;
};

#endif // !PATH_H