#include "GradientBrush.h"

wxGraphicsBrush Gradient::CreateBrush(wxGraphicsContext* gc, wxAffineMatrix2D* matrix, wxRect2DDouble rect, wxGraphicsGradientStops gradientStops)
{
    wxPoint2DDouble* startPoint = new wxPoint2DDouble(rect.GetLeftTop().m_x, rect.GetLeftTop().m_y);
    wxPoint2DDouble* endPoint = new wxPoint2DDouble(rect.GetRightTop().m_x, rect.GetRightTop().m_y);

    if (matrix)
    {
        *startPoint = matrix->TransformPoint(*startPoint);
        *endPoint = matrix->TransformPoint(*endPoint);
    }

    wxGraphicsBrush brush = gc->CreateLinearGradientBrush(startPoint->m_x, startPoint->m_y, endPoint->m_x, endPoint->m_y, gradientStops);

    delete startPoint;
    delete endPoint;

    return brush;
}