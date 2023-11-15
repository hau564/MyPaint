#pragma once

#include "Transform.h"
#include "TransformRotate.h"
#include <cmath>

class TransformResize : public Transform
{
public:
	//TransformResize(int typeX, int typeY) : typeX(typeX), typeY(typeY) {};

	wxAffineMatrix2D GetMatrix(double x1, double y1, double x2, double y2, wxAffineMatrix2D transformMatrix) override
	{
		wxAffineMatrix2D matrix;

		wxPoint2DDouble rotate = transformMatrix.TransformPoint({ (x1 + x2) / 2, y1 - RotateArm});
		wxPoint2DDouble center = transformMatrix.TransformPoint({ (x1 + x2) / 2, (y1 + y2) / 2 });

		TransformRotate rotateTransform;
		rotateTransform.angle = -atan2(rotate.m_x - center.m_x, center.m_y - rotate.m_y);
		wxAffineMatrix2D rotateMatrix = rotateTransform.GetMatrix(x1, y1, x2, y2, transformMatrix);

		transformMatrix.TransformPoint(&x1, &y1);
		rotateMatrix.TransformPoint(&x1, &y1);
		transformMatrix.TransformPoint(&x2, &y2);
		rotateMatrix.TransformPoint(&x2, &y2);

		wxPoint2DDouble v = rotateMatrix.TransformPoint(pos + adjust) - rotateMatrix.TransformPoint(pos);

		if (typeX != 1) {
			dx = typeX ? -x1 : -x2;
			if (!f) rx = 1.0 + (typeX ? v.m_x : -v.m_x) / (x2 - x1);
		}
		if (typeY != 1) {
			dy = typeY ? -y1 : -y2;
			if (!f) ry = 1.0 + (typeY ? v.m_y : -v.m_y) / (y2 - y1);
		}
		f = 1;

		rotateMatrix.Invert();
		matrix.Concat(rotateMatrix);
		rotateMatrix.Invert();
		matrix.Translate(-dx, -dy);
		matrix.Scale(rx, ry);
		matrix.Translate(dx, dy);
		matrix.Concat(rotateMatrix);


		return matrix;
	}
	void Modify(wxPoint2DDouble p, wxPoint2DDouble adj) override
	{
		pos = p;
		adjust = adj;
		f = 0;
		dx = dy = 0;
		rx = ry = 1;
	}

	int typeX = 0, typeY = 0, f = 0;
	double dx = 0, dy = 0, rx = 1, ry = 1;
};