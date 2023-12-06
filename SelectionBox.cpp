#include "SelectionBox.h"
#include<cmath>

void SelectionBox::Build(int n, wxPoint2DDouble* a, int width)
{
	if (!n) return;
	x1 = x2 = a[0].m_x;
	y1 = y2 = a[0].m_y;
	x2 += 1;
	y2 += 1;
	for (int i = 0; i < n; ++i) {
		x1 = std::min(x1, a[i].m_x);
		x2 = std::max(x2, a[i].m_x);
		y1 = std::min(y1, a[i].m_y);
		y2 = std::max(y2, a[i].m_y);
	}
	this->width = width;
	bound = wxRect2DDouble(x1 - width / 2, y1 - width / 2, x2 - x1 + width, y2 - y1 + width);
}

void SelectionBox::Build(double x, double y, double width, double height)
{
	x1 = x;
	y1 = y;
	x2 = x + width;
	y2 = y + height;
	width = 1;
	bound = wxRect2DDouble(x1 - width / 2, y1 - width / 2, x2 - x1 + width, y2 - y1 + width);
}

void SelectionBox::Draw(wxGraphicsContext* gc)
{
	if (!selected) return;
	gc->SetPen(wxPen(wxColour(200, 200, 200), 0.5));
	gc->SetBrush(*wxWHITE_BRUSH);
	
	double dx = (x2 - x1) / 2, dy = (y2 - y1) / 2;
	wxAffineMatrix2D tmatrix = GetTotalTransformMatrix();

	std::vector<wxPoint2DDouble> points = { {x1, y1}, {x1, y2}, {x2, y2}, {x2, y1}, {x1, y1} };
	for (auto& p : points) 
		p = tmatrix.TransformPoint(p);
	gc->StrokeLines(points.size(), points.data());

	wxPoint2DDouble topMid = tmatrix.TransformPoint({ x1 + dx, y1 });
	wxPoint2DDouble midToTop = topMid - tmatrix.TransformPoint({ x1 + dx, y1 + dy });
	double len = sqrt(midToTop.m_x * midToTop.m_x + midToTop.m_y * midToTop.m_y);
	rotatePoint = topMid + midToTop	/ len * RotateArm;
	
	gc->StrokeLine(topMid.m_x, topMid.m_y, rotatePoint.m_x, rotatePoint.m_y);
	gc->DrawEllipse(rotatePoint.m_x - r, rotatePoint.m_y - r, 2 * r, 2 * r);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == 1 && j == 1) continue;
			wxPoint2DDouble p(x1 + dx * i, y1 + dy * j);
			tmatrix.TransformPoint(&p.m_x, &p.m_y);
			gc->DrawEllipse(p.m_x - r, p.m_y - r, 2 * r, 2 * r);
		}
	}
}

double SelectionBox::GetArea() const
{
	return (bound.GetRight() - bound.GetLeft()) * (bound.GetBottom() - bound.GetTop());
}



Transform* SelectionBox::OnMouseDown(wxMouseEvent& event)
{
	transformMatrix.Invert();
	wxPoint2DDouble originalPos = event.GetPosition();
	wxPoint2DDouble pos = transformMatrix.TransformPoint(originalPos);
	transformMatrix.Invert();

	wxAffineMatrix2D tmatrix = GetTotalTransformMatrix();

	if (!selected) {
		if (bound.Contains(pos)) {
			selected = 1;
			return new TransformMove();
		}
		return nullptr;
	}

	double dx = (x2 - x1) / 2, dy = (y2 - y1) / 2;
	wxRect2DDouble rotateRect(rotatePoint.m_x - r, rotatePoint.m_y- r, 2 * r, 2 * r);
	if (rotateRect.Contains(originalPos)) {
		return new TransformRotate();
	}

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (i == 1 && j == 1) continue;
			wxPoint2DDouble p(x1 + dx * i, y1 + dy * j);
			tmatrix.TransformPoint(&p.m_x, &p.m_y);
			wxRect2DDouble rect(p.m_x - r, p.m_y - r, 2 * r, 2 * r);
			//wxRect2DDouble rect(x1 + dx * i - r, y1 + dy * j - r, 2 * r, 2 * r);
			if (rect.Contains(originalPos)) {
				TransformResize* t = new TransformResize;
				t->typeX = i;
				t->typeY = j;
				return t;
			}
		}
	}

	if (bound.Contains(pos)) {
		return new TransformMove();
	}
	return nullptr;
}

void SelectionBox::SetTransform(wxAffineMatrix2D transformMatrix)
{
	this->transformMatrix = transformMatrix;
	primaryTransformMatrix = wxAffineMatrix2D();
}

void SelectionBox::DoTransform(Transform* transform)
{
	primaryTransformMatrix = transform->GetMatrix(x1, y1, x2, y2, transformMatrix);
}

wxAffineMatrix2D SelectionBox::GetTotalTransformMatrix() const
{
	wxAffineMatrix2D t(primaryTransformMatrix);
	t.Concat(transformMatrix);
	return t;
}

void SelectionBox::CommitTransform()
{
	std::swap(transformMatrix, primaryTransformMatrix);
	transformMatrix.Concat(primaryTransformMatrix);
	primaryTransformMatrix = wxAffineMatrix2D();
}
