#pragma once

#include "SelectablePane.h"

class ImagePane : public SelectablePane
{
public:
	ImagePane(wxWindow* parent, const std::string dir, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	
private:
	void DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness) override;
	wxImage* image;
};

