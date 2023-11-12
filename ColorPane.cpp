#include "ColorPane.h"

ColorPane::ColorPane(wxWindow* parent, const wxColor& paneColor, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: SelectablePane(parent, id, pos, size), color(paneColor) {
	
}

void ColorPane::SetColor(const wxColor& color)
{
	this->color = color;
}

wxColor ColorPane::GetColor() const
{
	return color;
}

void ColorPane::DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness) const
{
	gc->SetPen(wxPen(color));
	gc->SetBrush(wxBrush(color));

	gc->DrawRoundedRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight(), roundness);
}
