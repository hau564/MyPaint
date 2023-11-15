#pragma once

#include <wx/wx.h>
#include <wx/affinematrix2d.h>

const int RotateArm = 20;

class Transform
{
public:
	
	virtual wxAffineMatrix2D GetMatrix(double x1, double y1, double x2, double y2, wxAffineMatrix2D transformMatrix) = 0;
	virtual void Modify(wxPoint2DDouble p, wxPoint2DDouble adj) { pos = p; adjust = adj; }
	wxPoint2DDouble pos, adjust;
};

