#include "Path.h"


Path::Path(wxColour color, int width)
{
	this->color = color;
	this->width = width;
}

void Path::BuildSelectionBox()
{
	selectionBox.Build(points.size(), points.data(), width);
}

void Path::Draw(wxGraphicsContext* gc) {
	gc->SetTransform(gc->CreateMatrix(selectionBox.GetTotalTransformMatrix()));
	gc->SetPen(wxPen(color, width));
	gc->StrokeLines(points.size(), points.data());
	selectionBox.Draw(gc);
}

void Path::AddPoint(wxPoint2DDouble point)
{
	points.push_back(point);
}