#pragma once

#include <wx/wx.h>
#include <wx/affinematrix2d.h>

const int RotateArm = 20;

class Transform
{
public:
	virtual wxAffineMatrix2D GetMatrix(double x1, double y1, double x2, double y2, wxAffineMatrix2D transformMatrix) const = 0;
	wxPoint2DDouble adjust;
};

