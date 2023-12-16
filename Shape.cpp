#include "Shape.h"
#include "GradientBrush.h"
Shape::Shape(std::vector<wxPoint2DDouble> points, wxColour color, wxColour fillColor, int width)
	: Path(points, color, width), fillColor(fillColor), mpoints(points)
{
	BuildRect();
}

void Shape::BuildRect()
{
	Path::BuildSelectionBox();
	x1 = x2 = mpoints[0].m_x;
	y1 = y2 = mpoints[0].m_y;
	for (int i = 1; i < points.size(); i++) {
		if (mpoints[i].m_x < x1) x1 = mpoints[i].m_x;
		if (mpoints[i].m_x > x2) x2 = mpoints[i].m_x;
		if (mpoints[i].m_y < y1) y1 = mpoints[i].m_y;
		if (mpoints[i].m_y > y2) y2 = mpoints[i].m_y;
	}
}

void Shape::ScaleToRect(const wxRect& rect)
{
	points = mpoints;
	for (auto& point : points) {
		point.m_x = (point.m_x - x1) * (1.0 * rect.GetWidth() / (x2 - x1)) + rect.GetX();
		point.m_y = (point.m_y - y1) * (1.0 * rect.GetHeight() / (y2 - y1)) + rect.GetY();
	}
	scale_rect = wxRect2DDouble(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
}



void Shape::DrawContent(wxGraphicsContext* gc)
{
	wxGraphicsPath fpath = gc->CreatePath();
	wxAffineMatrix2D matrix = selectionBox.GetTotalTransformMatrix();
	fpath.MoveToPoint(matrix.TransformPoint(points[0]));
	for (int i = 1; i < points.size(); i++) {
		fpath.AddLineToPoint(matrix.TransformPoint(points[i]));
	}
	gc->SetPen(color);
	gc->SetBrush(fillColor);
	if (isGradient)
		gc->SetBrush(Gradient::CreateBrush(gc, &matrix, scale_rect, stops));
	gc->DrawPath(fpath);
	
	Path::DrawContent(gc);
}

void Shape::DrawOnRect(wxGraphicsContext* gc, const wxRect& rect, int roundness)
{
	ScaleToRect(rect);
	DrawContent(gc);
}
