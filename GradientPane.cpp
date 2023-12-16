#include "GradientPane.h"

GradientPane::GradientPane(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: SelectablePane(parent, id, pos, size)
{
	
}

void GradientPane::SetGradientStops(wxGraphicsGradientStops stops)
{
	shape.stops = stops;
	shape.isGradient = true;
}

void GradientPane::DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness)
{
	shape.DrawOnRect(gc, rect, roundness);
}
