#pragma once

#include <wx/wx.h>

#include "SelectablePane.h"

class SizePane : public SelectablePane
{
public:
	SizePane(wxWindow* parent, int width, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	void SetWidth(const int width);
	int GetWidth() const;

private:
	void DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness) override;

	int width;
};

