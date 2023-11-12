#include "SelectionBox.h"

void SelectionBox::BuildBox(int n, wxPoint2DDouble* a, int width)
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
	gc->DrawRectangle(	bound.GetLeft(), bound.GetTop(), 
						bound.GetRight() - bound.GetLeft(), bound.GetBottom() - bound.GetTop());
}

double SelectionBox::GetBoundArea() const
{
	return (bound.GetRight() - bound.GetLeft()) * (bound.GetBottom() - bound.GetTop());
}

wxRect2DDouble SelectionBox::GetBound() const
{
	return bound;
}

std::vector<wxPoint2DDouble> SelectionBox::GetCorners()
{
	std::vector<wxPoint2DDouble> corners;
	corners.push_back(wxPoint2DDouble(x1, y1));
	corners.push_back(wxPoint2DDouble(x2, y1));
	corners.push_back(wxPoint2DDouble(x2, y2));
	corners.push_back(wxPoint2DDouble(x1, y2));
	corners.push_back(wxPoint2DDouble(x1, y1));
	return corners;	
}
