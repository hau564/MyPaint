#include "ImagePane.h"

ImagePane::ImagePane(wxWindow* parent, const std::string dir, wxWindowID id, const wxPoint& pos, const wxSize& size)
	: SelectablePane(parent, id, pos, size)
{
	image = new wxImage(dir, wxBITMAP_TYPE_PNG);
}

void ImagePane::DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness)
{
	if (image->IsOk())
	{
		auto bitmap = wxBitmap(*image);
		gc->DrawBitmap(bitmap, rect.GetX(), rect.GetY(), rect.GetWidth(), rect.GetHeight());
	}
}
