#pragma once

#ifndef PATH_H
#define PATH_H

#include <wx/wx.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>
#include <wx/splitter.h>
#include <iostream>

#include "Transform.h"
#include "Object.h"

class Path: public Object
{
public:
	Path() { color = *wxBLACK, width = 1; };
	Path(wxColour color, int width);

	void BuildSelectionBox() override;
	void DrawContent(wxGraphicsContext* gc) override;

	void AddPoint(wxPoint2DDouble point);
	
public:
	wxColour color;
	int width;
	std::vector<wxPoint2DDouble> points;
};

#endif // !PATH_H