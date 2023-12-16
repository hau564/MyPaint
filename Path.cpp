#include "Path.h"


Path::Path(wxColour color, int width)
{
	this->color = color;
	this->width = width;
}

Path::Path(std::vector<wxPoint2DDouble> points, wxColour color, int width)
	: points(points), color(color), width(width)
{
}

void Path::BuildSelectionBox()
{
	selectionBox.Build(points.size(), points.data(), width);
}

void Path::DrawContent(wxGraphicsContext* gc) {
	std::vector<wxPoint2DDouble> p = points;
	for (auto& point : p) {
		point = selectionBox.GetTotalTransformMatrix().TransformPoint(point);
	}
	//gc->SetTransform(gc->CreateMatrix(selectionBox.GetTotalTransformMatrix()));
	gc->SetPen(wxPen(color, width));
	gc->StrokeLines(p.size(), p.data());
	//gc->SetTransform(gc->CreateMatrix(wxAffineMatrix2D()));
}

void Path::AddPoint(wxPoint2DDouble point)
{
	points.push_back(point);
}

void Path::AddPoint(double x, double y)
{
	points.push_back(wxPoint2DDouble(x, y));
}
