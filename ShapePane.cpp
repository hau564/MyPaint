#include "ShapePane.h"

ShapePane::ShapePane(wxWindow* parent, std::vector<wxPoint2DDouble> points, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: SelectablePane(parent, id, pos, size), points(points)	
{
	shape = new Shape(points, *wxBLACK, wxColour(200, 200, 200), 1);
}

void ShapePane::DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness) 
{
	gc->SetPen(*wxWHITE_PEN);
	gc->SetBrush(*wxWHITE_BRUSH);

	Shape s = *shape;
	s.DrawOnRect(gc, wxRect(rect.GetX() + d, rect.GetY() + d, rect.GetWidth() - 2 * d, rect.GetHeight() - 2 * d), roundness);
}

void ShapePane::DrawSelected(wxGraphicsContext* gc, const wxRect& rect, int roundness)
{
	Shape s = *shape;
	s.width = 3;
	s.DrawOnRect(gc, wxRect(rect.GetX() + d, rect.GetY() + d, rect.GetWidth() - 2 * d, rect.GetHeight() - 2 * d), roundness);
}
