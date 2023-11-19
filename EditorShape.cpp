#include "EditorShape.h"
#include "DrawingCanvas.h"

EditorShape::EditorShape(DrawingCanvas* parent)
	:Editor(parent)
{
}

void EditorShape::OnMouseDown(wxMouseEvent& event)
{
	shape = new Shape;
	*shape = parent->GetShape();
	shape->color = parent->GetPenColor();
	shape->width = parent->GetPenSize();
	shape->fillColor = parent->GetBrushColor();

	x1 = event.GetX();
	y1 = event.GetY();
	x2 = x1 + 1;
	y2 = y1 + 1;
	shape->ScaleToRect(wxRect(x1, y1, x2 - x1, y2 - y1));
}

void EditorShape::OnMouseMove(wxMouseEvent& event)
{
	if (!shape) return;

	x2 = event.GetX();
	y2 = event.GetY();
	shape->ScaleToRect(wxRect(x1, y1, x2 - x1, y2 - y1));
}

void EditorShape::OnMouseUp(wxMouseEvent& event)
{
	if (!shape) return;
	parent->AddPath(shape);
	shape = nullptr;
}

void EditorShape::OnMouseLeave(wxMouseEvent& event)
{
	OnMouseUp(event);
}

void EditorShape::Draw(wxGraphicsContext* gc)
{
	if (shape) shape->Draw(gc);
}
