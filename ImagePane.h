#pragma once

#include "SelectablePane.h"
#include <wx/wx.h>

class ImagePane : public SelectablePane
{
public:
	ImagePane(wxWindow* parent, const std::string dir, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	
	void SetBGColor(wxColor color);
	void SetScale(double rx, double ry);
	void SetPosition(double dx, double dy);

	wxColor GetColor() const { return bgColor; }
protected:
	void DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness) override;

private:
	double rx = 1, ry = 1;
	double dx = 0, dy = 0;
	wxImage* image;
	wxColor bgColor = wxColour(-1, -1, -1, 0);
};

