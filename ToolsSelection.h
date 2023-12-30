#pragma once

#include <wx/wx.h>
#include "Shape.h"

class ToolsSelection
{
public:
    void SetPenColor(wxColor color);
    void SetBrushColor(wxColor color);
    void SetPenSize(int size);
    void SetShape(Shape shape);
    void SetGradientStops(wxGraphicsGradientStops stops);
    void SetTextFont(wxFont font);

    wxColor GetPenColor() const { return penColor; }
    wxColor GetBrushColor() const { return brushColor; }
    int GetPenSize() const { return penSize; }
    Shape GetShape() const { return shape; }
    wxGraphicsGradientStops GetGradientStops() const { return stops; }
    bool IsGradient() const { return isGradient; }
    wxFont GetTextFont() const { return font; }

private:
    wxColor penColor = wxColor(0, 0, 0);
    wxColor brushColor = wxColor(200, 200, 200);
    int penSize = 1;
    Shape shape;
    wxGraphicsGradientStops stops;
    bool isGradient = false;
    wxFont font;
};

