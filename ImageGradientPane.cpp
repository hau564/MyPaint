#include "ImageGradientPane.h"

ImageGradientPane::ImageGradientPane(wxWindow* parent, const std::string dir, wxWindowID id, const wxPoint& pos, const wxSize& size)
	:GradientPane(parent, id, pos, size)
{
	image = new wxImage(dir, wxBITMAP_TYPE_PNG);
}

void ImageGradientPane::DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness)
{
	GradientPane::DrawContent(gc, rect, roundness);
	if (image->IsOk())
	{
		auto bitmap = wxBitmap(*image);
		gc->DrawBitmap(bitmap, rect.GetX() + 2, rect.GetY() + 2, rect.GetWidth() * 0.6, rect.GetHeight() * 0.6);
	}
}
