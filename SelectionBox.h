#pragma once

#include <wx/wx.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>

#include "Transform.h"
#include "TransformMove.h"
#include "TransformRotate.h"

class SelectionBox
{
public:
	SelectionBox() {};

	void Build(int n, wxPoint2DDouble* a, int width = 0);
	void Draw(wxGraphicsContext* gc);

	bool Contains(wxPoint point) const;

	double GetArea() const;

	Transform* OnMouseDown(wxMouseEvent &event);
	
	void DoTransform(Transform *transform);
	wxAffineMatrix2D GetTotalTransformMatrix() const;
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
	int width, r = 4;
	bool selected = false;
	wxAffineMatrix2D transformMatrix, primaryTransformMatrix;
};

