#pragma once

#include "Transform.h"

class TransformMove : public Transform
{
public:
	wxAffineMatrix2D GetMatrix(double x1, double y1, double x2, double y2, wxAffineMatrix2D transformMatrix) override
	{
		wxAffineMatrix2D matrix;
		wxPoint2DDouble p = adjust;
		transformMatrix.Invert();
		transformMatrix.TransformDistance(&p.m_x, &p.m_y);
		matrix.Translate(p.m_x, p.m_y);
		return matrix;
	}
};