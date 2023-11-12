#pragma once

#include <wx/wx.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>

class SelectionBox
{
public:
	SelectionBox() {};

	void BuildBox(int n, wxPoint2DDouble* a, int width = 0);
	void Draw(wxGraphicsContext* gc);

	double GetBoundArea() const;
	wxRect2DDouble GetBound() const;

	std::vector<wxPoint2DDouble> GetCorners();

private:
	double x1, x2, y1, y2;
	wxRect2DDouble bound;
	int width;
};

