#include "Path.h"


Path::Path(wxColour color, int width)
{
	this->color = color;
	this->width = width;
}

void Path::Draw(wxGraphicsContext* gc)
{
	gc->SetPen(wxPen(color, width));
	gc->StrokeLines(size(), data());

	if (finished && selected) {
		SelectionBox::Draw(gc);
	}
}

void Path::OnPenDown(wxPoint2DDouble pos)
{
	push_back(pos);
}

void Path::OnPenMove(wxPoint2DDouble pos)
{
	push_back(pos);
}

void Path::OnPenUp()
{
	BuildBox(size(), data(), width);
	finished = true;
}



Path* Path::OnMouseDown(wxPoint pos)
{
	if (!GetBound().Contains(pos)) {
		selected = false;
		return nullptr;
	}
	else {
		selected = true;
		return this;
	}
} 
