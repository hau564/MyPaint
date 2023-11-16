#pragma once

#include <wx/wx.h>
#include <wx/affinematrix2d.h>

const int RotateArm = 20;

class Transform
{
public:	
	virtual wxAffineMatrix2D GetMatrix(double x1, double y1, double x2, double y2, wxAffineMatrix2D transformMatrix) = 0;
	virtual void Modify(wxPoint2DDouble p, wxPoint2DDouble adj, int holding = -1) { 
		pos = p; 
		adjust = adj; 
		holdingKey = holding;
	}
	wxPoint2DDouble pos, adjust;
	int holdingKey = -1;
};

