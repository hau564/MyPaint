#pragma once

#include "SelectablePane.h"
#include <wx/colour.h>
#include "Shape.h"

class ShapePane : public SelectablePane
{
public:
	ShapePane(wxWindow* parent, std::vector<wxPoint2DDouble> points, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	Shape GetShape() const { return *shape; }

private:
	void DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness) override;
	void DrawSelected(wxGraphicsContext* gc, const wxRect& rect, int roundness) override;
	Shape* shape;
	std::vector<wxPoint2DDouble> points;

	int d = 5;
};

