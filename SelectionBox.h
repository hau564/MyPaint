#pragma once

#include <wx/wx.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>

#include "Transform.h"

class SelectionBox
{
public:
	SelectionBox() {};

	void Build(int n, wxPoint2DDouble* a, int width = 0);
	void Draw(wxGraphicsContext* gc);

	bool Contains(wxPoint point) const;

	double GetArea() const;
	wxRect2DDouble GetBound() const;

public:
	double x1, x2, y1, y2;
	wxRect2DDouble bound;
	int width;
	Transform transform;
};

