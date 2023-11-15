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
	//gc->SetTransform(gc->CreateMatrix(selectionBox.GetTotalTransformMatrix()));
	std::vector<wxPoint2DDouble> p = points;
	for (auto& point : p) {
		point = selectionBox.GetTotalTransformMatrix().TransformPoint(point);
	}
	gc->SetPen(wxPen(color, width));
	gc->StrokeLines(p.size(), p.data());
	selectionBox.Draw(gc);
}

void Path::AddPoint(wxPoint2DDouble point)
{
	points.push_back(point);
}