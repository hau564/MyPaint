#pragma once

#include "Editor.h"
#include "Shape.h"

class EditorShape : public Editor
{
public:
	EditorShape(DrawingCanvas* parent);

	void OnMouseDown(wxMouseEvent& event) override;
	void OnMouseMove(wxMouseEvent& event) override;
	void OnMouseUp(wxMouseEvent& event) override;
	void OnMouseLeave(wxMouseEvent& event) override;

	void Draw(wxGraphicsContext* gc) override;
private:
	Shape* shape;
	double x1, x2, y1, y2;
};

