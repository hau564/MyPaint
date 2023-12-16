#include "ToolsSelection.h"

void ToolsSelection::SetPenColor(wxColor color)
{
	penColor = color;
}

void ToolsSelection::SetBrushColor(wxColor color)
{
	brushColor = color;
	isGradient = false;
}

void ToolsSelection::SetPenSize(int size)
{
	penSize = size;
}

void ToolsSelection::SetShape(Shape shape)
{
	this->shape = shape;
}

void ToolsSelection::SetGradientStops(wxGraphicsGradientStops stops)
{
	isGradient = true;
	this->stops = stops;
}
