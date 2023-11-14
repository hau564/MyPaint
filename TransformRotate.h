#pragma once

#include "Transform.h"
#include<cmath>

class TransformRotate : public Transform
{
public:
	wxAffineMatrix2D GetMatrix(double x1, double y1, double x2, double y2, wxAffineMatrix2D transformMatrix) override
	{
		wxAffineMatrix2D matrix;
		
		double dx = (x2 - x1) / 2, dy = (y2 - y1) / 2;
		wxPoint2DDouble center((x1 + x2) / 2, (y1 + y2) / 2);

		if (angle > 10) {
			wxPoint2DDouble p = adjust;
			transformMatrix.Invert();
			transformMatrix.TransformDistance(&p.m_x, &p.m_y);
			angle = atan2(p.m_x, dy - p.m_y);
		}

		if (abs(angle) <= 0.01) return matrix;

		matrix.Translate(center.m_x, center.m_y);
		matrix.Rotate(angle);
		matrix.Translate(-center.m_x, -center.m_y);

		return matrix;
	}
	void ModifyAdjust(wxPoint2DDouble adj) override
	{
		adjust = adj;
		angle = 11;
	}
	double angle = 11;
};