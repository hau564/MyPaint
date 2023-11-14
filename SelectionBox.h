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
	Transform GetTotalTransform();

	bool OnMouseDown(wxMouseEvent &event);
	bool OnMouseMove(wxMouseEvent& event);
	bool OnMouseUp(wxMouseEvent& event);

	void CommitTransform();

	enum {
		MOVE = 1,
		RESIZEX = 2,
		RESIZEY = 4,
		ROTATE = 8
	};

public:
	double x1, x2, y1, y2;
	wxRect2DDouble bound;
	int width;
	bool selected = false;
	Transform transform, tempTransform;
	int mode = 0;
	int r = 4;
	wxPoint2DDouble rotatePoint;
};

