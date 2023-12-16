#pragma once

#include "GradientPane.h"

class ImageGradientPane : public GradientPane
{
public:
	ImageGradientPane(wxWindow* parent, const std::string dir, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	
private:
	void DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness) override;

private:
	wxImage* image;
};

