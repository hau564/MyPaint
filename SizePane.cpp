#include "SizePane.h"

SizePane::SizePane(wxWindow* parent, int paneWidth, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: SelectablePane(parent, id, pos, size), width(paneWidth)
{
}

void SizePane::SetWidth(const int width)
{
	this->width = width;
}

int SizePane::GetWidth() const
{
	return width;
}

void SizePane::DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness)
{
    gc->SetPen(*wxWHITE_PEN);
    gc->SetBrush(*wxWHITE_BRUSH);

    gc->DrawRoundedRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight(), roundness);

    gc->SetPen(*wxBLACK_PEN);
    gc->SetBrush(*wxBLACK_BRUSH);

    gc->DrawEllipse(rect.GetX() + rect.GetWidth() / 2 - width / 2,
        rect.GetY() + rect.GetHeight() / 2 - width / 2,
        width,
        width);
}
