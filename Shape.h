#pragma once

#include <wx/wx.h>
#include "Path.h"

class Shape : public Path
{
public:
	Shape(std::vector<wxPoint2DDouble> points, wxColour color = *wxBLACK, wxColour fillColor = wxTRANSPARENT, int width = 1);
	//Shape(Shape oth);
	Shape() {};

	void BuildRect();
	void ScaleToRect(const wxRect& rect);
	void DrawContent(wxGraphicsContext* gc) override;
	void DrawOnRect(wxGraphicsContext* gc, const wxRect& rect, int roundness);

public:
	wxColour fillColor;
	std::vector<wxPoint2DDouble> mpoints;
private:
	double x1, x2, y1, y2;
};

