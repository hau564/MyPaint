#include "Path.h"


Path::Path(wxColour color, int width)
{
	this->color = color;
	this->width = width;
}

void Path::BuildSelectionBox()
{
	selectionBox.Build(size(), data());
}

void Path::Draw(wxGraphicsContext* gc) {
	gc->SetPen(wxPen(color, width));
	std::vector<wxPoint2DDouble> points = GetTransformedPoints();
	gc->StrokeLines(size(), points.data());
}

std::vector<wxPoint2DDouble> Path::GetTransformedPoints() const
{
	std::vector<wxPoint2DDouble> points = *this;
	for (auto &point : points)
		selectionBox.transform.TransformPoint(&point.m_x, &point.m_y);
	return points;
}
