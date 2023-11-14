#include "SelectionBox.h"
#include<cmath>

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
	if (!selected) return;

	Transform t = GetTotalTransform();

	gc->SetPen(*wxBLACK_DASHED_PEN);
	gc->DrawRectangle(x1, y1, x2 - x1, y2 - y1);

	double si = (x2 - x1) / 2, sj = (y2 - y1) / 2;

	gc->SetTransform(gc->CreateMatrix(Transform()));

	wxPoint2DDouble topMid = t.TransformPoint({ x1 + si, y1 });
	rotatePoint = t.TransformDistance({ 0, -30 });
	rotatePoint += topMid;
	gc->StrokeLine(topMid.m_x, topMid.m_y, rotatePoint.m_x, rotatePoint.m_y);

	gc->SetBrush(*wxWHITE_BRUSH);
	gc->SetPen(*wxBLACK_PEN);

	gc->DrawEllipse(rotatePoint.m_x - r, rotatePoint.m_y - r, 2 * r, 2 * r);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == 1 && j == 1) continue;
			wxPoint2DDouble point(x1 + si * i, y1 + sj * j);
			t.TransformPoint(&point.m_x, &point.m_y);

			gc->DrawEllipse(point.m_x - r, point.m_y - r, 2 * r, 2 * r);
		}
	}
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

Transform SelectionBox::GetTotalTransform()
{
	Transform t(transform);
	t.Concat(tempTransform);
	return t;
}



bool SelectionBox::OnMouseDown(wxMouseEvent& event)
{
	wxPoint2DDouble pos(event.GetX(), event.GetY());
	transform.Invert();
	transform.TransformPoint(&pos.m_x, &pos.m_y);
	transform.Invert();

	if (!selected) {
		if (bound.Contains(pos)) {
			selected = true;
			mode = MOVE;
			return true;
		}
		return false;
	}

	wxRect2DDouble rotateRect((x1 + x2) / 2 - r, y1 - 30 - r, 2 * r, 2 * r);
	if (rotateRect.Contains(pos)) {
		mode = ROTATE;
		return true;
	}

	double si = (x2 - x1) / 2, sj = (y2 - y1) / 2;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == 1 && j == 1) continue;
			wxPoint2DDouble point(x1 + si * i, y1 + sj * j);

			if (wxRect2DDouble(point.m_x - r, point.m_y - r, 2 * r, 2 * r).Contains(pos)) {

				return true;
			}
		}
	}

	return false;
}

bool SelectionBox::OnMouseMove(wxMouseEvent& event)
{
	if (!selected) return false;

	wxPoint2DDouble pos(event.GetX(), event.GetY());
	transform.Invert();
	transform.TransformPoint(&pos.m_x, &pos.m_y);
	transform.Invert();

	wxPoint2DDouble center((x1 + x2) / 2, (y1 + y2) / 2);
	wxPoint2DDouble c = transform.TransformPoint(center);

	if (mode == ROTATE) {
		double angle = atan2(pos.m_x - center.m_x, center.m_y - pos.m_y);

		tempTransform = Transform();
		tempTransform.Translate(c.m_x, c.m_y);
		tempTransform.Rotate(angle);
		tempTransform.Translate(-c.m_x, -c.m_y);
	}

	return false;
}

bool SelectionBox::OnMouseUp(wxMouseEvent& event)
{
	mode = 0;
	return false;
}

void SelectionBox::CommitTransform()
{
	transform.Concat(tempTransform);
	tempTransform = Transform();
}
