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
		transformMatrix.TransformPoint(&center.m_x, &center.m_y);
		
		if (angle > 10) {
			wxPoint2DDouble rotate((x1 + x2) / 2, y1 - RotateArm);
			transformMatrix.TransformPoint(&rotate.m_x, &rotate.m_y);
			wxPoint2DDouble mouse = rotate + adjust;
			angle =-atan2(mouse.m_x - center.m_x, mouse.m_y - center.m_y)
				+ atan2(rotate.m_x - center.m_x, rotate.m_y - center.m_y);
		}

		if (abs(angle) <= 0.01) return matrix;

		matrix.Translate(center.m_x, center.m_y);
		matrix.Rotate(angle);
		matrix.Translate(-center.m_x, -center.m_y);

		return matrix;
	}
	void Modify(wxPoint2DDouble p, wxPoint2DDouble adj) override
	{
		pos = p;
		adjust = adj;
		angle = 11;
	}
	double angle = 11;
};