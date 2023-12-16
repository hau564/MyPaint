#pragma once

#ifndef PATH_H
#define PATH_H

#include <wx/wx.h>

#include "Object.h"

class Path: public Object
{
public:
	Path() { color = *wxBLACK, width = 1; };
	Path(wxColour color, int width);
	Path(std::vector<wxPoint2DDouble> points, wxColour color, int width);

	void BuildSelectionBox() override;
	void DrawContent(wxGraphicsContext* gc) override;

	void AddPoint(wxPoint2DDouble point);
	void AddPoint(double x, double y);
	
public:
	wxColour color;
	int width;
	std::vector<wxPoint2DDouble> points;
};

#endif // !PATH_H