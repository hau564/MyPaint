#pragma once

#include "SelectablePane.h"
#include <wx/colour.h>

class ColorPane : public SelectablePane
{
public:
	ColorPane(wxWindow* parent, const wxColor& paneColor = *wxWHITE, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

	void SetColor(const wxColor& color);
	wxColor GetColor() const;

private:
	void DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness) const override;

	wxColor color;
};

