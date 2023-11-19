#pragma once

#ifndef SELECTABLE_PANE_H
#define SELECTABLE_PANE_H

#include <wx/wx.h>

#include <wx/graphics.h>
#include <wx/settings.h>
#include <wx/dcbuffer.h>

class SelectablePane : public wxWindow
{
public:
	SelectablePane(wxWindow *parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);
	
    wxSize DoGetBestSize() const override
    {
        return FromDIP(wxSize(45, 45));
    }

    void SetSelected(bool selected);


protected:
    virtual void DrawContent(wxGraphicsContext* gc, const wxRect& rect, int roundness) = 0;
    virtual void DrawSelected(wxGraphicsContext* gc, const wxRect& rect, int roundness);
    bool selected = false;
private:
    void OnPaint(wxPaintEvent& event);
};

#endif // !SELECTABLE_PANE_H