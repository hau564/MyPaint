#include "SelectionBox.h"

void SelectionBox::Build(int n, wxPoint2DDouble* a, int width)
{
	if (!n) return;
	x1 = x2 = a[0].m_x;
	y1 = y2 = a[0].m_y;
	for (int i = 0; i < n; ++i) {
		x1 = std::min(x1, a[i].m_x);
		x2 = std::max(x2, a[i].m_x);
		y1 = std::min(y1, a[i].m_y);
		y2 = std::max(y2, a[i].m_y);
	}
	this->width = width;
	bound = wxRect2DDouble(x1 - width / 2, y1 - width / 2, x2 - x1 + width, y2 - y1 + width);
}

void SelectionBox::Draw(wxGraphicsContext* gc)
{
	gc->SetPen(*wxBLACK_DASHED_PEN);
	auto points = std::vector<wxPoint2DDouble>{ {x1, y1}, {x2, y1}, {x2, y2}, {x1, y2}, {x1, y1} };
	for (auto &point : points)
		transform.TransformPoint(&point.m_x, &point.m_y);
	gc->StrokeLines(points.size(), points.data());
}

bool SelectionBox::Contains(wxPoint point) const
{
	Transform inv = transform;
	inv.Invert();
	return bound.Contains(inv.TransformPoint(point));
}

double SelectionBox::GetArea() const
{
	return (bound.GetRight() - bound.GetLeft()) * (bound.GetBottom() - bound.GetTop());
}

wxRect2DDouble SelectionBox::GetBound() const
{
	return bound;
}