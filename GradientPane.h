#pragma once

#include "SelectablePane.h"
#include "Shape.h"

class GradientPane : public SelectablePane
{
public:
	GradientPane(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	void SetGradientStops(wxGraphicsGradientStops stops);
	wxGraphicsGradientStops GetGradientStops() const {
		return shape.stops;
	}
protected:
	void DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness) override;

private:
	Shape shape = Shape(std::vector<wxPoint2DDouble>{ {0, 0}, { 0, 100 }, { 100, 100 }, { 100, 0 }, { 0, 0 } });
};

