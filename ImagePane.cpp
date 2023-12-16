#include "ImagePane.h"

ImagePane::ImagePane(wxWindow* parent, const std::string dir, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: SelectablePane(parent, id, pos, size)
{
	image = new wxImage(dir, wxBITMAP_TYPE_PNG);
}

void ImagePane::SetBGColor(wxColor color)
{
	bgColor = color;
}

void ImagePane::SetScale(double rx, double ry)
{
	this->rx = rx;
	this->ry = ry;
}

void ImagePane::SetPosition(double dx, double dy)
{
	this->dx = dx;
	this->dy = dy;
}

void ImagePane::DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness)
{
	gc->SetBrush(bgColor);
	gc->DrawRoundedRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight(), roundness);
	if (image->IsOk())
	{
		auto bitmap = wxBitmap(*image);
		gc->DrawBitmap(bitmap, rect.GetX() + dx, rect.GetY() + dy, rect.GetWidth() * rx, rect.GetHeight() * ry);
	}
}
