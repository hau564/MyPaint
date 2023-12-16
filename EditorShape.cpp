#include "EditorShape.h"
#include "DrawingCanvas.h"
#include "GradientBrush.h"

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

	if (parent->IsGradient()) {
		shape->isGradient = true;
		shape->stops = parent->GetGradientStops();
	}
	shape->stops = parent->GetGradientStops();
	
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
	if (!wxGetKeyState(WXK_CONTROL))
		shape->ScaleToRect(wxRect(x1, y1, x2 - x1, y2 - y1));
	else {
		double c = std::max(abs(x2 - x1), abs(y2 - y1));
		shape->ScaleToRect(wxRect(x1, y1, x2 > x1 ? c : -c, y2 > y1 ? c : -c));
	}
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

void EditorShape::OnKeyDown(wxKeyEvent& event)
{
}

void EditorShape::OnKeyUp(wxKeyEvent& event)
{
}

void EditorShape::Draw(wxGraphicsContext* gc)
{
	if (shape) shape->Draw(gc);
}
