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
	gc->SetPen(wxPen(color, width));
	gc->SetTransform(gc->CreateMatrix(selectionBox.GetTotalTransform()));
	gc->StrokeLines(points.size(), points.data());
	selectionBox.Draw(gc);
}

void Path::AddPoint(wxPoint2DDouble point)
{
	points.push_back(point);
}

std::vector<wxPoint2DDouble> Path::GetTransformedPoints() const
{
	std::vector<wxPoint2DDouble> points = this->points;
	for (auto &point : points)
		selectionBox.transform.TransformPoint(&point.m_x, &point.m_y);
	return points;
}
