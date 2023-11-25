#pragma once

#include <wx/wx.h>
#include<wx/graphics.h>
#include <wx/dcbuffer.h>

#include "Transform.h"
#include "TransformMove.h"
#include "TransformRotate.h"
#include "TransformResize.h"

class SelectionBox
{
public:
	SelectionBox() {};

	void Build(int n, wxPoint2DDouble* a, int width = 0);
	void Build(double x, double y, double width, double height);
	void Draw(wxGraphicsContext* gc);
	Transform* OnMouseDown(wxMouseEvent &event);

	double GetArea() const;
		
	void SetSelected(bool selected) { this->selected = selected; }
	bool IsSelected() const { return selected; }
		
	void SetTransform(wxAffineMatrix2D transformMatrix);
	void DoTransform(Transform *transform);
	void CommitTransform();
	wxAffineMatrix2D GetBaseTransform() const { return transformMatrix; }
	wxAffineMatrix2D GetTotalTransformMatrix() const;

	double GetX() const { return x1; }
	double GetY() const { return y1; }

	enum {
		MOVE = 1,
		RESIZEX = 2,
		RESIZEY = 4,
		ROTATE = 8
	};

private:
	double x1, x2, y1, y2;
	wxRect2DDouble bound;
	int width, r = 4;
	bool selected = false;
	wxPoint2DDouble rotatePoint;
	wxAffineMatrix2D transformMatrix, primaryTransformMatrix;
};

