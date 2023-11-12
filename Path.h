#pragma once

#ifndef PATH_H
#define PATH_H

#include <wx/wx.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/splitter.h>
#include <iostream>

#include "SelectionBox.h"

class Path: public std::vector<wxPoint2DDouble>, public SelectionBox
{
public:
	Path() {};
	Path(wxColour color, int width);

	void Draw(wxGraphicsContext* gc);

	void OnPenDown(wxPoint2DDouble pos);
	void OnPenMove(wxPoint2DDouble pos);
	void OnPenUp();
	
	void SetSelected(bool selected) { this->selected = selected; }
	Path* OnMouseDown(wxPoint pos);

public:
	wxColour color;
	int width;
	bool finished = false;
	bool selected = false;
};

#endif // !PATH_H