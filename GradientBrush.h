#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>

enum class ColorType
{
    Single,
    Gradient
};

namespace Gradient
{
    wxGraphicsBrush CreateBrush(wxGraphicsContext* gc, wxAffineMatrix2D* matrix, wxRect2DDouble rect, wxGraphicsGradientStops gradientStops);
};